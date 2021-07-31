using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace PhyicsRT
{
    public static class PhysicsApi
    {
#if UNITY_IPHONE && !UNITY_EDITOR
	    private const string DLL_NNAME = "_Internal";
#else
        private const string DLL_NNAME = "Physics_RT";
#endif

        private const CallingConvention _CallingConvention = CallingConvention.Cdecl;

        [StructLayout(LayoutKind.Sequential)]
        private struct sInitStruct {
            public IntPtr errCallback;
            public bool mulithread;
            public int smallPoolSize;
        };
        [StructLayout(LayoutKind.Sequential)]
        private struct sApiStruct {
            public IntPtr CommonDelete;
            public IntPtr CreateVec3;
            public IntPtr CreateTransform;
            public IntPtr CreateVec4;
            public IntPtr DestroyVec4;
            public IntPtr DestroyVec3;
            public IntPtr DestroyTransform;
            public IntPtr CreatePhysicsWorld;
            public IntPtr DestroyPhysicsWorld;
            public IntPtr StepPhysicsWorld;
            public IntPtr SetPhysicsWorldGravity;
            public IntPtr ReadPhysicsWorldBodys;
            public IntPtr CreateRigdBody;
            public IntPtr ActiveRigdBody;
            public IntPtr DeactiveRigdBody;
            public IntPtr SetRigdBodyMass;
            public IntPtr SetRigdBodyFriction;
            public IntPtr SetRigdBodyRestitution;
            public IntPtr SetRigdBodyCenterOfMass;
            public IntPtr SetRigdBodyPosition;
            public IntPtr SetRigdBodyPositionAndRotation;
            public IntPtr SetRigdBodyLinearDampin;
            public IntPtr SetRigdBodyAngularDamping;
            public IntPtr SetRigdBodyMotionType;
	        public IntPtr SetRigdBodyGravityFactor;
            public IntPtr GetConvexHullResultTriangles;
            public IntPtr GetConvexHullResultVertices;
            public IntPtr Build3DPointsConvexHull;
            public IntPtr Build3DFromPlaneConvexHull;
            public IntPtr DestroyRigdBody;
            public IntPtr ComputeShapeVolumeMassProperties;
            public IntPtr ComputeBoxSurfaceMassProperties;
            public IntPtr ComputeBoxVolumeMassProperties;
            public IntPtr ComputeCapsuleVolumeMassProperties;
            public IntPtr ComputeCylinderVolumeMassProperties;
            public IntPtr ComputeSphereVolumeMassProperties;
            public IntPtr ComputeSphereSurfaceMassProperties;
            public IntPtr ComputeTriangleSurfaceMassProperties;
            public IntPtr CreateBoxShape;
            public IntPtr CreateSphereShape;
            public IntPtr CreateCapsuleShape;
            public IntPtr CreateCylindeShape;
            public IntPtr CreateTriangleShape;
            public IntPtr CreateConvexVerticesShape;
            public IntPtr CreateConvexVerticesShapeByConvexHullResult;
            public IntPtr CreateConvexTranslateShape;
            public IntPtr CreateConvexTransformShape;
            public IntPtr CreateListShape;
            public IntPtr CreateStaticCompoundShape;
            public IntPtr StaticCompoundShapeSetInstanceEnabled;
            public IntPtr StaticCompoundShapeIsInstanceEnabled;
            public IntPtr StaticCompoundShapeEnableAllInstancesAndShapeKeys;
            public IntPtr DestroyShape;
        };

        public delegate void ErrorReportCallback([MarshalAs(UnmanagedType.LPStr)] string msg);

        [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
        private static extern IntPtr init(IntPtr pInitStruct);
        [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
        private static extern bool quit();

        private static void ErrorReport(string msg) {
            Debug.LogError(msg);
        }

        /// <summary>
        /// 释放
        /// </summary>
        public static void PhysicsApiDestroy() {
            quit();
        }
        /// <summary>
        /// 初始化
        /// </summary>
        public static void PhysicsApiInit() {

            //初始化
            sInitStruct intStruct = new sInitStruct();
            intStruct.mulithread = PhysicsConfig.mulithread;
            intStruct.smallPoolSize = PhysicsConfig.smallPoolSize;
            ErrorReportCallback callback = ErrorReport;
            intStruct.errCallback = Marshal.GetFunctionPointerForDelegate(callback);

            //拷贝结构体至托管内存
            int nSizeOfPerson = Marshal.SizeOf(intStruct);
            IntPtr intStructPtr = Marshal.AllocHGlobal(nSizeOfPerson);
            Marshal.StructureToPtr(intStruct, intStructPtr, false);

            //调用初始化
            IntPtr apiStructPtr = init(intStructPtr);

            Marshal.FreeHGlobal(intStructPtr);

            //获取函数结构体
            sApiStruct apiStruct = new sApiStruct();
            Marshal.PtrToStructure(apiStructPtr, apiStruct);
            //获取所有函数指针
            initAllApi(apiStruct);
        }

        `   #region API初始化

        /// <summary>
        /// 所有的API
        /// </summary>
        /// <returns></returns>
        public static ApiStruct API = new ApiStruct();

        //获取所有函数指针
        private static void initAllApi(sApiStruct apiStruct) {
            API.CommonDelete = Marshal.GetDelegateForFunctionPointer<fnCommonDelete>(apiStruct.CommonDelete);
            API.CreateVec3 = Marshal.GetDelegateForFunctionPointer<fnCreateVec3>(apiStruct.CreateVec3);
            API.CreateTransform = Marshal.GetDelegateForFunctionPointer<fnCreateTransform>(apiStruct.CreateTransform);
            API.DestroyVec4 = Marshal.GetDelegateForFunctionPointer<fnDestroyVec4>(apiStruct.DestroyVec4);
            API.DestroyVec3 = Marshal.GetDelegateForFunctionPointer<fnDestroyVec3>(apiStruct.DestroyVec3);
            API.DestroyTransform = Marshal.GetDelegateForFunctionPointer<fnDestroyTransform>(apiStruct.DestroyTransform);
            API.CreatePhysicsWorld = Marshal.GetDelegateForFunctionPointer<fnCreatePhysicsWorld>(apiStruct.CreatePhysicsWorld);
            API.DestroyPhysicsWorld = Marshal.GetDelegateForFunctionPointer<fnDestroyPhysicsWorld>(apiStruct.DestroyPhysicsWorld);
            API.StepPhysicsWorld = Marshal.GetDelegateForFunctionPointer<fnStepPhysicsWorld>(apiStruct.StepPhysicsWorld);
            API.SetPhysicsWorldGravity = Marshal.GetDelegateForFunctionPointer<fnSetPhysicsWorldGravity>(apiStruct.SetPhysicsWorldGravity);
            API.ReadPhysicsWorldBodys = Marshal.GetDelegateForFunctionPointer<fnReadPhysicsWorldBodys>(apiStruct.ReadPhysicsWorldBodys);
            API.CreateRigdBody = Marshal.GetDelegateForFunctionPointer<fnCreateRigdBody>(apiStruct.CreateRigdBody);
            API.ActiveRigdBody = Marshal.GetDelegateForFunctionPointer<fnActiveRigdBody>(apiStruct.ActiveRigdBody);
            API.DeactiveRigdBody = Marshal.GetDelegateForFunctionPointer<fnDeactiveRigdBody>(apiStruct.DeactiveRigdBody);
            API.SetRigdBodyMass = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyMass>(apiStruct.SetRigdBodyMass);
            API.SetRigdBodyFriction = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyFriction>(apiStruct.SetRigdBodyFriction);
            API.SetRigdBodyRestitution = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyRestitution>(apiStruct.SetRigdBodyRestitution);
            API.SetRigdBodyCenterOfMass = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyCenterOfMass>(apiStruct.SetRigdBodyCenterOfMass);
            API.SetRigdBodyPosition = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyPosition>(apiStruct.SetRigdBodyPosition);
            API.SetRigdBodyPositionAndRotation = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyPositionAndRotation>(apiStruct.SetRigdBodyPositionAndRotation);
            API.SetRigdBodyMotionType = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyMotionType>(apiStruct.SetRigdBodyMotionType);
            API.SetRigdBodyGravityFactor = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyGravityFactor>(apiStruct.SetRigdBodyGravityFactor);
            API.DestroyRigdBody = Marshal.GetDelegateForFunctionPointer<fnDestroyRigdBody>(apiStruct.DestroyRigdBody);
            API.GetConvexHullResultTriangles = Marshal.GetDelegateForFunctionPointer<fnGetConvexHullResultTriangles>(apiStruct.GetConvexHullResultTriangles);
            API.GetConvexHullResultVertices = Marshal.GetDelegateForFunctionPointer<fnGetConvexHullResultVertices>(apiStruct.GetConvexHullResultVertices);
            API.Build3DPointsConvexHull = Marshal.GetDelegateForFunctionPointer<fnBuild3DPointsConvexHull>(apiStruct.Build3DPointsConvexHull);
            API.Build3DFromPlaneConvexHull = Marshal.GetDelegateForFunctionPointer<fnBuild3DFromPlaneConvexHull>(apiStruct.Build3DFromPlaneConvexHull);
            API.ComputeShapeVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeShapeVolumeMassProperties>(apiStruct.ComputeShapeVolumeMassProperties);
            API.ComputeBoxSurfaceMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeBoxSurfaceMassProperties>(apiStruct.ComputeBoxSurfaceMassProperties);
            API.ComputeBoxVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeBoxVolumeMassProperties>(apiStruct.ComputeBoxVolumeMassProperties);
            API.ComputeCapsuleVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeCapsuleVolumeMassProperties>(apiStruct.ComputeCapsuleVolumeMassProperties);
            API.ComputeCylinderVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeCylinderVolumeMassProperties>(apiStruct.ComputeCylinderVolumeMassProperties);
            API.ComputeCapsuleVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeCapsuleVolumeMassProperties>(apiStruct.ComputeCapsuleVolumeMassProperties);
            API.ComputeSphereVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeSphereVolumeMassProperties>(apiStruct.ComputeSphereVolumeMassProperties);
            API.ComputeSphereSurfaceMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeSphereSurfaceMassProperties>(apiStruct.ComputeSphereSurfaceMassProperties);
            API.ComputeTriangleSurfaceMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeTriangleSurfaceMassProperties>(apiStruct.ComputeTriangleSurfaceMassProperties);
            API.CreateBoxShape = Marshal.GetDelegateForFunctionPointer<fnCreateBoxShape>(apiStruct.CreateBoxShape);
            API.CreateSphereShape = Marshal.GetDelegateForFunctionPointer<fnCreateSphereShape>(apiStruct.CreateSphereShape);
            API.CreateCapsuleShape = Marshal.GetDelegateForFunctionPointer<fnCreateCapsuleShape>(apiStruct.CreateCapsuleShape);
            API.CreateTriangleShape = Marshal.GetDelegateForFunctionPointer<fnCreateTriangleShape>(apiStruct.CreateTriangleShape);
            API.CreateCylindeShape = Marshal.GetDelegateForFunctionPointer<fnCreateCylindeShape>(apiStruct.CreateCylindeShape);
            API.CreateConvexVerticesShape = Marshal.GetDelegateForFunctionPointer<fnCreateConvexVerticesShape>(apiStruct.CreateConvexVerticesShape);
            API.CreateConvexVerticesShapeByConvexHullResult = Marshal.GetDelegateForFunctionPointer<fnCreateConvexVerticesShapeByConvexHullResult>(apiStruct.CreateConvexVerticesShapeByConvexHullResult);
            API.CreateConvexTranslateShape = Marshal.GetDelegateForFunctionPointer<fnCreateConvexTranslateShape>(apiStruct.CreateConvexTranslateShape);
            API.CreateConvexTransformShape = Marshal.GetDelegateForFunctionPointer<fnCreateConvexTransformShape>(apiStruct.CreateConvexTransformShape);
            API.CreateListShape = Marshal.GetDelegateForFunctionPointer<fnCreateListShape>(apiStruct.CreateListShape);
            API.CreateStaticCompoundShape = Marshal.GetDelegateForFunctionPointer<fnCreateStaticCompoundShape>(apiStruct.CreateStaticCompoundShape);
            API.StaticCompoundShapeSetInstanceEnabled = Marshal.GetDelegateForFunctionPointer<fnStaticCompoundShapeSetInstanceEnabled>(apiStruct.StaticCompoundShapeSetInstanceEnabled);
            API.StaticCompoundShapeIsInstanceEnabled = Marshal.GetDelegateForFunctionPointer<fnStaticCompoundShapeIsInstanceEnabled>(apiStruct.StaticCompoundShapeIsInstanceEnabled);
            API.StaticCompoundShapeEnableAllInstancesAndShapeKeys = Marshal.GetDelegateForFunctionPointer<fnStaticCompoundShapeEnableAllInstancesAndShapeKeys>(apiStruct.StaticCompoundShapeEnableAllInstancesAndShapeKeys);
            API.DestroyShape = Marshal.GetDelegateForFunctionPointer<fnDestroyShape>(apiStruct.DestroyShape);
        }

        #endregion

        #region 函数定义

        public struct ApiStruct {
            public fnCommonDelete CommonDelete;
            public fnCreateVec3 CreateVec3;
            public fnCreateTransform CreateTransform;
            public fnCreateVec4 CreateVec4;
            public fnDestroyVec4 DestroyVec4;
            public fnDestroyVec3 DestroyVec3;
            public fnDestroyTransform DestroyTransform;
            public fnCreatePhysicsWorld CreatePhysicsWorld;
            public fnDestroyPhysicsWorld DestroyPhysicsWorld;
            public fnStepPhysicsWorld StepPhysicsWorld;
            public fnSetPhysicsWorldGravity SetPhysicsWorldGravity;
            public fnReadPhysicsWorldBodys ReadPhysicsWorldBodys;
            public fnCreateRigdBody CreateRigdBody;
            public fnActiveRigdBody ActiveRigdBody;
            public fnDeactiveRigdBody DeactiveRigdBody;
            public fnSetRigdBodyMass SetRigdBodyMass;
            public fnSetRigdBodyFriction SetRigdBodyFriction;
            public fnSetRigdBodyRestitution SetRigdBodyRestitution;
            public fnSetRigdBodyCenterOfMass SetRigdBodyCenterOfMass;
            public fnSetRigdBodyAngularDamping SetRigdBodyAngularDamping;
            public fnSetRigdBodyLinearDampin SetRigdBodyLinearDampin;
            public fnSetRigdBodyPosition SetRigdBodyPosition;
            public fnSetRigdBodyPositionAndRotation SetRigdBodyPositionAndRotation;
            public fnSetRigdBodyMotionType SetRigdBodyMotionType;
	        public fnSetRigdBodyGravityFactor SetRigdBodyGravityFactor;
            public fnGetConvexHullResultTriangles GetConvexHullResultTriangles;
            public fnGetConvexHullResultVertices GetConvexHullResultVertices;
            public fnBuild3DPointsConvexHull Build3DPointsConvexHull;
            public fnBuild3DFromPlaneConvexHull Build3DFromPlaneConvexHull;
            public fnDestroyRigdBody DestroyRigdBody;
            public fnComputeShapeVolumeMassProperties ComputeShapeVolumeMassProperties;
            public fnComputeBoxSurfaceMassProperties ComputeBoxSurfaceMassProperties;
            public fnComputeBoxVolumeMassProperties ComputeBoxVolumeMassProperties;
            public fnComputeCapsuleVolumeMassProperties ComputeCapsuleVolumeMassProperties;
            public fnComputeCylinderVolumeMassProperties ComputeCylinderVolumeMassProperties;
            public fnComputeSphereVolumeMassProperties ComputeSphereVolumeMassProperties;
            public fnComputeSphereSurfaceMassProperties ComputeSphereSurfaceMassProperties;
            public fnComputeTriangleSurfaceMassProperties ComputeTriangleSurfaceMassProperties;
            public fnCreateBoxShape CreateBoxShape;
            public fnCreateSphereShape CreateSphereShape;
            public fnCreateCapsuleShape CreateCapsuleShape;
            public fnCreateCylindeShape CreateCylindeShape;
            public fnCreateTriangleShape CreateTriangleShape;
            public fnCreateConvexVerticesShape CreateConvexVerticesShape;
            public fnCreateConvexVerticesShapeByConvexHullResult CreateConvexVerticesShapeByConvexHullResult;
            public fnCreateConvexTranslateShape CreateConvexTranslateShape;
            public fnCreateConvexTransformShape CreateConvexTransformShape;
            public fnCreateListShape CreateListShape;
            public fnCreateStaticCompoundShape CreateStaticCompoundShape;
            public fnStaticCompoundShapeSetInstanceEnabled StaticCompoundShapeSetInstanceEnabled;
            public fnStaticCompoundShapeIsInstanceEnabled StaticCompoundShapeIsInstanceEnabled;
            public fnStaticCompoundShapeEnableAllInstancesAndShapeKeys StaticCompoundShapeEnableAllInstancesAndShapeKeys;
            public fnDestroyShape DestroyShape;
        };

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr fnCreateVec3(float x, float y, float z);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr fnCreateVec4(float x, float y, float z, float w);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void  fnCommonDelete(IntPtr ptr);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* spTransform */ fnCreateTransform(float px, float py, float pz, float rx, float ry, float rz, float rw, float sx, float sy, float sz);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnDestroyVec4(IntPtr ptr);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnDestroyVec3(IntPtr ptr);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnDestroyTransform(IntPtr /* spTransform */ ptr);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsRigdbody* */  fnCreateRigdBody(
            IntPtr /* sPhysicsRigdbody* */ world, 
            IntPtr /* sPhysicsShape* */ shape, IntPtr /* spVec3 */ position,
            int motionType, int qualityType, float friction, float restitution, float mass, int active,
            float gravityFactor, float linearDamping, float angularDamping,
            IntPtr /* spVec3 */ linearVelocity, 
            IntPtr /* spVec3 */ angularVelocity, 
            IntPtr /* spVec3 */ massProperties);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnActiveRigdBody(IntPtr /* sPhysicsRigdbody* */ body);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnDeactiveRigdBody(IntPtr /* sPhysicsRigdbody* */ body);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetRigdBodyMass(IntPtr /* sPhysicsRigdbody* */ body, float mass);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetRigdBodyFriction(IntPtr /* sPhysicsRigdbody* */ body, float friction);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetRigdBodyRestitution(IntPtr /* sPhysicsRigdbody* */ body, float restitution);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetRigdBodyAngularDamping(IntPtr /* sPhysicsRigdbody* */ body, float angularDamping);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetRigdBodyLinearDampin(IntPtr /* sPhysicsRigdbody* */ body, float linearDamping);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetRigdBodyCenterOfMass(IntPtr /* sPhysicsRigdbody* */ body, IntPtr /* spVec3 */ centerOfMass);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetRigdBodyPosition(IntPtr /* sPhysicsRigdbody* */ body, IntPtr /* spVec3 */ pos);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetRigdBodyPositionAndRotation(IntPtr /* sPhysicsRigdbody* */ body, IntPtr /* spVec3 */ pos, IntPtr /* spVec4 */ roate);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetRigdBodyMotionType(IntPtr /* sPhysicsRigdbody* */ body, int newState);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnDestroyRigdBody(IntPtr /* sPhysicsWorld* */ world, IntPtr /* sPhysicsRigdbody* */ body);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetRigdBodyGravityFactor(IntPtr /* sPhysicsRigdbody* */ body, float gravityFactor);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnGetConvexHullResultTriangles(IntPtr /* sConvexHullResult* */ result, IntPtr /* float* */ trianglesBuffer, int count);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnGetConvexHullResultVertices(IntPtr /* sConvexHullResult* */ result, IntPtr /* float* */ pointsBuffer, int numPoints);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sConvexHullResult* */ fnBuild3DPointsConvexHull (IntPtr /* float* */ points, int numPoints);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sConvexHullResult* */ fnBuild3DFromPlaneConvexHull(IntPtr /* float* */ panels, int numPanels);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsRigdbodyMassProperties* */ fnComputeShapeVolumeMassProperties(IntPtr /* sPhysicsShape* */ shape, float mass);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsRigdbodyMassProperties* */ fnComputeBoxSurfaceMassProperties(IntPtr /* spVec4 */ halfExtents, float mass, float surfaceThickness);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsRigdbodyMassProperties* */ fnComputeBoxVolumeMassProperties(IntPtr /* spVec4 */ halfExtents, float mass);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsRigdbodyMassProperties* */ fnComputeCapsuleVolumeMassProperties(IntPtr /* spVec4 */ startAxis, IntPtr /* spVec4 */ endAxis, float radius, float mass);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsRigdbodyMassProperties* */ fnComputeCylinderVolumeMassProperties(IntPtr /* spVec4 */ startAxis, IntPtr /* spVec4 */ endAxis, float radius, float mass);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsRigdbodyMassProperties* */ fnComputeSphereVolumeMassProperties(float radius, float sphereMass);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsRigdbodyMassProperties* */ fnComputeSphereSurfaceMassProperties(float radius, float mass, float surfaceThickness);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsRigdbodyMassProperties* */ fnComputeTriangleSurfaceMassProperties(IntPtr /* spVec4 */ v0, IntPtr /* spVec4 */ v1, IntPtr /* spVec4 */ v2, float mass, float surfaceThickness);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsShape* */ fnCreateBoxShape(IntPtr /* spVec3 */ boxSize, float radius);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsShape* */ fnCreateSphereShape(float radius);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsShape* */ fnCreateCapsuleShape(IntPtr /* spVec3 */ start, IntPtr /* spVec3 */ end, float radius);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsShape* */ fnCreateCylindeShape(IntPtr /* spVec3 */ start, IntPtr /* spVec3 */ end, float radius, float paddingRadius);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsShape* */ fnCreateTriangleShape(IntPtr /* spVec3 */ v0, IntPtr /* spVec3 */ v1, IntPtr /* spVec3 */ v2);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsShape* */ fnCreateConvexVerticesShape(IntPtr /* float* */ vertices, int numVertices, float convexRadius);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr fnCreateConvexVerticesShapeByConvexHullResult(IntPtr /* sConvexHullResult* */ result, float convexRadius);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsShape* */ fnCreateConvexTranslateShape(IntPtr /* sPhysicsShape* */ child, IntPtr /* spVec3 */ translation);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsShape* */ fnCreateConvexTransformShape(IntPtr /* sPhysicsShape* */ child, IntPtr /* spTransform */ transform);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsShape* */ fnCreateListShape(IntPtr /* sPhysicsShape* */ childs, int childCount);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsShape* */ fnCreateStaticCompoundShape(IntPtr /* sPhysicsShape* */ childs, IntPtr /* spTransform* */ transforms, int childCount);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnStaticCompoundShapeSetInstanceEnabled(IntPtr /* sPhysicsShape* */ pStaticCompoundShape, int id, int enabled);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int fnStaticCompoundShapeIsInstanceEnabled(IntPtr /* sPhysicsShape* */ pStaticCompoundShape, int id);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnStaticCompoundShapeEnableAllInstancesAndShapeKeys(IntPtr /* sPhysicsShape* */ pStaticCompoundShape);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnDestroyShape(IntPtr /* sPhysicsShape* */ s);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr /* sPhysicsRigdbody* */  fnCreatePhysicsWorld(IntPtr /* spVec3 */ gravity, int solverIterationCount, float broadPhaseWorldSize, float collisionTolerance);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnDestroyPhysicsWorld(IntPtr /* sPhysicsRigdbody* */ world);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]        
        public delegate void fnStepPhysicsWorld(IntPtr /* sPhysicsRigdbody* */ world, float timestep);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void fnSetPhysicsWorldGravity(IntPtr /* sPhysicsRigdbody* */ world, IntPtr /* spVec3 */ gravity);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int fnReadPhysicsWorldBodys(IntPtr /* sPhysicsRigdbody* */ world, IntPtr /* float* */ buffer, int count);

        #endregion

        #region 结构体和枚举定义

        [StructLayout(LayoutKind.Sequential)]
        struct sConvexHullResult
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8, ArraySubType = UnmanagedType.R4)]
            float[] aabb; //min(4) max(4) 
            int verticesCount;
            int trianglesCount;
        };

        #endregion
    }
}