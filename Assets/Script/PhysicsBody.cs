
using PhysicsRT.Utils;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace PhysicsRT
{
    public enum MotionType {
        /// <summary>
        /// A fully-simulated, movable rigid body. At construction time the engine checks
        /// the input inertia and selects MOTION_SPHERE_INERTIA or MOTION_BOX_INERTIA as
        /// appropriate.
        /// </summary>
        Dynamic,
        /// <summary>
        /// Simulation is performed using a sphere inertia tensor. (A multiple of the
        /// Identity matrix). The highest value of the diagonal of the rigid body's
        /// inertia tensor is used as the spherical inertia.
        /// </summary>
        SphereInertia,
        /// <summary>
        /// Simulation is performed using a box inertia tensor. The non-diagonal elements
        /// of the inertia tensor are set to zero. This is slower than the
        /// MOTION_SPHERE_INERTIA motions, however it can produce more accurate results,
        /// especially for long thin objects.
        /// </summary>
        BoxInertia,
        /// <summary>
        /// Simulation is not performed as a normal rigid body. During a simulation step,
        /// the velocity of the rigid body is used to calculate the new position of the
        /// rigid body, however the velocity is NOT updated. The user can keyframe a rigid
        /// body by setting the velocity of the rigid body to produce the desired keyframe
        /// positions. The hkpKeyFrameUtility class can be used to simply apply keyframes
        /// in this way. The velocity of a keyframed rigid body is NOT changed by the
        /// application of impulses or forces. The keyframed rigid body has an infinite
        /// mass when viewed by the rest of the system.
        /// </summary>
        Keyframed,
        /// <summary>
        /// This motion type is used for the static elements of a game scene, e.g., the
        /// landscape. Fixed rigid bodies are treated in a special way by the system. They
        /// have the same effect as a rigid body with a motion of type MOTION_KEYFRAMED
        /// and velocity 0, however they are much faster to use, incurring no simulation
        /// overhead, except in collision with moving bodies.
        /// </summary>
        Fixed,

        /// <summary>
        /// A box inertia motion which is optimized for thin boxes and has less stability problems
        /// </summary>
        ThinBoxInertia,
        /// <summary>
        /// A specialized motion used for character controllers
        /// </summary>
        Character,
    }
    public enum CollidableQualityType
    {    
        Default = -1,
        /// Use this for fixed bodies.
        Fixed = 0,
        /// Use this for moving objects with infinite mass.
        Keyframed,
        /// Use this for all your debris objects.
        Debris,
        /// Use this for debris objects that should have simplified TOI collisions with fixed/landscape objects.
        DebrisSimpleTOI,
        /// Use this for moving bodies, which should not leave the world,
        /// but you rather prefer those objects to tunnel through the world than
        /// dropping frames because the engine .
        Moving,
        /// Use this for all objects, which you cannot afford to tunnel through
        /// the world at all.
        Critical,
        /// Use this for very fast objects.
        Bullet,
        /// For user. If you want to use this, you have to modify hkpCollisionDispatcher::initCollisionQualityInfo()
        User,
        /// Use this for rigid body character controllers.
        Character,
        /// Use this for moving objects with infinite mass which should report contact points and TOI-collisions against all other bodies, including other fixed and keyframed bodies.
        ///
        /// Note that only non-TOI contact points are reported in collisions against debris-quality objects.
        KeyframedReporting,
    };

    [AddComponentMenu("PhysicsRT/Physics Body")]
    [DefaultExecutionOrder(250)]
    [DisallowMultipleComponent]
    [RequireComponent(typeof(PhysicsShape))]
    public class PhysicsBody : MonoBehaviour, LinkedListItem<PhysicsBody>
    {
        const float MinimumMass = 0.001f;
    
        private int Convert(MotionType m) {
            switch(m) {
                case MotionType.Dynamic: return 1;
                case MotionType.SphereInertia: return 2;
                case MotionType.BoxInertia: return 3;
                case MotionType.Keyframed: return 4;
                case MotionType.Fixed: return 5;
                case MotionType.ThinBoxInertia: return 6;
                case MotionType.Character: return 7;
            }
            return 0;
        }

        [SerializeField]
        MotionType m_MotionType = MotionType.Fixed;
        [SerializeField]
        [Tooltip("The quality type, used to specify when to use continuous physics.")]
        CollidableQualityType m_CollidableQualityType = CollidableQualityType.Default;
        [SerializeField]
        float m_Mass = 1.0f;
        [SerializeField]
        [Tooltip("???????????????????????????????????????????????????")]
        float m_LinearDamping = 0.0f;
        [SerializeField]
        [Tooltip("????????????????????????????????????????????????????????????")]
        float m_AngularDamping = 0.05f;
        [SerializeField]
        [Tooltip("??????????????????????????????????????????")]
        Vector3 m_InitialLinearVelocity = Vector3.zero;
        [SerializeField]
        [Tooltip("???????????????????????????????????????????????????????????????????????????????????????????????????")]
        Vector3 m_InitialAngularVelocity = Vector3.zero;
        [SerializeField]
        [Tooltip("????????????????????????????????????")]
        float m_GravityFactor = 1f;
        [SerializeField]
        public Vector3 m_CenterOfMass;
        [SerializeField]
        CustomPhysicsBodyTags m_CustomTags = CustomPhysicsBodyTags.Nothing;
        [Range(0, 1)]
        [Tooltip("???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????0???1???????????????????????????????????????255??????????????????0.5???")]
        public float m_Friction = 0.5f;
        [Range(0, 1.99f)]
        [Tooltip("??????????????????????????????????????????????????????????????????????????????????????????????????????1??????????????????????????????????????????????????????0????????????????????????????????????????????????0.4????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????")]
        [SerializeField]
        private float m_Restitution = 0.4f;
        [SerializeField]
        private int m_Layer = -1;
        [SerializeField]
        private Matrix4x4 m_InertiaTensor = Matrix4x4.identity;
        [SerializeField]
        [Tooltip("The maximum angular velocity of the body (in rad/s).")]
        private float m_MaxAngularVelocity = 200;
        [SerializeField]
        [Tooltip("The maximum linear velocity of the body (in m/s).")]
        private float m_MaxLinearVelocity = 200;
        [SerializeField]
        [Tooltip("Is this body is Tigger ?")]
        private bool m_IsTigger = false;
        [Tooltip("????????????ContactListener??????????????????ContactListener????????????OnCollision??????")]
        [SerializeField]
        private bool m_AddContactListener = false;
        [Tooltip("??? Awake ???????????????????????????????????? false ???????????????????????? ForceReCreateShape ???????????????")]
        [SerializeField]
        public bool m_DoNotAutoCreateAtAwake = false;
        [Tooltip("???????????? CenterOfMass ")]
        [SerializeField]
        public bool m_AutoComputeCenterOfMass = true;

        private IntPtr ptr = IntPtr.Zero;

        /// <summary>
        /// ??? Awake ???????????????????????????????????? false ???????????????????????? ForceReCreateShape ???????????????
        /// </summary>
        public bool DoNotAutoCreateAtAwake { get => m_DoNotAutoCreateAtAwake; set { m_DoNotAutoCreateAtAwake = value; } }
        /// <summary>
        /// ????????????CenterOfMass?????????????????????????????????
        /// </summary>
        public bool AutoComputeCenterOfMass { get => m_AutoComputeCenterOfMass; set { m_AutoComputeCenterOfMass = value; } }
        /// <summary>
        /// ??????????????????????????????
        /// </summary>
        public int Layer {
            get => m_Layer; 
            set {
                if(m_Layer != value) {
                    m_Layer = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigidBodyLayer(ptr, m_Layer);
                }
            }
        }  
        /// <summary>
        /// ??????????????????????????????
        /// </summary>
        public MotionType MotionType {
            get => m_MotionType; 
            set {
                if(m_MotionType != value) {
                    m_MotionType = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigidBodyMotionType(ptr, (int)Convert(m_MotionType));
                }
            }
        }
        /// <summary>
        /// ?????????????????????????????????????????????????????????????????????????????????
        /// </summary>
        public CollidableQualityType CollidableQualityType {
            get => m_CollidableQualityType; 
            set => m_CollidableQualityType = value;
        }
        /// <summary>
        /// ?????????????????????????????????????????????????????????????????????????????????????????????
        /// </summary>
        public Vector3 InitialAngularVelocity
        {
            get => m_InitialAngularVelocity;
            set => m_InitialAngularVelocity = value;
        }
        /// <summary>
        /// ????????????????????????????????????????????????????????????????????????????????????
        /// </summary>
        public Vector3 InitialLinearVelocity
        {
            get => m_InitialLinearVelocity;
            set => m_InitialLinearVelocity = value;
        }
        /// <summary>
        /// ??????????????????????????????
        /// </summary>
        public float Mass {
            get => m_Mass; 
            set {
                if(m_Mass != value) {
                    m_Mass = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigidBodyMass(ptr, value);
                }
            }
        }
        /// <summary>
        /// ???????????????????????????????????????
        /// </summary>
        public CustomPhysicsBodyTags CustomTags { get => m_CustomTags; set { m_CustomTags = value; } }
        /// <summary>
        /// ???????????????????????????????????????????????????????????????????????????????????????????????????????????????
        /// </summary>
        public bool IsTigger { get => m_IsTigger; set { m_IsTigger = value; } }
        /// <summary>
        /// ????????????ContactListener??????????????????ContactListener????????????OnCollision???????????????????????????????????????
        /// </summary>
        public bool AddContactListener { 
            get => m_AddContactListener; 
            set { 
                if(ptr != IntPtr.Zero)
                    throw new Exception("Body is created, do not modify this after creation");
                m_AddContactListener = value; 
            } 
        }
        /// <summary>
        /// ??????????????????????????????
        /// </summary>
        public Vector3 CenterOfMass {
            get => m_CenterOfMass; 
            set {
                if(m_CenterOfMass != value) {
                    m_CenterOfMass = value; 
                    if(ptr != IntPtr.Zero) {
                        PhysicsApi.API.SetRigidBodyCenterOfMass(ptr, value);
                    }
                }
            }
        }
        /// <summary>
        /// ????????????????????????????????????
        /// </summary>
        public Matrix4x4 InertiaTensor {
            get => m_InertiaTensor; 
            set {
                if(m_InertiaTensor != value) {
                    m_InertiaTensor = value; 
                    if(ptr != IntPtr.Zero) 
                        PhysicsApi.API.SetRigidBodyInertiaTensor(ptr, value);
                }
            }
        }
        /// <summary>
        /// ????????????????????????????????????
        /// </summary>
        public float GravityFactor {
            get => m_GravityFactor; 
            set {
                if(m_GravityFactor != value) {
                    m_GravityFactor = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigidBodyGravityFactor(ptr, m_GravityFactor);
                }
            }
        }
        /// <summary>
        /// ?????????????????????????????????
        /// </summary>
        public float LinearDamping {
            get => m_LinearDamping; 
            set {
                if(m_LinearDamping != value) {
                    m_LinearDamping = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigidBodyLinearDampin(ptr, m_LinearDamping);
                }
            }
        }
        /// <summary>
        /// ?????????????????????????????????
        /// </summary>
        public float AngularDamping {
            get => m_AngularDamping; 
            set {
                if(m_AngularDamping != value) {
                    m_AngularDamping = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigidBodyAngularDamping(ptr, m_AngularDamping);
                }
            }
        }
        /// <summary>
        /// ?????????????????????????????????
        /// </summary>
        public float Friction {
            get => m_Friction; 
            set {
                if(m_Friction != value) {
                    m_Friction = value;
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigidBodyFriction(ptr, m_Friction);
                }
            }
        }
        /// <summary>
        /// ??????????????????????????????
        /// </summary>
        public float Restitution {
            get => m_Restitution; 
            set {
                if(m_Restitution != value) {
                    m_Restitution = value;
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigidBodyRestitution(ptr, m_Restitution);
                }
            }
        }
        /// <summary>
        /// ID
        /// </summary>
        /// <value></value>
        public int Id { get; private set; }

        public PhysicsBody prev { get; set; }
        public PhysicsBody next { get; set; }

        /// <summary>
        /// ???????????????????????????????????????????????????????????????
        /// </summary>
        public void ForceReCreateShape()
        {
            nextCreateForce = true;
            DestroyBody();
            CreateBody();
        }

        private void Awake() {
            CurrentPhysicsWorld = PhysicsWorld.GetCurrentScensePhysicsWorld();
            StartCoroutine(LateCreate());
        }
        private void OnDestroy() {
            DestroyBody();
        }
        private IEnumerator LateCreate() {
            yield return new WaitForSeconds(0.05f); 
            if(!m_DoNotAutoCreateAtAwake)
                CreateBody();
        }

        private void OnEnable()
        {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.ActiveRigidBody(ptr);
        }
        private void OnDisable() 
        {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.DeactiveRigidBody(ptr);
        }
        private void OnValidate()
        {
            Mass = Mathf.Max(MinimumMass, Mass);
            m_LinearDamping = Mathf.Max(m_LinearDamping, 0f);
            m_AngularDamping = Mathf.Max(m_AngularDamping, 0f);
        }

        private PhysicsWorld CurrentPhysicsWorld = null;
        private IntPtr currentShapeMassProperties = IntPtr.Zero;
        private bool nextCreateForce = false;

        public IntPtr GetPtr() { return ptr; }
        private IntPtr GetShapeBody() {

            var shape = GetComponent<PhysicsShape>();
            if(shape == null)
            {
                Debug.LogWarning("Not found PhysicsShape on this gameObject, physical function has been disabled.");
                return IntPtr.Zero;
            }

            var s = shape.GetShapeBody(nextCreateForce);
            if(CenterOfMass != Vector3.zero)
                currentShapeMassProperties = shape.ComputeMassProperties(m_Mass);
            return s;
        }
        private void ReleaseShapeBody() {

            var shape = GetComponent<PhysicsShape>();
            if(shape != null)
                shape.ReleaseShapeBody();
        }
        private void CreateBody() {
            if(ptr != IntPtr.Zero) {
                return;
            }
            if(CurrentPhysicsWorld == null) {
                Debug.LogWarning("Not found PhysicsWorld in this scense, please add it before use PhysicsBody.");
                return;
            }

            ptr = PhysicsApi.API.CreateRigidBody(
                CurrentPhysicsWorld.GetPtr(),
                GetShapeBody(), 
                transform.position, 
                transform.rotation,
                Convert(m_MotionType),
                (int)m_CollidableQualityType,
                m_Friction,
                m_Restitution,
                m_Mass, 
                PhysicsApi.API.BoolToInt(gameObject.activeSelf), 
                m_Layer,
                m_IsTigger,
                m_AddContactListener,
                m_GravityFactor,
                m_LinearDamping,
                m_AngularDamping,
                m_CenterOfMass,
                m_InertiaTensor,
                m_InitialLinearVelocity,
                m_InitialAngularVelocity,
                m_MaxLinearVelocity,
                m_MaxAngularVelocity,
                currentShapeMassProperties);

            TryCreateConstant();

            Id = PhysicsApi.API.GetRigidBodyId(ptr);
            CurrentPhysicsWorld.AddBody(Id, this);
            
            ReApplyForce();

            nextCreateForce = false;
        }
        private void DestroyBody() {
            if(CurrentPhysicsWorld == null || ptr == IntPtr.Zero)
                return;

            if(currentShapeMassProperties != IntPtr.Zero)
            {
                PhysicsApi.API.CommonDelete(currentShapeMassProperties);
                currentShapeMassProperties = IntPtr.Zero;
            }

            ReleaseShapeBody();

            CurrentPhysicsWorld.RemoveBody(this);
            PhysicsApi.API.DestroyRigidBody(ptr);
            ptr = IntPtr.Zero;
        }
    
        //???????????????????????????
        private void TryCreateConstant() {
            var constants = GetComponents<PhysicsConstraint>();
            for(int i = 0; i < constants.Length; i++) 
                constants[i].TryCreate();
            foreach(PhysicsConstraint c in pendingCreateConstant)
                c.TryCreate();
            pendingCreateConstant.Clear();
        }
        private List<PhysicsConstraint> pendingCreateConstant = new List<PhysicsConstraint>();
        internal void AddPendingCreateConstant(PhysicsConstraint c) { pendingCreateConstant.Add(c); }

        private MotionType oldMotionType = MotionType.Fixed;
        private float oldMass = 0;
        private float oldLinearDamping =  0;
        private float oldAngularDamping = 0;
        private float oldGravityFactor =  0;
        private Vector3 oldCenterOfMass = Vector3.zero;
        private float oldFriction =  0;
        private float oldRestitution = 0;
        private int oldLayer = 0;
        private Vector3 oldPosition = Vector3.zero;
        private Quaternion oldRotation = Quaternion.identity;

        public void BackUpRuntimeCanModifieProperties() {
            oldMotionType = m_MotionType;
            oldMass = m_Mass;
            oldLinearDamping = m_LinearDamping;
            oldAngularDamping = m_AngularDamping;
            oldGravityFactor = m_GravityFactor;
            oldCenterOfMass = m_CenterOfMass;
            oldFriction = m_Friction;
            oldRestitution = m_Restitution;
            oldLayer = m_Layer;
            oldPosition = transform.position;
            oldRotation = transform.rotation;
        }
        public void ApplyModifiedProperties() {
            if(oldMotionType != m_MotionType) {
                var newVal = m_MotionType; m_MotionType = oldMotionType;
                MotionType = newVal;
            }
            if(oldMass != m_Mass) {
                var newVal = m_Mass; m_Mass = oldMass;
                Mass = newVal;
            }
            if(oldLinearDamping != m_LinearDamping) {
                var newVal = m_LinearDamping; m_LinearDamping = oldLinearDamping;
                LinearDamping = newVal;
            }
            if(oldAngularDamping != m_AngularDamping) {
                var newVal = m_AngularDamping; m_AngularDamping = oldAngularDamping;
                AngularDamping = newVal;
            }
            if(oldGravityFactor != m_GravityFactor) {
                var newVal = m_GravityFactor; m_GravityFactor = oldGravityFactor;
                GravityFactor = newVal;
            }
            if(oldCenterOfMass != m_CenterOfMass) {
                var newVal = m_CenterOfMass; m_CenterOfMass = oldCenterOfMass;
                CenterOfMass = newVal;
            }
            if(oldFriction != m_Friction) {
                var newVal = m_Friction; m_Friction = oldFriction;
                Friction = newVal;
            }
            if(oldRestitution != m_Restitution) {
                var newVal = m_Restitution; m_Restitution = oldRestitution;
                Restitution = newVal;
            }
            if(oldLayer != m_Layer) {
                var newVal = m_Layer; m_Layer = oldLayer;
                Layer = newVal;
            }
            if(oldRotation != transform.rotation)
                UpdateTransformToPhysicsEngine();
            else if(oldPosition != transform.position)
                UpdatePositionToPhysicsEngine();
        }
        /// <summary>
        /// ????????????????????????????????????
        /// </summary>
        public void UpdateTransformToPhysicsEngine() {
             if(ptr != IntPtr.Zero)
                PhysicsApi.API.SetRigidBodyPositionAndRotation(ptr, transform.position, transform.rotation);
        }
        /// <summary>
        /// ????????????
        /// </summary>
        public void UpdatePositionToPhysicsEngine() {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.SetRigidBodyPosition(ptr, transform.position);
        }

        /// <summary>
        /// The velocity of the rigidbody at the point worldPoint in global space.
        /// </summary>
        /// <param name="worldPoint"></param>
        /// <returns></returns>
        public Vector3 GetPointVelocity(Vector3 worldPoint) {
            if(ptr == IntPtr.Zero) throw new PhysicsBodyNotCreateException();
            
            PhysicsApi.API.GetRigidBodyPointVelocity(ptr, worldPoint, out var v);
            return v;
        }
        /// <summary>
        /// The velocity relative to the rigidbody at the point relativePoint.
        /// </summary>
        /// <param name="relativePoint"></param>
        /// <returns></returns>
        public Vector3 GetRelativePointVelocity(Vector3 relativePoint) {
            return GetPointVelocity(transform.position + relativePoint);
        }
        /// <summary>
        /// ??????????????????????????????
        /// </summary>
        /// <value></value>
        public Vector3 AngularVelocity {
            get {
                if(ptr == IntPtr.Zero)
                    return InitialAngularVelocity;
                else {
                    PhysicsApi.API.GetRigidBodyAngularVelocity(ptr, out var v);
                    return v;
                }
            }
            set {
                if(ptr == IntPtr.Zero) throw new PhysicsBodyNotCreateException();
                PhysicsApi.API.SetRigidBodyAngularVelocity(ptr, value);
            }
        }
        /// <summary>
        /// ??????????????????????????????
        /// </summary>
        /// <value></value>
        public Vector3 LinearVelocity {
            get {
                if(ptr == IntPtr.Zero)
                    return InitialLinearVelocity;
                else {
                    PhysicsApi.API.GetRigidBodyLinearVelocity(ptr, out var v);
                    return v;
                }
            }
            set {
                if(ptr == IntPtr.Zero) throw new PhysicsBodyNotCreateException();
                PhysicsApi.API.SetRigidBodyLinearVelocity(ptr, value);
            }
        }
        /// <summary>
        /// The maximum angular velocity of the body (in rad/s).
        /// </summary>
        /// <value></value>
        public float MaxAngularVelocity {
            get => m_MaxAngularVelocity;
            set {
                if(ptr == IntPtr.Zero) throw new PhysicsBodyNotCreateException();
                m_MaxAngularVelocity = value;
                PhysicsApi.API.SetRigidBodyMaxAngularVelocity(ptr, value);
            }
        }
        /// <summary>
        /// The maximum linear velocity of the body (in rad/s).
        /// </summary>
        /// <value></value>
        public float MaxLinearVelocity {
            get => m_MaxLinearVelocity;
            set {
                if(ptr == IntPtr.Zero) throw new PhysicsBodyNotCreateException();
                m_MaxLinearVelocity = value;
                PhysicsApi.API.SetRigidBodyMaxLinearVelocity(ptr, value);
            }
        }
    
        //???????????????????????????????????????????????????????????????????????????
        private enum StartTemForceType {
           Force,
           ForceAtPoint,
           Torque,
           LinearImpulse,
           PointImpulse,
           AngularImpulse
        }
        private class StartTemForce {
            public StartTemForceType type;
            public Vector3 force;
            public Vector3 point;
            public StartTemForce(StartTemForceType type, Vector3 force, Vector3 point) {
                this.type = type;
                this.force = force;
                this.point = point;
            }

        }
        private List<StartTemForce> fTemp = new List<StartTemForce>();
        private void ReApplyForce() {
            if(ptr != IntPtr.Zero) {
                fTemp.ForEach((a) => {
                    switch(a.type) {
                        case StartTemForceType.Force: 
                            ApplyForce(a.force);
                            break;
                        case StartTemForceType.ForceAtPoint: 
                            ApplyForceAtPoint(a.force, a.point);
                            break;
                        case StartTemForceType.Torque: 
                            ApplyTorque(a.force);
                            break;
                        case StartTemForceType.LinearImpulse: 
                            ApplyForce(a.force);
                            break;
                        case StartTemForceType.PointImpulse: 
                            ApplyPointImpulse(a.force, a.point);
                            break;
                        case StartTemForceType.AngularImpulse: 
                            ApplyAngularImpulse(a.force);
                            break;
                    }
                });
                fTemp.Clear();
            }
        }

        /// <summary>
        /// Applies a force to the rigid body. The force is applied to the center of mass.
        /// </summary>
        /// <param name="force"></param>
        public void ApplyForce(Vector3 force) {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.RigidBodyApplyForce(ptr, Time.deltaTime, force);
            else
                fTemp.Add(new StartTemForce(StartTemForceType.Force, force, Vector3.zero));
        }
        /// <summary>
        /// Applies a force (in world space) to the rigid body at the point p in world space.
        /// </summary>
        /// <param name="force"></param>
        /// <param name="point"></param>
        public void ApplyForceAtPoint(Vector3 force, Vector3 point) {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.RigidBodyApplyForceAtPoint(ptr, Time.deltaTime, force, point);
            else
                fTemp.Add(new StartTemForce(StartTemForceType.ForceAtPoint, force, point));
        }
        /// <summary>
        /// Applies the specified torque (in world space) to the rigid body.
        /// Specify the torque as an Vector3. The direction of the vector indicates the axis (in world space) that you want the body to rotate around, and the magnitude of the vector indicates the strength of the force applied. The change in the body's angular velocity after torques are applied is proportional to the simulation delta time value and inversely proportional to the body's  inertia. 
        /// </summary>
        /// <param name="torque"></param>
        public void ApplyTorque(Vector3 torque) {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.RigidBodyApplyTorque(ptr, Time.deltaTime, torque);
            else
                fTemp.Add(new StartTemForce(StartTemForceType.Torque, torque, Vector3.zero));
        }
        /// <summary>
        /// Applies an impulse (in world space) to the center of mass.
        /// </summary>
        /// <param name="imp"></param>
        public void ApplyLinearImpulse(Vector3 imp) {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.RigidBodyApplyLinearImpulse(ptr, imp);
            else
                fTemp.Add(new StartTemForce(StartTemForceType.LinearImpulse, imp, Vector3.zero));
        }
        /// <summary>
        /// Apply an impulse at the point p in world space.
        /// </summary>
        /// <param name="imp"></param>
        /// <param name="point"></param>
        public void ApplyPointImpulse(Vector3 imp, Vector3 point) {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.RigidBodyApplyPointImpulse(ptr, imp, point);
            else
                fTemp.Add(new StartTemForce(StartTemForceType.PointImpulse, imp, point));
        }
        /// <summary>
        /// Apply an instantaneous change in angular velocity around center of mass.
        /// </summary>
        /// <param name="imp"></param>
        public void ApplyAngularImpulse(Vector3 imp) {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.RigidBodyApplyAngularImpulse(ptr, imp);
            else
                fTemp.Add(new StartTemForce(StartTemForceType.AngularImpulse, imp, Vector3.zero));
        }

        public delegate void OnBodyTiggerCollCallback(PhysicsBody body, PhysicsBody other);
        public delegate void OnBodyCollisionCallback(PhysicsBody body, PhysicsBody other, PhysicsBodyCollisionInfo info);
        public delegate void OnBodyCollisionLeaveCallback(PhysicsBody body, PhysicsBody other);

        /// <summary>
        /// Tigger?????????????????????????????????Tigger????????????
        /// </summary>
        public OnBodyTiggerCollCallback onTiggerEnter;
        /// <summary>
        /// Tigger?????????????????????????????????Tigger????????????
        /// </summary>
        public OnBodyTiggerCollCallback onTiggerLeave;

        /// <summary>
        /// ?????????????????????????????????AddContactListener???true????????????
        /// </summary>
        public OnBodyCollisionCallback onCollisionEnter;
        /// <summary>
        /// ?????????????????????????????????AddContactListener???true????????????
        /// </summary>
        public OnBodyCollisionLeaveCallback onCollisionLeave;
        /// <summary>
        /// ?????????????????????????????????AddContactListener???true????????????
        /// </summary>
        public OnBodyCollisionCallback onCollisionStay;

        private enum PhysicsBodyContactDataState {
            NEW_ADD,
            TWICE_ADD,
            END,
        }
        private class PhysicsBodyContactData : LinkedListItem<PhysicsBodyContactData> {
            public PhysicsBody body;
            public sPhysicsBodyContactData data;
            public PhysicsBodyContactDataState state;
            public bool entered = false;
            public bool needLeave = false;
            public PhysicsBodyContactData(PhysicsBody body, sPhysicsBodyContactData data) {
                this.body = body;
                this.data = data;
                state = PhysicsBodyContactDataState.NEW_ADD;
            }

            public PhysicsBodyContactData prev { get; set; }
            public PhysicsBodyContactData next { get; set; }
        }
        private Dictionary<int, PhysicsBodyContactData> currentFramEnterBodies = new Dictionary<int, PhysicsBodyContactData>();
        private SimpleLinkedList<PhysicsBodyContactData> currentFramEnterBodiesList = new SimpleLinkedList<PhysicsBodyContactData>();

        internal void FlushPhysicsBodyContactDataTick() {
            List<int> needRemoveData = new List<int>();
            PhysicsBodyContactData d = currentFramEnterBodiesList.getBegin();
            while(d != null) {
                switch(d.state) {
                    case PhysicsBodyContactDataState.NEW_ADD: 
                        onCollisionEnter?.Invoke(this, d.body, new PhysicsBodyCollisionInfo(d.data));
                        d.state = d.needLeave ? PhysicsBodyContactDataState.END : PhysicsBodyContactDataState.TWICE_ADD;
                        d.entered = true;
                        break;
                    case PhysicsBodyContactDataState.TWICE_ADD: 
                        onCollisionStay?.Invoke(this, d.body, new PhysicsBodyCollisionInfo(d.data));
                        break;
                    case PhysicsBodyContactDataState.END: 
                        onCollisionLeave?.Invoke(this, d.body);
                        currentFramEnterBodies.Remove(d.body.Id);
                        currentFramEnterBodiesList.remove(d);
                        break;
                }
                d = d.next;
            }
        }
        internal void OnBodyPointContactCallback(PhysicsBody other, sPhysicsBodyContactData data) {
            if(currentFramEnterBodies.TryGetValue(other.Id, out var d)) {
                if(data.isRemoved == 1) {
                    if(d.entered) d.state = PhysicsBodyContactDataState.END;
                    else d.needLeave = true;
                } else {
                    d.data = data;
                    d.state = PhysicsBodyContactDataState.TWICE_ADD;
                }
            } else {
                d = new PhysicsBodyContactData(other, data);
                currentFramEnterBodies.Add(other.Id, d);
                currentFramEnterBodiesList.add(d);
            }
        }
    }
    public class PhysicsBodyCollisionInfo {
        public float distance { get; private set; }
        public Vector3 position { get; private set; }
        public Vector3 normal { get; private set; }
        public Vector3 separatingNormal { get; private set; }
        public float separatingVelocity { get; private set; }

        internal PhysicsBodyCollisionInfo(sPhysicsBodyContactData data) {
            distance = data.distance;
            separatingVelocity = data.separatingVelocity;
            position = new Vector3(data.pos[0], data.pos[1], data.pos[2]);
            separatingNormal = new Vector3(data.separatingNormal[0], data.separatingNormal[1], data.separatingNormal[2]);
            normal = new Vector3(data.normal[0], data.normal[1], data.normal[2]);
        }
    }
    public class PhysicsBodyNotCreateException : Exception {
        public PhysicsBodyNotCreateException() : base("Body is not created yet.") {}
    }
}