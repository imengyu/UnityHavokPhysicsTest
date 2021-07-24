using System;
using System.Collections.Generic;
using UnityEngine;

[AddComponentMenu("PhysicsRT/Physics World")]
[DefaultExecutionOrder(90)]
[DisallowMultipleComponent]
public class PhysicsWorld : MonoBehaviour
{
    [Tooltip("Use this simulation if you want any continuous simulation.")]
    public bool Continuous = false;
    [Tooltip("Multithreaded continuous simulation.")]
    public bool Multithreaded = false;
    [Tooltip("The gravity for the world. The default is (0, -9.8, 0).")]
    public Vector3 Gravity = new Vector3(0, -9.81f, 0);
    [Tooltip("Specifies the number of solver iterations the physics engine will perform. Higher values mean more stability, but also worse performance.")]
    public int SolverIterationCount = 4;
    [Tooltip("Sets the broadphase size to be a cube centered on the origin of side sideLength.")]
    public float BroadPhaseWorldSize = 1000;
    [Tooltip("The collision tolerance. This is used to create and keep contact points even for non penetrating objects. This dramatically increases the stability of the system. The default collision tolerance is 0.1f.")]
    public float CollisionTolerance = 0.1f;
    [Tooltip("Enable simulating .")]
    public bool Simulating = true;

    public static PhysicsWorld Inastance { get; private set; }

    private List<PhysicsBody> bodys = new List<PhysicsBody>();

    private void Awake() {
        if(Inastance != null) 
            Debug.LogError("There can only one PhysicsWorld instance in a scense.");
        else {
            Inastance = this;
            InitPhysicsWorld();
        }
    }
    private void OnDestroy() {
        Inastance = null; 
        DestroyPhysicsWorld();
    }
    private void Start()
    {
        
    }
    private void Update()
    {
        
    }
    private void FixedUpdate() {
        if(Simulating) {

            //StepWorld
            PhysicsApi.RT_StepWorld(physicsWorldPtr, PhysicsApi.MulitThreadPtr, Time.deltaTime);

            //Update all bodys position
            foreach(PhysicsBody body in bodys) {
                if(body.gameObject.activeSelf) {
                    
                }
            }
        }
    }

    private IntPtr physicsWorldPtr = IntPtr.Zero;

    private void InitPhysicsWorld() {

        bool mulitThread = PhysicsApi.MulitThreadEnabled && Multithreaded;

        hkpWorldCinfoSimulationType type = hkpWorldCinfoSimulationType.SIMULATION_TYPE_DISCRETE;
        if(Multithreaded) type = hkpWorldCinfoSimulationType.SIMULATION_TYPE_MULTITHREADED;
        else if(Multithreaded) type = hkpWorldCinfoSimulationType.SIMULATION_TYPE_CONTINUOUS;
        
        physicsWorldPtr = PhysicsApi.hkpWorld_new(
            type,
            BroadPhaseWorldSize,
            new hkVector4(Gravity).Ptr,
            CollisionTolerance,
            SolverIterationCount
        );

        PhysicsApi.hkpWorld_markForWrite(physicsWorldPtr);
        PhysicsApi.hkpAgentRegisterUtil_registerAllAgents(PhysicsApi.hkpWorld_getCollisionDispatcher(physicsWorldPtr));

        if(mulitThread)
            PhysicsApi.hkpWorld_registerWithJobQueue(PhysicsApi.RT_GetMulitThreadJobQueue(PhysicsApi.MulitThreadPtr));

        PhysicsApi.hkpWorld_unmarkForWrite(physicsWorldPtr);
    }
    private void DestroyPhysicsWorld() {
        PhysicsApi.hkpWorld_markForWrite(physicsWorldPtr);
        PhysicsApi.hkpWorld_removeReference(physicsWorldPtr);
        physicsWorldPtr = IntPtr.Zero;
    }

    public void AddBody(PhysicsBody body) {
        if(!bodys.Contains(body)) {

            bodys.Add(body);

            PhysicsApi.hkpWorld_addEntity(physicsWorldPtr, body.Ptr, body.gameObject.activeSelf ? PhysicsApi.HK_ENTITY_ACTIVATION_DO_ACTIVATE :  PhysicsApi.HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE);
            PhysicsApi.hkpEntity_removeReference(body.Ptr);
        }
    }
    public void RemoveBody(PhysicsBody body) {
        if(bodys.Contains(body)) {
            bodys.Remove(body);

            PhysicsApi.hkpWorld_removeEntity(physicsWorldPtr, body.Ptr);
            PhysicsApi.hkpEntity_addReference(body.Ptr);
        }
    }
}
