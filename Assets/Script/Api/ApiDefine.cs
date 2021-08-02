using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace PhyicsRT
{
  #region 函数定义

  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnTestAssert();
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateVec3(float x, float y, float z);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateVec4(float x, float y, float z, float w);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnCommonDelete(IntPtr ptr);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateTransform(float px, float py, float pz, float rx, float ry, float rz, float rw, float sx, float sy, float sz);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnDestroyVec4(IntPtr ptr);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnDestroyVec3(IntPtr ptr);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnDestroyTransform(IntPtr ptr);

  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateRigdBody(
      IntPtr world,
      IntPtr shape, IntPtr position, IntPtr rot,
      int motionType, int qualityType, float friction, float restitution, float mass, int active, int layer,
      float gravityFactor, float linearDamping, float angularDamping,
      IntPtr linearVelocity,
      IntPtr angularVelocity,
      IntPtr massProperties);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnActiveRigdBody(IntPtr body);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnDeactiveRigdBody(IntPtr body);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyMass(IntPtr body, float mass);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyFriction(IntPtr body, float friction);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyRestitution(IntPtr body, float restitution);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyAngularDamping(IntPtr body, float angularDamping);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyLinearDampin(IntPtr body, float linearDamping);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyCenterOfMass(IntPtr body, IntPtr centerOfMass);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyPosition(IntPtr body, IntPtr pos);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyPositionAndRotation(IntPtr body, IntPtr pos, IntPtr roate);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyMotionType(IntPtr body, int newState);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnDestroyRigdBody(IntPtr body);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyGravityFactor(IntPtr body, float gravityFactor);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnGetConvexHullResultTriangles(IntPtr result, IntPtr trianglesBuffer, int count);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnGetConvexHullResultVertices(IntPtr result, IntPtr pointsBuffer, int numPoints);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnBuild3DPointsConvexHull(IntPtr points, int numPoints);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnBuild3DFromPlaneConvexHull(IntPtr panels, int numPanels);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnComputeShapeVolumeMassProperties(IntPtr shape, float mass);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnComputeBoxSurfaceMassProperties(IntPtr halfExtents, float mass, float surfaceThickness);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnComputeBoxVolumeMassProperties(IntPtr halfExtents, float mass);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnComputeCapsuleVolumeMassProperties(IntPtr startAxis, IntPtr endAxis, float radius, float mass);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnComputeCylinderVolumeMassProperties(IntPtr startAxis, IntPtr endAxis, float radius, float mass);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnComputeSphereVolumeMassProperties(float radius, float sphereMass);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnComputeSphereSurfaceMassProperties(float radius, float mass, float surfaceThickness);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnComputeTriangleSurfaceMassProperties(IntPtr v0, IntPtr v1, IntPtr v2, float mass, float surfaceThickness);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateBoxShape(IntPtr boxSize, float radius);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateSphereShape(float radius);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateCapsuleShape(IntPtr start, IntPtr end, float radius);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateCylindeShape(IntPtr start, IntPtr end, float radius, float paddingRadius);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateTriangleShape(IntPtr v0, IntPtr v1, IntPtr v2);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateConvexVerticesShape(IntPtr vertices, int numVertices, float convexRadius);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateConvexVerticesShapeByConvexHullResult(IntPtr result, float convexRadius);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateConvexTranslateShape(IntPtr child, IntPtr translation);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateConvexTransformShape(IntPtr child, IntPtr transform);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateListShape(IntPtr childs, int childCount);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreateStaticCompoundShape(IntPtr childs, IntPtr transforms, int childCount);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnStaticCompoundShapeSetInstanceEnabled(IntPtr pStaticCompoundShape, int id, int enabled);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate int fnStaticCompoundShapeIsInstanceEnabled(IntPtr pStaticCompoundShape, int id);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnStaticCompoundShapeEnableAllInstancesAndShapeKeys(IntPtr pStaticCompoundShape);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnDestroyShape(IntPtr s);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate IntPtr fnCreatePhysicsWorld(IntPtr gravity,
      int solverIterationCount, float broadPhaseWorldSize, float collisionTolerance,
      bool bContinuous, bool bVisualDebugger, uint layerMask, IntPtr layerToMask);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnDestroyPhysicsWorld(IntPtr world);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnStepPhysicsWorld(IntPtr world, float timestep);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetPhysicsWorldGravity(IntPtr world, IntPtr gravity);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate int fnReadPhysicsWorldBodys(IntPtr world, IntPtr buffer, int count);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetPhysicsWorldCollisionLayerMasks(IntPtr world, uint layerId, uint toMask, int enable, int forceUpdate);
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void fnSetRigdBodyLayer(IntPtr body, int layer);

  #endregion

  #region 异常

  public class ApiNotFoundException : Exception
  {
    public ApiNotFoundException(string name) : base(name + " api not found") { }
  }
  public class ApiException : Exception
  {
    public ApiException(string msg) : base(msg) { }
  }

  #endregion

  public class ApiStruct
  {
    //获取所有函数指针
    internal void initAll(IntPtr apiArrayPtr, int len)
    {
      int i = 0;
      IntPtr[] apiArray = new IntPtr[len];
      Marshal.Copy(apiArrayPtr, apiArray, 0, len);

      _CommonDelete = Marshal.GetDelegateForFunctionPointer<fnCommonDelete>(apiArray[i++]);
      _CreateVec3 = Marshal.GetDelegateForFunctionPointer<fnCreateVec3>(apiArray[i++]);
      _CreateTransform = Marshal.GetDelegateForFunctionPointer<fnCreateTransform>(apiArray[i++]);
      _CreateVec4 = Marshal.GetDelegateForFunctionPointer<fnCreateVec4>(apiArray[i++]);
      _DestroyVec4 = Marshal.GetDelegateForFunctionPointer<fnDestroyVec4>(apiArray[i++]);
      _DestroyVec3 = Marshal.GetDelegateForFunctionPointer<fnDestroyVec3>(apiArray[i++]);
      _DestroyTransform = Marshal.GetDelegateForFunctionPointer<fnDestroyTransform>(apiArray[i++]);
      _CreatePhysicsWorld = Marshal.GetDelegateForFunctionPointer<fnCreatePhysicsWorld>(apiArray[i++]);
      _DestroyPhysicsWorld = Marshal.GetDelegateForFunctionPointer<fnDestroyPhysicsWorld>(apiArray[i++]);
      _StepPhysicsWorld = Marshal.GetDelegateForFunctionPointer<fnStepPhysicsWorld>(apiArray[i++]);
      _SetPhysicsWorldGravity = Marshal.GetDelegateForFunctionPointer<fnSetPhysicsWorldGravity>(apiArray[i++]);
      _ReadPhysicsWorldBodys = Marshal.GetDelegateForFunctionPointer<fnReadPhysicsWorldBodys>(apiArray[i++]);
      _CreateRigdBody = Marshal.GetDelegateForFunctionPointer<fnCreateRigdBody>(apiArray[i++]);
      _ActiveRigdBody = Marshal.GetDelegateForFunctionPointer<fnActiveRigdBody>(apiArray[i++]);
      _DeactiveRigdBody = Marshal.GetDelegateForFunctionPointer<fnDeactiveRigdBody>(apiArray[i++]);
      _SetRigdBodyMass = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyMass>(apiArray[i++]);
      _SetRigdBodyFriction = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyFriction>(apiArray[i++]);
      _SetRigdBodyRestitution = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyRestitution>(apiArray[i++]);
      _SetRigdBodyCenterOfMass = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyCenterOfMass>(apiArray[i++]);
      _SetRigdBodyPosition = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyPosition>(apiArray[i++]);
      _SetRigdBodyPositionAndRotation = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyPositionAndRotation>(apiArray[i++]);
      _SetRigdBodyAngularDamping = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyAngularDamping>(apiArray[i++]);
      _SetRigdBodyLinearDampin = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyLinearDampin>(apiArray[i++]);
      _SetRigdBodyMotionType = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyMotionType>(apiArray[i++]);
      _SetRigdBodyGravityFactor = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyGravityFactor>(apiArray[i++]);
      _GetConvexHullResultTriangles = Marshal.GetDelegateForFunctionPointer<fnGetConvexHullResultTriangles>(apiArray[i++]);
      _GetConvexHullResultVertices = Marshal.GetDelegateForFunctionPointer<fnGetConvexHullResultVertices>(apiArray[i++]);
      _Build3DPointsConvexHull = Marshal.GetDelegateForFunctionPointer<fnBuild3DPointsConvexHull>(apiArray[i++]);
      _Build3DFromPlaneConvexHull = Marshal.GetDelegateForFunctionPointer<fnBuild3DFromPlaneConvexHull>(apiArray[i++]);
      _DestroyRigdBody = Marshal.GetDelegateForFunctionPointer<fnDestroyRigdBody>(apiArray[i++]);
      _ComputeShapeVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeShapeVolumeMassProperties>(apiArray[i++]);
      _ComputeBoxSurfaceMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeBoxSurfaceMassProperties>(apiArray[i++]);
      _ComputeBoxVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeBoxVolumeMassProperties>(apiArray[i++]);
      _ComputeCapsuleVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeCapsuleVolumeMassProperties>(apiArray[i++]);
      _ComputeCylinderVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeCylinderVolumeMassProperties>(apiArray[i++]);
      _ComputeSphereVolumeMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeSphereVolumeMassProperties>(apiArray[i++]);
      _ComputeSphereSurfaceMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeSphereSurfaceMassProperties>(apiArray[i++]);
      _ComputeTriangleSurfaceMassProperties = Marshal.GetDelegateForFunctionPointer<fnComputeTriangleSurfaceMassProperties>(apiArray[i++]);
      _CreateBoxShape = Marshal.GetDelegateForFunctionPointer<fnCreateBoxShape>(apiArray[i++]);
      _CreateSphereShape = Marshal.GetDelegateForFunctionPointer<fnCreateSphereShape>(apiArray[i++]);
      _CreateCapsuleShape = Marshal.GetDelegateForFunctionPointer<fnCreateCapsuleShape>(apiArray[i++]);
      _CreateCylindeShape = Marshal.GetDelegateForFunctionPointer<fnCreateCylindeShape>(apiArray[i++]);
      _CreateTriangleShape = Marshal.GetDelegateForFunctionPointer<fnCreateTriangleShape>(apiArray[i++]);
      _CreateConvexVerticesShape = Marshal.GetDelegateForFunctionPointer<fnCreateConvexVerticesShape>(apiArray[i++]);
      _CreateConvexVerticesShapeByConvexHullResult = Marshal.GetDelegateForFunctionPointer<fnCreateConvexVerticesShapeByConvexHullResult>(apiArray[i++]);
      _CreateConvexTranslateShape = Marshal.GetDelegateForFunctionPointer<fnCreateConvexTranslateShape>(apiArray[i++]);
      _CreateConvexTransformShape = Marshal.GetDelegateForFunctionPointer<fnCreateConvexTransformShape>(apiArray[i++]);
      _CreateListShape = Marshal.GetDelegateForFunctionPointer<fnCreateListShape>(apiArray[i++]);
      _CreateStaticCompoundShape = Marshal.GetDelegateForFunctionPointer<fnCreateStaticCompoundShape>(apiArray[i++]);
      _StaticCompoundShapeSetInstanceEnabled = Marshal.GetDelegateForFunctionPointer<fnStaticCompoundShapeSetInstanceEnabled>(apiArray[i++]);
      _StaticCompoundShapeIsInstanceEnabled = Marshal.GetDelegateForFunctionPointer<fnStaticCompoundShapeIsInstanceEnabled>(apiArray[i++]);
      _StaticCompoundShapeEnableAllInstancesAndShapeKeys = Marshal.GetDelegateForFunctionPointer<fnStaticCompoundShapeEnableAllInstancesAndShapeKeys>(apiArray[i++]);
      _DestroyShape = Marshal.GetDelegateForFunctionPointer<fnDestroyShape>(apiArray[i++]);
	    _TestAssert = Marshal.GetDelegateForFunctionPointer<fnTestAssert>(apiArray[i++]);
	    _SetRigdBodyLayer = Marshal.GetDelegateForFunctionPointer<fnSetRigdBodyLayer>(apiArray[i++]);
	    _SetPhysicsWorldCollisionLayerMasks = Marshal.GetDelegateForFunctionPointer<fnSetPhysicsWorldCollisionLayerMasks>(apiArray[i++]);
    }

    private fnTestAssert _TestAssert;
    private fnCommonDelete _CommonDelete;
    private fnCreateVec3 _CreateVec3;
    private fnCreateTransform _CreateTransform;
    private fnCreateVec4 _CreateVec4;
    private fnDestroyVec4 _DestroyVec4;
    private fnDestroyVec3 _DestroyVec3;
    private fnDestroyTransform _DestroyTransform;
    private fnCreatePhysicsWorld _CreatePhysicsWorld;
    private fnDestroyPhysicsWorld _DestroyPhysicsWorld;
    private fnStepPhysicsWorld _StepPhysicsWorld;
    private fnSetPhysicsWorldGravity _SetPhysicsWorldGravity;
    private fnReadPhysicsWorldBodys _ReadPhysicsWorldBodys;
    private fnCreateRigdBody _CreateRigdBody;
    private fnActiveRigdBody _ActiveRigdBody;
    private fnDeactiveRigdBody _DeactiveRigdBody;
    private fnSetRigdBodyMass _SetRigdBodyMass;
    private fnSetRigdBodyFriction _SetRigdBodyFriction;
    private fnSetRigdBodyRestitution _SetRigdBodyRestitution;
    private fnSetRigdBodyCenterOfMass _SetRigdBodyCenterOfMass;
    private fnSetRigdBodyAngularDamping _SetRigdBodyAngularDamping;
    private fnSetRigdBodyLinearDampin _SetRigdBodyLinearDampin;
    private fnSetRigdBodyPosition _SetRigdBodyPosition;
    private fnSetRigdBodyPositionAndRotation _SetRigdBodyPositionAndRotation;
    private fnSetRigdBodyMotionType _SetRigdBodyMotionType;
    private fnSetRigdBodyGravityFactor _SetRigdBodyGravityFactor;
    private fnGetConvexHullResultTriangles _GetConvexHullResultTriangles;
    private fnGetConvexHullResultVertices _GetConvexHullResultVertices;
    private fnBuild3DPointsConvexHull _Build3DPointsConvexHull;
    private fnBuild3DFromPlaneConvexHull _Build3DFromPlaneConvexHull;
    private fnDestroyRigdBody _DestroyRigdBody;
    private fnComputeShapeVolumeMassProperties _ComputeShapeVolumeMassProperties;
    private fnComputeBoxSurfaceMassProperties _ComputeBoxSurfaceMassProperties;
    private fnComputeBoxVolumeMassProperties _ComputeBoxVolumeMassProperties;
    private fnComputeCapsuleVolumeMassProperties _ComputeCapsuleVolumeMassProperties;
    private fnComputeCylinderVolumeMassProperties _ComputeCylinderVolumeMassProperties;
    private fnComputeSphereVolumeMassProperties _ComputeSphereVolumeMassProperties;
    private fnComputeSphereSurfaceMassProperties _ComputeSphereSurfaceMassProperties;
    private fnComputeTriangleSurfaceMassProperties _ComputeTriangleSurfaceMassProperties;
    private fnCreateBoxShape _CreateBoxShape;
    private fnCreateSphereShape _CreateSphereShape;
    private fnCreateCapsuleShape _CreateCapsuleShape;
    private fnCreateCylindeShape _CreateCylindeShape;
    private fnCreateTriangleShape _CreateTriangleShape;
    private fnCreateConvexVerticesShape _CreateConvexVerticesShape;
    private fnCreateConvexVerticesShapeByConvexHullResult _CreateConvexVerticesShapeByConvexHullResult;
    private fnCreateConvexTranslateShape _CreateConvexTranslateShape;
    private fnCreateConvexTransformShape _CreateConvexTransformShape;
    private fnCreateListShape _CreateListShape;
    private fnCreateStaticCompoundShape _CreateStaticCompoundShape;
    private fnStaticCompoundShapeSetInstanceEnabled _StaticCompoundShapeSetInstanceEnabled;
    private fnStaticCompoundShapeIsInstanceEnabled _StaticCompoundShapeIsInstanceEnabled;
    private fnStaticCompoundShapeEnableAllInstancesAndShapeKeys _StaticCompoundShapeEnableAllInstancesAndShapeKeys;
    private fnDestroyShape _DestroyShape;
    private fnSetPhysicsWorldCollisionLayerMasks _SetPhysicsWorldCollisionLayerMasks;
    private fnSetRigdBodyLayer _SetRigdBodyLayer;

    public void CommonDelete(IntPtr ptr)
    {
      if (_CommonDelete == null)
        throw new ApiNotFoundException("CommonDelete");
      if (ptr == IntPtr.Zero)
        throw new ApiException("ptr is nullptr");

      _CommonDelete(ptr);
    }

    public IntPtr CreateVec3(float x, float y, float z){
      if (_CreateVec3 == null)
        throw new ApiNotFoundException("CreateVec3");
      return _CreateVec3(x, y, z);
    }
    public IntPtr CreateVec4(float x, float y, float z, float w){
      if (_CreateVec4 == null)
        throw new ApiNotFoundException("CreateVec4");
      return _CreateVec4(x, y, z, w);
    }
    public IntPtr CreateTransform(float px, float py, float pz, float rx, float ry, float rz, float rw, float sx, float sy, float sz) {
      if (_CreateTransform == null)
        throw new ApiNotFoundException("CreateTransform");
      return _CreateTransform( px, py, pz, rx, ry, rz, rw, sx, sy, sz);
    }
    public void DestroyVec4(IntPtr ptr)
    {
      if (_DestroyVec4 == null)
        throw new ApiNotFoundException("DestroyVec4");
      _DestroyVec4(ptr);
    }
    public void DestroyVec3(IntPtr ptr)
    {
      if (_DestroyVec3 == null)
        throw new ApiNotFoundException("DestroyVec3");
      _DestroyVec3(ptr);
    }
    public void ActiveRigdBody(IntPtr ptr)
    {
      if (_ActiveRigdBody== null)
        throw new ApiNotFoundException("ActiveRigdBody");
      _ActiveRigdBody(ptr);
    }
    public void DeactiveRigdBody(IntPtr ptr)
    {
      if (_DeactiveRigdBody == null)
        throw new ApiNotFoundException("DeactiveRigdBody");
      _DeactiveRigdBody(ptr);
    }
    public void DestroyTransform(IntPtr ptr)
    {
      if (_DestroyTransform == null)
        throw new ApiNotFoundException("DestroyTransform");
      _DestroyTransform(ptr);
    }
    public IntPtr CreateRigdBody(IntPtr world, IntPtr shape, IntPtr position, IntPtr rot, int motionType, int qualityType, float friction, float restitution, float mass, int active, int layer, float gravityFactor, float linearDamping, float angularDamping, IntPtr linearVelocity, IntPtr angularVelocity, IntPtr massProperties)
    {
      if (_CreateRigdBody == null)
        throw new ApiNotFoundException("CreateRigdBody");

      var rs = _CreateRigdBody(world, shape, position, rot, motionType, qualityType, friction, restitution, mass, active, layer, gravityFactor, linearDamping, angularDamping, linearVelocity, angularVelocity, massProperties);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public void SetRigdBodyMass(IntPtr body, float mass)
    {
      if (_SetRigdBodyMass == null)
        throw new ApiNotFoundException("SetRigdBodyMass");

      _SetRigdBodyMass(body, mass);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetRigdBodyFriction(IntPtr body, float friction)
    {
      if (_SetRigdBodyFriction == null)
        throw new ApiNotFoundException("SetRigdBodyFriction");

      _SetRigdBodyFriction(body, friction);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetRigdBodyRestitution(IntPtr body, float restitution)
    {
      if (_SetRigdBodyFriction == null)
        throw new ApiNotFoundException("SetRigdBodyFriction");

      _SetRigdBodyFriction(body, restitution);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetRigdBodyAngularDamping(IntPtr body, float angularDamping)
    {
      if (_SetRigdBodyAngularDamping == null)
        throw new ApiNotFoundException("SetRigdBodyAngularDamping");

      _SetRigdBodyAngularDamping(body, angularDamping);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetRigdBodyLinearDampin(IntPtr body, float linearDamping)
    {
      if (_SetRigdBodyLinearDampin == null)
        throw new ApiNotFoundException("SetRigdBodyLinearDampin");

      _SetRigdBodyLinearDampin(body, linearDamping);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetRigdBodyCenterOfMass(IntPtr body, IntPtr centerOfMass)
    {
      if (_SetRigdBodyCenterOfMass == null)
        throw new ApiNotFoundException("SetRigdBodyCenterOfMass");

      _SetRigdBodyCenterOfMass(body, centerOfMass);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetRigdBodyPosition(IntPtr body, IntPtr pos)
    {
      if (_SetRigdBodyPosition == null)
        throw new ApiNotFoundException("SetRigdBodyPosition");

      _SetRigdBodyPosition(body, pos);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetRigdBodyPositionAndRotation(IntPtr body, IntPtr pos, IntPtr roate)
    {
      if (_SetRigdBodyPositionAndRotation == null)
        throw new ApiNotFoundException("SetRigdBodyPositionAndRotation");

      _SetRigdBodyPositionAndRotation(body, pos, roate);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetRigdBodyMotionType(IntPtr body, int newState)
    {
      if (_SetRigdBodyMotionType == null)
        throw new ApiNotFoundException("SetRigdBodyMotionType");

      _SetRigdBodyMotionType(body, newState);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetRigdBodyLayer(IntPtr body, int layer) 
    {
      if (_SetRigdBodyLayer == null)
        throw new ApiNotFoundException("SetRigdBodyLayer");

      _SetRigdBodyLayer(body, layer);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void DestroyRigdBody(IntPtr body)
    {
      if (_DestroyRigdBody == null)
        throw new ApiNotFoundException("DestroyRigdBody");

      _DestroyRigdBody(body);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetRigdBodyGravityFactor(IntPtr body, float gravityFactor)
    {
      if (_SetRigdBodyGravityFactor == null)
        throw new ApiNotFoundException("SetRigdBodyGravityFactor");

      _SetRigdBodyGravityFactor(body, gravityFactor);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void GetConvexHullResultTriangles(IntPtr result, IntPtr trianglesBuffer, int count)
    {
      if (_GetConvexHullResultTriangles == null)
        throw new ApiNotFoundException("GetConvexHullResultTriangles");

      _GetConvexHullResultTriangles(result, trianglesBuffer, count);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void GetConvexHullResultVertices(IntPtr result, IntPtr pointsBuffer, int numPoints)
    {
      if (_GetConvexHullResultVertices == null)
        throw new ApiNotFoundException("GetConvexHullResultVertices");

      _GetConvexHullResultVertices(result, pointsBuffer, numPoints);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public IntPtr Build3DPointsConvexHull(IntPtr points, int numPoints)
    {
      if (_Build3DPointsConvexHull == null)
        throw new ApiNotFoundException("Build3DPointsConvexHull");

      var rs = _Build3DPointsConvexHull(points, numPoints);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr Build3DFromPlaneConvexHull(IntPtr panels, int numPanels)
    {
      if (_Build3DFromPlaneConvexHull == null)
        throw new ApiNotFoundException("Build3DFromPlaneConvexHull");

      var rs = _Build3DFromPlaneConvexHull(panels, numPanels);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr ComputeShapeVolumeMassProperties(IntPtr shape, float mass)
    {
      if (_ComputeShapeVolumeMassProperties == null)
        throw new ApiNotFoundException("ComputeShapeVolumeMassProperties");

      var rs = _ComputeShapeVolumeMassProperties(shape, mass);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr ComputeBoxSurfaceMassProperties(IntPtr halfExtents, float mass, float surfaceThickness)
    {
      if (_ComputeBoxSurfaceMassProperties == null)
        throw new ApiNotFoundException("ComputeBoxSurfaceMassProperties");

      var rs = _ComputeBoxSurfaceMassProperties(halfExtents, mass, surfaceThickness);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr ComputeBoxVolumeMassProperties(IntPtr halfExtents, float mass)
    {
      if (_ComputeBoxVolumeMassProperties == null)
        throw new ApiNotFoundException("ComputeBoxVolumeMassProperties");

      var rs = _ComputeBoxVolumeMassProperties(halfExtents, mass);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr ComputeCapsuleVolumeMassProperties(IntPtr startAxis, IntPtr endAxis, float radius, float mass)
    {
      if (_ComputeCapsuleVolumeMassProperties == null)
        throw new ApiNotFoundException("ComputeCapsuleVolumeMassProperties");

      var rs = _ComputeCapsuleVolumeMassProperties(startAxis, endAxis, radius, mass);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr ComputeCylinderVolumeMassProperties(IntPtr startAxis, IntPtr endAxis, float radius, float mass)
    {
      if (_ComputeCylinderVolumeMassProperties == null)
        throw new ApiNotFoundException("ComputeCylinderVolumeMassProperties");

      var rs = _ComputeCylinderVolumeMassProperties(startAxis, endAxis, radius, mass);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr ComputeSphereVolumeMassProperties(float radius, float sphereMass)
    {
      if (_ComputeSphereVolumeMassProperties == null)
        throw new ApiNotFoundException("ComputeSphereVolumeMassProperties");

      var rs = _ComputeSphereVolumeMassProperties(radius, sphereMass);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr ComputeSphereSurfaceMassProperties(float radius, float mass, float surfaceThickness)
    {
      if (_ComputeSphereSurfaceMassProperties == null)
        throw new ApiNotFoundException("ComputeSphereSurfaceMassProperties");

      var rs = _ComputeSphereSurfaceMassProperties(radius, mass, surfaceThickness);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr ComputeTriangleSurfaceMassProperties(IntPtr v0, IntPtr v1, IntPtr v2, float mass, float surfaceThickness)
    {
      if (_ComputeTriangleSurfaceMassProperties == null)
        throw new ApiNotFoundException("ComputeTriangleSurfaceMassProperties");

      var rs = _ComputeTriangleSurfaceMassProperties(v0, v1, v2, mass, surfaceThickness);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateBoxShape(IntPtr boxSize, float radius)
    {
      if (_CreateBoxShape == null)
        throw new ApiNotFoundException("CreateBoxShape");

      var rs = _CreateBoxShape(boxSize, radius);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateSphereShape(float radius)
    {
      if (_CreateSphereShape == null)
        throw new ApiNotFoundException("CreateSphereShape");

      var rs = _CreateSphereShape(radius);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateCapsuleShape(IntPtr start, IntPtr end, float radius)
    {
      if (_CreateCapsuleShape == null)
        throw new ApiNotFoundException("CreateCapsuleShape");

      var rs = _CreateCapsuleShape(start, end, radius);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateCylindeShape(IntPtr start, IntPtr end, float radius, float paddingRadius)
    {
      if (_CreateCylindeShape == null)
        throw new ApiNotFoundException("CreateCylindeShape");

      var rs = _CreateCylindeShape(start, end, radius, paddingRadius);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateTriangleShape(IntPtr v0, IntPtr v1, IntPtr v2)
    {
      if (_CreateTriangleShape == null)
        throw new ApiNotFoundException("CreateTriangleShape");

      var rs = _CreateTriangleShape(v0, v1, v2);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateConvexVerticesShape(IntPtr vertices, int numVertices, float convexRadius)
    {
      if (_CreateConvexVerticesShape == null)
        throw new ApiNotFoundException("CreateConvexVerticesShape");

      var rs = _CreateConvexVerticesShape(vertices, numVertices, convexRadius);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateConvexVerticesShapeByConvexHullResult(IntPtr result, float convexRadius)
    {
      if (_CreateConvexVerticesShapeByConvexHullResult == null)
        throw new ApiNotFoundException("CreateConvexVerticesShapeByConvexHullResult");

      var rs = _CreateConvexVerticesShapeByConvexHullResult(result, convexRadius);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateConvexTranslateShape(IntPtr child, IntPtr translation)
    {
      if (_CreateConvexTranslateShape == null)
        throw new ApiNotFoundException("CreateConvexTranslateShape");

      var rs = _CreateConvexTranslateShape(child, translation);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateConvexTransformShape(IntPtr child, IntPtr transform)
    {
      if (_CreateConvexTransformShape == null)
        throw new ApiNotFoundException("CreateConvexTransformShape");

      var rs = _CreateConvexTransformShape(child, transform);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateListShape(IntPtr childs, int childCount)
    {
      if (_CreateListShape == null)
        throw new ApiNotFoundException("CreateListShape");

      var rs = _CreateListShape(childs, childCount);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public IntPtr CreateStaticCompoundShape(IntPtr childs, IntPtr transforms, int childCount)
    {
      if (_CreateStaticCompoundShape == null)
        throw new ApiNotFoundException("CreateStaticCompoundShape");

      var rs = _CreateStaticCompoundShape(childs, transforms, childCount);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public void StaticCompoundShapeSetInstanceEnabled(IntPtr pStaticCompoundShape, int id, int enabled)
    {
      if (_StaticCompoundShapeSetInstanceEnabled == null)
        throw new ApiNotFoundException("StaticCompoundShapeSetInstanceEnabled");

      _StaticCompoundShapeSetInstanceEnabled(pStaticCompoundShape, id, enabled);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public int StaticCompoundShapeIsInstanceEnabled(IntPtr pStaticCompoundShape, int id)
    {
      if (_StaticCompoundShapeIsInstanceEnabled == null)
        throw new ApiNotFoundException("StaticCompoundShapeIsInstanceEnabled");

      var rs = _StaticCompoundShapeIsInstanceEnabled(pStaticCompoundShape, id);
      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public void StaticCompoundShapeEnableAllInstancesAndShapeKeys(IntPtr pStaticCompoundShape)
    {
      if (_StaticCompoundShapeEnableAllInstancesAndShapeKeys == null)
        throw new ApiNotFoundException("StaticCompoundShapeEnableAllInstancesAndShapeKeys");

      _StaticCompoundShapeEnableAllInstancesAndShapeKeys(pStaticCompoundShape);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void DestroyShape(IntPtr s)
    {
      if (_DestroyShape == null)
        throw new ApiNotFoundException("DestroyShape");

      _DestroyShape(s);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public IntPtr CreatePhysicsWorld(IntPtr gravity, int solverIterationCount, float broadPhaseWorldSize, float collisionTolerance, bool bContinuous, bool bVisualDebugger, uint layerMask, uint[] layerToMask)
    {
      if (_CreatePhysicsWorld == null)
        throw new ApiNotFoundException("CreatePhysicsWorld");

      //uint[] to native
      IntPtr layerToMaskPtr = Marshal.AllocHGlobal(Marshal.SizeOf<int>() * 32);
      IntPtr layerToMaskPtr2 = new IntPtr(layerToMaskPtr.ToInt64());
      for(int i = 0; i < layerToMask.Length && i < 32; i++){
        Marshal.WriteInt32(layerToMaskPtr, (int)layerToMask[i]);
        layerToMaskPtr2 = new IntPtr(layerToMaskPtr2.ToInt64() + i);
      }

      var rs = _CreatePhysicsWorld(gravity, solverIterationCount, broadPhaseWorldSize, collisionTolerance, bContinuous, bVisualDebugger, layerMask, layerToMaskPtr);

      Marshal.FreeHGlobal(layerToMaskPtr);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public void DestroyPhysicsWorld(IntPtr world)
    {
      if (_DestroyPhysicsWorld == null)
        throw new ApiNotFoundException("DestroyPhysicsWorld");

      _DestroyPhysicsWorld(world);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void StepPhysicsWorld(IntPtr world, float timestep)
    {
      if (_StepPhysicsWorld == null)
        throw new ApiNotFoundException("StepPhysicsWorld");
      _StepPhysicsWorld(world, timestep);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetPhysicsWorldGravity(IntPtr world, IntPtr gravity)
    {
      if (_SetPhysicsWorldGravity == null)
        throw new ApiNotFoundException("SetPhysicsWorldGravity");

      _SetPhysicsWorldGravity(world, gravity);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public void SetPhysicsWorldCollisionLayerMasks(IntPtr world, uint layerId, uint toMask, int enable, int forceUpdate) {
      if (_SetPhysicsWorldCollisionLayerMasks == null)
        throw new ApiNotFoundException("SetPhysicsWorldCollisionLayerMasks");

      _SetPhysicsWorldCollisionLayerMasks(world, layerId, toMask, enable, forceUpdate);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }
    public int ReadPhysicsWorldBodys(IntPtr world, IntPtr buffer, int count)
    {
      if (_ReadPhysicsWorldBodys == null)
        throw new ApiNotFoundException("ReadPhysicsWorldBodys");

      var rs = _ReadPhysicsWorldBodys(world, buffer, count);

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);

      return rs;
    }
    public void TestAssert()
    {
      if (_TestAssert == null)
        throw new ApiNotFoundException("TestAssert");

      _TestAssert();

      var exp = PhysicsApi.checkException();
      if (exp != null)
        throw new ApiException(exp);
    }   
  };
}