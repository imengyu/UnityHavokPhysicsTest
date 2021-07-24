using System;
using System.Runtime.InteropServices;

public static class PhysicsApi
{
#if UNITY_IPHONE && !UNITY_EDITOR
	public const string DLL_NNAME = "_Internal";
#else
    public const string DLL_NNAME = "Physics_RT";
#endif

    public const CallingConvention _CallingConvention = CallingConvention.Cdecl;

    //================================================
    // Base
    //================================================

    public delegate void ErrorReportCallback([MarshalAs(UnmanagedType.LPStr)] string msg);

    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void RT_InitializeBaseSystem(IntPtr errorReportCallback);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr RT_InitializeMulitThread();
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr RT_GetMulitThreadJobQueue(IntPtr info);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr RT_GetMulitThreadThreadPool(IntPtr info);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern int RT_GetMulitThreadTotalNumThreadsUsed(IntPtr info);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void RT_DestroyMulitThread(IntPtr info);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void RT_StepWorld(IntPtr physicsWorld, IntPtr info, float timestep);

    //Havok Err Callback
    private static void PhysicsApiErrorCallback(string msg) {
        UnityEngine.Debug.LogError(msg);
    }
    private static IntPtr ptrMulitThread = IntPtr.Zero;
    
    public static IntPtr MulitThreadPtr => ptrMulitThread;
    public static bool MulitThreadEnabled { get;private set; }
    
    public static void PhysicsApiInit() {
        ErrorReportCallback error = PhysicsApiErrorCallback;
        hkPlatformInit();
        RT_InitializeBaseSystem(Marshal.GetFunctionPointerForDelegate(error));

        if(PhysicsOptions.Instance.EnableMultithreaded) {
            ptrMulitThread = RT_InitializeMulitThread();
            MulitThreadEnabled = true;
        }
    }
    public static void PhysicsApiDestroy() {
        
        if(ptrMulitThread != IntPtr.Zero) {
            RT_DestroyMulitThread(ptrMulitThread);
            ptrMulitThread = IntPtr.Zero;
        }

        hkBaseSystem_quit();
        hkMemoryInitUtil_quit();
    }

    //hkBase
    //=====================

    public const float HK_FLOAT_EPSILON = 1.192092896e-07F;

    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkPlatformInit();
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    [return:MarshalAs(UnmanagedType.I8)]
    public static extern int hkMemoryInitUtil_quit();
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    [return:MarshalAs(UnmanagedType.I8)]
    public static extern int hkBaseSystem_quit();

    //================================================
    // World
    //================================================

    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpWorld_new([MarshalAs(UnmanagedType.I8)] hkpWorldCinfoSimulationType simulationType, float broadPhaseWorldSize, IntPtr gravity, float collisionTolerance, int solverIterations);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpWorld_markForWrite(IntPtr physicsWorld);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
	public static extern void hkpWorld_unmarkForWrite(IntPtr physicsWorld);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpWorld_getCollisionDispatcher(IntPtr physicsWorld);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpWorld_registerWithJobQueue(IntPtr jobQueue);

    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpAgentRegisterUtil_registerAllAgents(IntPtr dis);

    /// <summary>
    /// Tries to add the body in an inactive state. However if the body overlaps with an active body, it gets activated
    /// </summary>
    public const ushort HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE = 0;
    /// <summary>
    /// Always activate this body and overlapping bodies
    /// </summary>
	public const ushort HK_ENTITY_ACTIVATION_DO_ACTIVATE = 1;

    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpWorld_addEntity(IntPtr physicsWorld, IntPtr entity, ushort initialActivationState);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern bool hkpWorld_removeEntity(IntPtr physicsWorld, IntPtr entity);


    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    [return:MarshalAs(UnmanagedType.I8)]
    public static extern hkpStepResult hkpWorld_initMtStep(IntPtr physicsWorld, IntPtr jobQueue, float physicsDeltaTime);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    [return:MarshalAs(UnmanagedType.I8)]
    public static extern hkpStepResult hkpWorld_finishMtStep(IntPtr physicsWorld);

	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpWorld_removeReference(IntPtr physicsWorld);

    //================================================
    // Entity
    //================================================


    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpEntity_removeReference(IntPtr entity);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpEntity_addReference(IntPtr entity);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpEntity_activate(IntPtr entity);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpEntity_deactivate(IntPtr entity);

    //================================================
    // Body
    //================================================

    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpRigidBody_new(IntPtr shape, IntPtr position, float mass, [MarshalAs(UnmanagedType.I8)] hkpMotionMotionType motionType, [MarshalAs(UnmanagedType.I8)] hkpCollidableQualityType qualityType, float linearDamping, float angularDamping, IntPtr linearVelocity, IntPtr angularVelocity, float gravityFactor);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_getPosition(IntPtr entity, IntPtr positionOut);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_getRotation(IntPtr entity, IntPtr quaternionOut);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setPosition(IntPtr entity, IntPtr position);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setRotation(IntPtr entity, IntPtr quaternion);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setMotionType(IntPtr entity,  [MarshalAs(UnmanagedType.I8)] hkpMotionMotionType motionType);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setMass(IntPtr entity, float mass);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setFriction(IntPtr entity, float friction);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setRestitution(IntPtr entity, float restitution);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setCenterOfMassLocal(IntPtr entity, IntPtr centerOfMass);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setInertiaLocal(IntPtr entity, IntPtr inertia);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setAngularDamping(IntPtr entity, float d);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setLinearDamping(IntPtr entity, float d);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setLinearVelocity(IntPtr entity, IntPtr newVel);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setAngularVelocity(IntPtr entity, IntPtr newVel);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpRigidBody_setGravityFactor(IntPtr entity, float f);

    //================================================
    // Shape
    //================================================

    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpBoxShape_new(IntPtr halfExtents, float radius);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpSphereShape_new(float radius);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpTriangleShape_new(IntPtr v0, IntPtr v1, IntPtr v2, float radius);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpCapsuleShape_new(float height, float radius);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpConvexVerticesShape_new(IntPtr vertices, int verticesCount);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpCylinderShape_new(float height, float radius, float convexRadius);
	[DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern IntPtr hkpSimpleMeshShape_new(float radius);
    [DllImport(DLL_NNAME, CallingConvention = _CallingConvention)]
    public static extern void hkpShape_removeReference(IntPtr shape);
}

public enum hkResult {
    
}
public enum hkpMotionMotionType
{
    /// 
    MOTION_INVALID,

    /// A fully-simulated, movable rigid body. At construction time the engine checks
    /// the input inertia and selects MOTION_SPHERE_INERTIA or MOTION_BOX_INERTIA as
    /// appropriate.
    MOTION_DYNAMIC,

    /// Simulation is performed using a sphere inertia tensor. (A multiple of the
    /// Identity matrix). The highest value of the diagonal of the rigid body's
    /// inertia tensor is used as the spherical inertia.
    MOTION_SPHERE_INERTIA,

    /// Simulation is performed using a box inertia tensor. The non-diagonal elements
    /// of the inertia tensor are set to zero. This is slower than the
    /// MOTION_SPHERE_INERTIA motions, however it can produce more accurate results,
    /// especially for long thin objects.
    MOTION_BOX_INERTIA,

    /// Simulation is not performed as a normal rigid body. During a simulation step,
    /// the velocity of the rigid body is used to calculate the new position of the
    /// rigid body, however the velocity is NOT updated. The user can keyframe a rigid
    /// body by setting the velocity of the rigid body to produce the desired keyframe
    /// positions. The hkpKeyFrameUtility class can be used to simply apply keyframes
    /// in this way. The velocity of a keyframed rigid body is NOT changed by the
    /// application of impulses or forces. The keyframed rigid body has an infinite
    /// mass when viewed by the rest of the system.
    MOTION_KEYFRAMED,

    /// This motion type is used for the static elements of a game scene, e.g., the
    /// landscape. Fixed rigid bodies are treated in a special way by the system. They
    /// have the same effect as a rigid body with a motion of type MOTION_KEYFRAMED
    /// and velocity 0, however they are much faster to use, incurring no simulation
    /// overhead, except in collision with moving bodies.
    MOTION_FIXED,

    /// A box inertia motion which is optimized for thin boxes and has less stability problems
    MOTION_THIN_BOX_INERTIA,

    /// A specialized motion used for character controllers
    MOTION_CHARACTER,
};
public enum hkpCollidableQualityType
{
		/// Invalid or unassigned type. If you add a hkpRigidBody to the hkpWorld,
		/// this type automatically gets converted to either
		/// HK_COLLIDABLE_QUALITY_FIXED, HK_COLLIDABLE_QUALITY_KEYFRAMED or HK_COLLIDABLE_QUALITY_DEBRIS
	HK_COLLIDABLE_QUALITY_INVALID = -1,

		/// Use this for fixed bodies.
	HK_COLLIDABLE_QUALITY_FIXED = 0,

		/// Use this for moving objects with infinite mass.
	HK_COLLIDABLE_QUALITY_KEYFRAMED,

		/// Use this for all your debris objects.
	HK_COLLIDABLE_QUALITY_DEBRIS,

		/// Use this for debris objects that should have simplified TOI collisions with fixed/landscape objects.
	HK_COLLIDABLE_QUALITY_DEBRIS_SIMPLE_TOI,

		/// Use this for moving bodies, which should not leave the world,
		/// but you rather prefer those objects to tunnel through the world than
		/// dropping frames because the engine .
	HK_COLLIDABLE_QUALITY_MOVING,

		/// Use this for all objects, which you cannot afford to tunnel through
		/// the world at all.
	HK_COLLIDABLE_QUALITY_CRITICAL,

		/// Use this for very fast objects.
	HK_COLLIDABLE_QUALITY_BULLET,

		/// For user. If you want to use this, you have to modify hkpCollisionDispatcher::initCollisionQualityInfo()
	HK_COLLIDABLE_QUALITY_USER,

		/// Use this for rigid body character controllers.
	HK_COLLIDABLE_QUALITY_CHARACTER,

		/// Use this for moving objects with infinite mass which should report contact points and TOI-collisions against all other bodies, including other fixed and keyframed bodies.
		///
		/// Note that only non-TOI contact points are reported in collisions against debris-quality objects.
	HK_COLLIDABLE_QUALITY_KEYFRAMED_REPORTING,

		/// End of this list
	HK_COLLIDABLE_QUALITY_MAX
};
public enum hkpStepResult
{
    /// <summary>
	/// The call to stepDelta time was a processed to the end
    /// </summary>   
	HK_STEP_RESULT_SUCCESS,
    /// <summary>
	/// The engine predicted that it would run out of memory before doing any work
    /// </summary>   
	HK_STEP_RESULT_MEMORY_FAILURE_BEFORE_INTEGRATION,
    /// <summary>
	/// The collide call failed as some collision agents were allocated too much memory
    /// </summary>   
	HK_STEP_RESULT_MEMORY_FAILURE_DURING_COLLIDE,
    /// <summary>
	/// The advanceTime call failed during TOI solving
    /// </summary>   
	HK_STEP_RESULT_MEMORY_FAILURE_DURING_TOI_SOLVE,
};
public enum hkpWorldCinfoSimulationType
{
    ///
    SIMULATION_TYPE_INVALID,

    /// No continuous simulation is performed
    SIMULATION_TYPE_DISCRETE,

    /// Use this simulation if you want any continuous simulation.
    /// Depending on the hkpEntity->getQualityType(), collisions
    /// are not only performed at 'normal' physical timesteps (called PSI), but
    /// at any time when two objects collide (TOI)
    SIMULATION_TYPE_CONTINUOUS,

    /// Multithreaded continuous simulation.
    /// You must have read the multi threading user guide.
    ///
    /// To use this you should call hkpWorld::stepMultithreaded(), see
    /// the hkDefaultPhysicsDemo::stepDemo for an example.
    /// Notes:
    ///   - The internal overhead for multi threaded is small and you can expect
    ///     good speedups, except:
    ///   - solving multiple TOI events can not be done on different threads,
    ///     so TOI are solved on a single thread. However the collision detection
    ///     for each TOI event can be solver multithreaded (see m_processToisMultithreaded)
    SIMULATION_TYPE_MULTITHREADED,
};