using System;
using UnityEngine;

public enum ShapeType
{
    Box = 0,
    Sphere = 1,
    Capsule = 2,
    Cylinder = 3,
    Plane = 4,
    ConvexHull = 5,
    Mesh = 6
}
public enum ShapeWrap
{
    None = 0,
    TranslateShape = 1,
    TransformShape = 2,
}

[AddComponentMenu("PhysicsRT/Physics Shape")]
[DefaultExecutionOrder(100)]
[DisallowMultipleComponent]
public class PhysicsShape : MonoBehaviour
{
    [SerializeField]
    [Tooltip("Defines the object’s shape and size for collision detection purposes.")]
    private ShapeType m_ShapeType = ShapeType.Box;
    [SerializeField]
    [Tooltip("Wrap other convex shapes with an additional transform.")]
    private ShapeWrap m_Wrap = ShapeWrap.None;

    [SerializeField]
    private Vector3 m_Translation = Vector3.zero;
    [SerializeField]
    private Vector3 m_Rotation = Vector3.zero;
    [SerializeField]
    private Vector3 m_Scale = Vector3.zero;
    
    [SerializeField]
    private CustomPhysicsMaterialTags m_CustomTags = CustomPhysicsMaterialTags.Nothing;

    [SerializeField]
    private Mesh m_ShapeMesh = null;
    [SerializeField]
    private Vector3 m_ShapeSize = Vector3.one;
    [SerializeField]
    private float m_ShapeRadius = 0.5f;
    [SerializeField]
    private float m_ShapeConvexRadius = 0.0f;
    [SerializeField]
    private float m_ShapeHeight = 1.0f;
    [SerializeField]
    private int m_ShapeSideCount = 32;
    [SerializeField]
    [Tooltip(
        "Specifies the minimum weight of a skinned vertex assigned to this shape and/or its transform children required for it to be included for automatic detection. " +
        "A value of 0 will include all points with any weight assigned to this shape's hierarchy."
    )]
    [Range(0f, 1f)]
    private float m_MinimumSkinnedVertexWeight = 0.1f;
    private IntPtr ptr = IntPtr.Zero;
    private IntPtr shapeRealPtr = IntPtr.Zero;

    public IntPtr Ptr => ptr;
    public ShapeType ShapeType => m_ShapeType;
    public ShapeWrap Wrap => m_Wrap;
    public Mesh ShapeMesh { get => m_ShapeMesh; set => m_ShapeMesh = value; }
    public Vector3 ShapeSize { get => m_ShapeSize; set => m_ShapeSize = value; }
    public float ShapeRadius { get => m_ShapeRadius; set => m_ShapeRadius = value; }
    public float ShapeConvexRadius { get => m_ShapeConvexRadius; set => m_ShapeConvexRadius = value; }
    public float ShapeHeight { get => m_ShapeHeight; set => m_ShapeHeight = value; }
    public int ShapeSideCount { get => m_ShapeSideCount; set => m_ShapeSideCount = value; }
    public Vector3 ShapeScale { get => m_Scale; set => m_Scale = value; }
    public Vector3 ShapeRotation { get => m_Rotation; set => m_Rotation = value; }
    public Vector3 ShapeTranslation { get => m_Translation; set => m_Translation = value; }
    public float MinimumSkinnedVertexWeight { get => m_MinimumSkinnedVertexWeight; set => m_MinimumSkinnedVertexWeight = value; }


    private void Awake() {
        if(m_ShapeMesh == null) {
            var m = GetComponent<MeshFilter>();
            if(m != null) m_ShapeMesh = m.mesh;
        }
        CreateShape();
    }
    private void OnDestroy() {
        DestroyShape();
    }
    private void OnValidate()
    {
        m_ShapeConvexRadius = Mathf.Max(m_ShapeConvexRadius, 0f);
        m_ShapeRadius = Mathf.Max(m_ShapeRadius, 0f);
        m_ShapeSideCount = (int)Mathf.Max(m_ShapeSideCount, 0f);
        m_ShapeHeight = Mathf.Max(m_ShapeHeight, 0f);
    }

    public void CreateShape() {

        //Create base shape
        switch(m_ShapeType) {
            case ShapeType.Box:
                using(var vec4 = new hkVector4(m_ShapeSize))
                    shapeRealPtr = PhysicsApi.hkpBoxShape_new(vec4.Ptr, m_ShapeConvexRadius);
                break;
            case ShapeType.Capsule:
                shapeRealPtr = PhysicsApi.hkpCapsuleShape_new(m_ShapeHeight, m_ShapeConvexRadius);
                break;
            case ShapeType.ConvexHull:
                break;
            case ShapeType.Cylinder:
                shapeRealPtr = PhysicsApi.hkpCylinderShape_new(m_ShapeHeight, m_ShapeRadius, m_ShapeConvexRadius);
                break;
            case ShapeType.Mesh:
                break;
            case ShapeType.Plane:
                break;
            case ShapeType.Sphere:
                shapeRealPtr = PhysicsApi.hkpSphereShape_new(m_ShapeRadius);
                break;
        }
   
        //Create Wrap shape
        switch(m_Wrap) {
            case ShapeWrap.None:
                ptr = shapeRealPtr;
                break;
            case ShapeWrap.TransformShape:

                break;
            case ShapeWrap.TranslateShape:

                break;
        }
    }
    public void DestroyShape() {
        if(ptr != shapeRealPtr) {
            
        }
    }

    public void FitToEnabledRenderMeshes(float f) {

    }
}
