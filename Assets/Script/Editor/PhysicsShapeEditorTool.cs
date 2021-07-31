using System;
using System.Collections.Generic;
using PhyicsRT;
using Unity.Mathematics;
using Unity.Physics.Editor;
using UnityEditor;
using UnityEditor.EditorTools;
using UnityEditor.IMGUI.Controls;
using UnityEngine;

[EditorTool("PhysicsShapeEditorTool", typeof(PhysicsShape))]
public class PhysicsShapeEditorTool : EditorTool
{
  private static readonly BeveledBoxBoundsHandle s_Box = new BeveledBoxBoundsHandle();
  private static readonly PhysicsCapsuleBoundsHandle s_Capsule =
    new PhysicsCapsuleBoundsHandle { heightAxis = CapsuleBoundsHandle.HeightAxis.Z };
  private static readonly BeveledCylinderBoundsHandle s_Cylinder = new BeveledCylinderBoundsHandle();
  private static readonly PhysicsSphereBoundsHandle s_Sphere = new PhysicsSphereBoundsHandle();
  private static readonly BoxBoundsHandle s_Plane =
      new BoxBoundsHandle { axes = PrimitiveBoundsHandle.Axes.X | PrimitiveBoundsHandle.Axes.Z };

  private static readonly Color k_ShapeHandleColor = new Color32(145, 244, 139, 210);
  private static readonly Color k_ShapeHandleColorDisabled = new Color32(84, 200, 77, 140);
  private int m_DraggingControlID = 0;

  private static readonly string GenericUndoMessage = L10n.Tr("Change Shape");

  public override GUIContent toolbarIcon
  {
    get { return EditorGUIUtility.IconContent("EditCollider"); }
  }

  public override void OnActivated()
  {
    base.OnActivated();
  }
  public override void OnWillBeDeactivated()
  {
    base.OnWillBeDeactivated();
  }
  public override void OnToolGUI(EditorWindow window)
  {
    var hotControl = GUIUtility.hotControl;
    switch (Event.current.GetTypeForControl(hotControl))
    {
      case EventType.MouseDrag:
        m_DraggingControlID = hotControl;
        break;
      case EventType.MouseUp:
        m_DraggingControlID = 0;
        break;
    }

    var shape = target as PhysicsShape;

    var sOrientation = shape.Wrap == ShapeWrap.TransformShape ? Quaternion.Euler(shape.ShapeRotation) : Quaternion.Euler(Vector3.zero);
    var sTranslation = shape.Wrap == ShapeWrap.None ? Vector3.zero : shape.ShapeTranslation;

    var handleColor = shape.enabled ? k_ShapeHandleColor : k_ShapeHandleColorDisabled;
    var handleMatrix = new float4x4(MathUtils.DecomposeRigidBodyTransform(shape.transform.localToWorldMatrix));
    using (new Handles.DrawingScope(handleColor, handleMatrix))
    {
      switch (shape.ShapeType)
      {
        case ShapeType.Box:
          s_Box.bevelRadius = shape.ShapeConvexRadius;
          s_Box.center = sTranslation;
          s_Box.size = shape.ShapeSize;
          EditorGUI.BeginChangeCheck();
          {
            using (new Handles.DrawingScope(math.mul(Handles.matrix, float4x4.TRS(sTranslation, sOrientation, 1f))))
              s_Box.DrawHandle();
          }
          if (EditorGUI.EndChangeCheck())
          {
            Undo.RecordObject(shape, GenericUndoMessage);
            shape.ShapeSize = s_Box.size;
            shape.ShapeConvexRadius = s_Box.bevelRadius;
          }
          break;
        case ShapeType.Capsule:
          s_Capsule.center = sTranslation;
          s_Capsule.height = shape.ShapeHeight;
          s_Capsule.radius = shape.ShapeRadius;
          EditorGUI.BeginChangeCheck();
          {
            using (new Handles.DrawingScope(math.mul(Handles.matrix, float4x4.TRS(sTranslation, sOrientation, 1f))))
              s_Capsule.DrawHandle();
          }
          if (EditorGUI.EndChangeCheck())
          {
            Undo.RecordObject(shape, GenericUndoMessage);
            shape.ShapeHeight = s_Capsule.height;
            shape.ShapeRadius = s_Capsule.radius;
          }
          break;
        case ShapeType.Sphere:
          s_Sphere.center = sTranslation;
          s_Sphere.radius = shape.ShapeRadius;
          EditorGUI.BeginChangeCheck();
          {
            using (new Handles.DrawingScope(math.mul(Handles.matrix, float4x4.TRS(sTranslation, sOrientation, 1f))))
              s_Sphere.DrawHandle();
          }
          if (EditorGUI.EndChangeCheck())
          {
            Undo.RecordObject(shape, GenericUndoMessage);
            shape.ShapeRadius = s_Sphere.radius;
          }
          break;
        case ShapeType.Cylinder:
          s_Cylinder.center = float3.zero;
          s_Cylinder.height = shape.ShapeHeight;
          s_Cylinder.radius = shape.ShapeRadius;
          s_Cylinder.sideCount = shape.ShapeSideCount;
          s_Cylinder.bevelRadius = shape.ShapeConvexRadius;
          EditorGUI.BeginChangeCheck();
          {
            using (new Handles.DrawingScope(math.mul(Handles.matrix, float4x4.TRS(sTranslation, sOrientation, 1f))))
              s_Cylinder.DrawHandle();
          }
          if (EditorGUI.EndChangeCheck())
          {
            Undo.RecordObject(shape, GenericUndoMessage);
            shape.ShapeHeight = s_Cylinder.height;
            shape.ShapeRadius = s_Cylinder.radius;
            shape.ShapeConvexRadius = s_Cylinder.bevelRadius;
          }
          break;
        case ShapeType.Plane:
          {
            var size2 = shape.ShapeSize;
            s_Plane.center = float3.zero;
            s_Plane.size = new float3(size2.x, size2.y, size2.z);
            EditorGUI.BeginChangeCheck();
            {
              var m = math.mul(shape.transform.localToWorldMatrix, float4x4.TRS(sTranslation, sOrientation, 1f));
              using (new Handles.DrawingScope(m))
                s_Plane.DrawHandle();
              var right = math.mul(m, new float4 { x = 1f }).xyz;
              var forward = math.mul(m, new float4 { z = 1f }).xyz;
              var normal = math.cross(math.normalizesafe(forward), math.normalizesafe(right))
                  * 0.5f * math.lerp(math.length(right) * size2.x, math.length(forward) * size2.y, 0.5f);

              using (new Handles.DrawingScope(float4x4.identity))
                Handles.DrawLine(m.c3.xyz, m.c3.xyz + normal);
            }
            if (EditorGUI.EndChangeCheck())
            {
              Undo.RecordObject(shape, GenericUndoMessage);
              shape.ShapeSize = s_Plane.size;
            }
            break;
          }
        case ShapeType.ConvexHull:
        case ShapeType.Mesh:
          {
            if (Event.current.type != EventType.Repaint)
              break;
            var points = GetPreviewData(shape).Edges;
            if (points != null && points.Length > 0)
              Handles.DrawLines(points);
            break;
          }
      }
    }
    base.OnToolGUI(window);
  }

  public class PreviewMeshData : IDisposable
  {
    private bool disposedValue;

    protected virtual void Dispose(bool disposing)
    {
      if (!disposedValue)
      {
        if (disposing)
        {
          // TODO: 释放托管状态(托管对象)
        }

        // TODO: 释放未托管的资源(未托管的对象)并重写终结器
        // TODO: 将大型字段设置为 null
        disposedValue = true;
      }
    }

    ~PreviewMeshData()
    {
      Dispose(disposing: false);
    }

    public void Dispose()
    {
      Dispose(disposing: true);
      GC.SuppressFinalize(this);
    }

    public void SchedulePreviewIfChanged(PhysicsShape shape) {

    }

    public Vector3[] Edges {
      get {
        return null;
      }
    }
  }

  private Dictionary<PhysicsShape, PreviewMeshData> m_PreviewData = new Dictionary<PhysicsShape, PreviewMeshData>();

  public PreviewMeshData GetPreviewData(PhysicsShape shape)
  {
    if (shape.ShapeType != ShapeType.ConvexHull && shape.ShapeType != ShapeType.Mesh)
      return null;

    if (!m_PreviewData.TryGetValue(shape, out var preview))
    {
      preview = m_PreviewData[shape] = new PreviewMeshData();
      preview.SchedulePreviewIfChanged(shape);
    }

    // do not generate a new preview until the user has finished dragging a control handle (e.g., scale)
    if (m_DraggingControlID == 0 && !EditorGUIUtility.editingTextField)
      preview.SchedulePreviewIfChanged(shape);

    return preview;
  }
}