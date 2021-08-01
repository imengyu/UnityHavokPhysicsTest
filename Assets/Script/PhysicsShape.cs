using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;

namespace PhyicsRT
{
    public enum ShapeType
    {
        Box,
        Sphere,
        Capsule,
        Cylinder,
        Plane,
        ConvexHull,
        Mesh,
        List,
        StaticCompound,
    }
    public enum ShapeWrap
    {
        None = 0,
        TranslateShape = 1,
        TransformShape = 2,
    }

    [AddComponentMenu("PhysicsRT/Physics Shape")]
    [DefaultExecutionOrder(110)]
    [DisallowMultipleComponent]
    public class PhysicsShape : MonoBehaviour
    {
        [SerializeField]
        [Tooltip("为碰撞检测目的定义对象的形状和大小。")]
        private ShapeType m_ShapeType = ShapeType.Box;
        [SerializeField]
        [Tooltip("使用附加变换包裹其他凸面形状。")]
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
        [Tooltip("指定指定给此形状的蒙皮顶点的最小权重和/或自动检测所需的变换子级。值为0时，将包括所有具有指定给此形状层次的任何权重的点。")]
        [Range(0f, 1f)]
        private float m_MinimumSkinnedVertexWeight = 0.1f;
        private IntPtr ptr = IntPtr.Zero;
        private IntPtr shapeRealPtr = IntPtr.Zero;

        public int StaticCompoundChildId { get; private set; }
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

        private void Start() {
            if(m_ShapeMesh == null) {
                var m = GetComponent<MeshFilter>();
                if(m != null) m_ShapeMesh = m.mesh;
            }
        }
        private void OnValidate()
        {
            m_ShapeConvexRadius = Mathf.Max(m_ShapeConvexRadius, 0f);
            m_ShapeRadius = Mathf.Max(m_ShapeRadius, 0f);
            m_ShapeSideCount = (int)Mathf.Max(m_ShapeSideCount, 0f);
            m_ShapeHeight = Mathf.Max(m_ShapeHeight, 0f);
        }

        public IntPtr GetPtr() { return ptr; }
        public IntPtr ComputeMassProperties(float mass)
        {
            IntPtr result = IntPtr.Zero;
            switch (ShapeType)
            {
                case ShapeType.Box:
                    {
                        IntPtr sizePtr = PhysicsApi.API.CreateVec3(ShapeSize.x, ShapeSize.y, ShapeSize.z);
                        result = PhysicsApi.API.ComputeBoxVolumeMassProperties(sizePtr, mass);
                        PhysicsApi.API.DestroyVec3(sizePtr);
                        break;
                    }
                case ShapeType.Sphere:
                    {
                        result = PhysicsApi.API.ComputeSphereVolumeMassProperties(ShapeRadius, mass);
                        break;
                    }
                case ShapeType.Capsule:
                    {
                        IntPtr posPtrStart = PhysicsApi.API.CreateVec3(0, ShapeHeight / 2, 0);
                        IntPtr posPtrEnd = PhysicsApi.API.CreateVec3(0, -ShapeHeight / 2, 0);
                        result = PhysicsApi.API.ComputeCapsuleVolumeMassProperties(posPtrStart, posPtrEnd, ShapeRadius, mass);
                        PhysicsApi.API.DestroyVec3(posPtrEnd);
                        PhysicsApi.API.DestroyVec3(posPtrStart);
                        break;
                    }
                case ShapeType.Cylinder:
                    {
                        IntPtr posPtrStart = PhysicsApi.API.CreateVec3(0, ShapeHeight / 2, 0);
                        IntPtr posPtrEnd = PhysicsApi.API.CreateVec3(0, -ShapeHeight / 2, 0);
                        result = PhysicsApi.API.ComputeCylinderVolumeMassProperties(posPtrStart, posPtrEnd, ShapeRadius, mass);
                        PhysicsApi.API.DestroyVec3(posPtrEnd);
                        PhysicsApi.API.DestroyVec3(posPtrStart);
                        break;
                    }
                case ShapeType.Plane:
                    {
                        IntPtr sizePtr = PhysicsApi.API.CreateVec3(ShapeSize.x, 0, ShapeSize.z);
                        result = PhysicsApi.API.ComputeBoxVolumeMassProperties(sizePtr, mass);
                        PhysicsApi.API.DestroyVec3(sizePtr);
                        break;
                    }
                case ShapeType.ConvexHull:
                case ShapeType.Mesh:
                case ShapeType.List:
                    {
                        result = PhysicsApi.API.ComputeShapeVolumeMassProperties(ptr, mass);
                        break;
                    }
                case ShapeType.StaticCompound:
                    break;
            }
            return result;
        }

        [StructLayout(LayoutKind.Sequential)]
        struct sPhysicsShape {
            public IntPtr shape;
            public UInt16 type;
            public IntPtr staticCompoundShapeRetIds;
            public int staticCompoundShapeRetIdsCount;
        };

        private void CreateShape(bool forceRecreate) {

            //Create base shape
            switch (m_ShapeType)
            {
                case ShapeType.Box:
                    {
                        IntPtr sizePtr = PhysicsApi.API.CreateVec3(ShapeSize.x, ShapeSize.y, ShapeSize.z);
                        shapeRealPtr = PhysicsApi.API.CreateBoxShape(sizePtr, ShapeConvexRadius);
                        PhysicsApi.API.DestroyVec3(sizePtr);
                        break;
                    }
                case ShapeType.Plane:
                    {
                        IntPtr sizePtr = PhysicsApi.API.CreateVec3(ShapeSize.x, 0.01f, ShapeSize.z);
                        shapeRealPtr = PhysicsApi.API.CreateBoxShape(sizePtr, ShapeConvexRadius);
                        PhysicsApi.API.DestroyVec3(sizePtr);
                        break;
                    }
                case ShapeType.Capsule:
                    {
                        IntPtr posPtrStart = PhysicsApi.API.CreateVec3(0, ShapeHeight / 2, 0);
                        IntPtr posPtrEnd = PhysicsApi.API.CreateVec3(0, -ShapeHeight / 2, 0);
                        shapeRealPtr = PhysicsApi.API.CreateCapsuleShape(posPtrStart, posPtrEnd, ShapeRadius);
                        PhysicsApi.API.DestroyVec3(posPtrEnd);
                        PhysicsApi.API.DestroyVec3(posPtrStart);
                        break;
                    }
                case ShapeType.Cylinder:
                    {
                        IntPtr posPtrStart = PhysicsApi.API.CreateVec3(0, ShapeHeight / 2, 0);
                        IntPtr posPtrEnd = PhysicsApi.API.CreateVec3(0, -ShapeHeight / 2, 0);
                        shapeRealPtr = PhysicsApi.API.CreateCylindeShape(posPtrStart, posPtrEnd, ShapeRadius, ShapeConvexRadius);
                        PhysicsApi.API.DestroyVec3(posPtrEnd);
                        PhysicsApi.API.DestroyVec3(posPtrStart);
                        break;
                    }
                case ShapeType.Sphere:
                    {
                        shapeRealPtr = PhysicsApi.API.CreateSphereShape(ShapeRadius);
                        break;
                    }
                case ShapeType.ConvexHull:
                    {
                        Mesh mesh = ShapeMesh;
                        if (mesh == null)
                        {
                            Debug.LogWarning("ConvexHull need a mesh");
                            return;
                        }

                        //To HGlobal
                        float[] verticesArr = new float[mesh.vertices.Length * 3];
                        for (int i = 0; i < mesh.vertices.Length; i++)
                        {
                            verticesArr[i * 3 + 0] = mesh.vertices[i].x;
                            verticesArr[i * 3 + 1] = mesh.vertices[i].y;
                            verticesArr[i * 3 + 2] = mesh.vertices[i].z;
                        }
                        int bufferSize = Marshal.SizeOf(verticesArr);
                        IntPtr verticesBuffer = Marshal.AllocHGlobal(bufferSize);
                        Marshal.Copy(verticesArr, 0, verticesBuffer, verticesArr.Length);

                        IntPtr convexHullResult = PhysicsApi.API.Build3DPointsConvexHull(verticesBuffer, mesh.vertices.Length);
                        shapeRealPtr = PhysicsApi.API.CreateConvexVerticesShapeByConvexHullResult(convexHullResult, ShapeConvexRadius);

                        Marshal.FreeHGlobal(verticesBuffer);
                        PhysicsApi.API.CommonDelete(convexHullResult);
                        break;
                    }
                case ShapeType.Mesh:
                    {
                        Mesh mesh = ShapeMesh;
                        if (mesh == null)
                        {
                            Debug.LogWarning("Shape need a mesh");
                            return;
                        }

                        float[] verticesArr = new float[mesh.vertices.Length * 3];
                        for (int i = 0; i < mesh.vertices.Length; i++)
                        {
                            verticesArr[i * 3 + 0] = mesh.vertices[i].x;
                            verticesArr[i * 3 + 1] = mesh.vertices[i].y;
                            verticesArr[i * 3 + 2] = mesh.vertices[i].z;
                        }
                        int bufferSize = Marshal.SizeOf(verticesArr);
                        IntPtr verticesBuffer = Marshal.AllocHGlobal(bufferSize);
                        Marshal.Copy(verticesArr, 0, verticesBuffer, verticesArr.Length);

                        shapeRealPtr = PhysicsApi.API.CreateConvexVerticesShape(verticesBuffer, mesh.vertices.Length, ShapeConvexRadius);

                        Marshal.FreeHGlobal(verticesBuffer);
                        break;
                    }
                case ShapeType.List:
                    {
                        List<IntPtr> childernTransforms = null;
                        IntPtr childTransforms = IntPtr.Zero;
                        IntPtr childs = GetChildernShapes(forceRecreate, false, out int childCount, ref childTransforms, ref childernTransforms);
                        PhysicsApi.API.CreateListShape(childs, childCount);
                        Marshal.FreeHGlobal(childs);
                        break;
                    }
                case ShapeType.StaticCompound:
                    {
                        List<IntPtr> childernTransforms = new List<IntPtr>();
                        IntPtr childTransforms = IntPtr.Zero;
                        IntPtr childs = GetChildernShapes(forceRecreate, true, out int childCount, ref childTransforms, ref childernTransforms);
                        IntPtr retStruct = PhysicsApi.API.CreateStaticCompoundShape(childs, childTransforms, childCount);

                        //更新ID至每个shape
                        sPhysicsShape str = (sPhysicsShape)Marshal.PtrToStructure(retStruct, typeof(sPhysicsShape));
                        int[] staticCompoundShapeRetIds = new int[str.staticCompoundShapeRetIdsCount];
                        Marshal.Copy(str.staticCompoundShapeRetIds, staticCompoundShapeRetIds, 0, str.staticCompoundShapeRetIdsCount);
                        for (int i = 0, ia = 0, c = transform.childCount; i < c; i++) {
                            var shape = transform.GetChild(i).gameObject.GetComponent<PhysicsShape>();
                            if (shape != null) {
                                ia++;
                                shape.StaticCompoundChildId = staticCompoundShapeRetIds[ia];
                            }
                        }

                        Marshal.FreeHGlobal(childs);
                        Marshal.FreeHGlobal(childTransforms);

                        foreach (var p in childernTransforms)
                            PhysicsApi.API.DestroyTransform(p);
                        childernTransforms.Clear();
                        break;
                    }
            }
    
            //Create Wrap shape
            switch(m_Wrap) {
                case ShapeWrap.None:
                    ptr = shapeRealPtr;
                    break;
                case ShapeWrap.TransformShape:
                    {
                        Quaternion quaternion = Quaternion.Euler(ShapeRotation.x, ShapeRotation.y, ShapeRotation.z);
                        IntPtr posPtr = PhysicsApi.API.CreateTransform(
                            ShapeTranslation.x, ShapeTranslation.y, ShapeTranslation.z,
                            quaternion.x, quaternion.y, quaternion.z, quaternion.w,
                            ShapeScale.x, ShapeScale.y, ShapeScale.z
                        );
                        PhysicsApi.API.CreateConvexTransformShape(shapeRealPtr, posPtr);
                        PhysicsApi.API.DestroyTransform(posPtr);
                        break;
                    }
                case ShapeWrap.TranslateShape:
                    {
                        IntPtr posPtr = PhysicsApi.API.CreateVec3(ShapeTranslation.x, ShapeTranslation.y, ShapeTranslation.z);
                        PhysicsApi.API.CreateConvexTranslateShape(shapeRealPtr, posPtr);
                        PhysicsApi.API.DestroyVec3(posPtr);
                        break;
                    }
            }
        }
        private void DestroyShape(bool forceRecreate = false) {
            if(ptr != shapeRealPtr) {
                PhysicsApi.API.DestroyShape(shapeRealPtr);
                shapeRealPtr = IntPtr.Zero;
            }

            PhysicsApi.API.DestroyShape(ptr);
            ptr = IntPtr.Zero;
        }
        private IntPtr GetChildernShapes(bool forceRecreate, bool withChildTransforms, out int childCount, ref IntPtr outChildTransforms, ref List<IntPtr> childernTransforms)
        {
            //获取子级 PhysicsShape 的指针

            List<IntPtr> childernShapes = new List<IntPtr>();
            for (int i = 0, c = transform.childCount; i < c; i++) {
                var shape = transform.GetChild(i).gameObject.GetComponent<PhysicsShape>();
                if (shape != null)
                {
                    childernShapes.Add(shape.GetShapeBody(forceRecreate));

                    if (withChildTransforms)// Child Transforms
                    {
                        childernTransforms.Add(PhysicsApi.API.CreateTransform(
                            shape.transform.position.x, shape.transform.position.y, shape.transform.position.z,
                            shape.transform.rotation.x, shape.transform.rotation.y, shape.transform.rotation.z, shape.transform.rotation.w,
                            shape.transform.localScale.x, shape.transform.localScale.y, shape.transform.localScale.z
                        ));
                    }
                }
            }

            childCount = childernShapes.Count;

            var outArr = childernShapes.ToArray();
            IntPtr outArrBuf = Marshal.AllocHGlobal(Marshal.SizeOf(outArr));
            Marshal.Copy(outArr, 0, outArrBuf, outArr.Length);

            if (withChildTransforms)
            {
                var outArr2 = childernTransforms.ToArray();
                IntPtr outArrBuf2 = Marshal.AllocHGlobal(Marshal.SizeOf(outArr2));
                Marshal.Copy(outArr2, 0, outArrBuf2, outArr2.Length);
                outChildTransforms = outArrBuf2;
            }

            return outArrBuf;
        }

        public void ReleaseShapeBody() {
            DestroyShape(false);

            if(ShapeType == ShapeType.List || ShapeType == ShapeType.StaticCompound)
                for (int i = 0, c = transform.childCount; i < c; i++) {
                    var shape = transform.GetChild(i).gameObject.GetComponent<PhysicsShape>();
                    if (shape != null)
                        shape.ReleaseShapeBody();
                }
        }
        public IntPtr GetShapeBody(bool forceRecreate)
        {
            if (forceRecreate && ptr != IntPtr.Zero)
                DestroyShape(true);
            if (ptr == IntPtr.Zero)
                CreateShape(forceRecreate);
            return ptr;
        }
        public void FitToEnabledRenderMeshes(float f) {
            if(ShapeMesh == null)
            {
                Debug.LogWarning("Not found mesh in this gameObject");
                return;
            }
            Bounds bounds = ShapeMesh.bounds;
            switch (m_ShapeType)
            {
                case ShapeType.Box:
                case ShapeType.Plane:
                    ShapeSize = bounds.size;
                    ShapeTranslation = bounds.center;
                    break;
                case ShapeType.Capsule:
                case ShapeType.Cylinder:
                    ShapeRadius = new Vector2(bounds.size.x, bounds.size.z).magnitude / 2;
                    ShapeHeight = bounds.size.y;
                    break;
                case ShapeType.Sphere:
                    ShapeRadius = bounds.size.magnitude / 2;
                    break;
            }
        }

        public void SetChildInstanceEnable(int id, bool enable)
        {
            if(m_ShapeType != ShapeType.StaticCompound)
            {
                Debug.LogError("Only StaticCompoundShape can use this action");
                return;
            }

            PhysicsApi.API.StaticCompoundShapeSetInstanceEnabled(shapeRealPtr, id, enable ? 1 : 0);
        }
        public bool GetChildInstanceEnable(int id)
        {
            if (m_ShapeType != ShapeType.StaticCompound)
            {
                Debug.LogError("Only StaticCompoundShape can use this action");
                return false;
            }
            return PhysicsApi.API.StaticCompoundShapeIsInstanceEnabled(shapeRealPtr, id) > 0;
        }
        public void EnableAllChildInstance()
        {
            if (m_ShapeType != ShapeType.StaticCompound)
            {
                Debug.LogError("Only StaticCompoundShape can use this action");
                return;
            }

            PhysicsApi.API.StaticCompoundShapeEnableAllInstancesAndShapeKeys(shapeRealPtr);
        }
    }
}
