
using PhyicsRT.Utils;
using System;
using UnityEngine;

namespace PhyicsRT
{
    public enum MotionMotionType {
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

    [AddComponentMenu("PhysicsRT/Physics Body")]
    [DefaultExecutionOrder(150)]
    [DisallowMultipleComponent]
    public class PhysicsBody : MonoBehaviour, LinkedListItem<PhysicsBody>
    {

        const float MinimumMass = 0.001f;
    
        private int Convert(MotionMotionType m) {
            switch(m) {
                case MotionMotionType.Dynamic: return 1;
                case MotionMotionType.SphereInertia: return 2;
                case MotionMotionType.BoxInertia: return 3;
                case MotionMotionType.Keyframed: return 4;
                case MotionMotionType.Fixed: return 5;
                case MotionMotionType.ThinBoxInertia: return 6;
                case MotionMotionType.Character: return 7;
            }
            return 0;
        }

        [SerializeField]
        MotionMotionType m_MotionType = MotionMotionType.Fixed;
        [SerializeField]
        CollidableQualityType m_CollidableQualityType = CollidableQualityType.HK_COLLIDABLE_QUALITY_FIXED;
        [SerializeField]
        float m_Mass = 1.0f;
        [SerializeField]
        [Tooltip("这适用于物体的线速度，随时间减小。")]
        float m_LinearDamping = 0.01f;
        [SerializeField]
        [Tooltip("这适用于物体的角速度，随时间减小角速度。")]
        float m_AngularDamping = 0.05f;
        [SerializeField]
        [Tooltip("物体在世界空间中的初始线速度")]
        Vector3 m_InitialLinearVelocity = Vector3.zero;
        [SerializeField]
        [Tooltip("这表示在身体的局部运动空间（即围绕质心）中围绕每个轴的初始旋转速度")]
        Vector3 m_InitialAngularVelocity = Vector3.zero;
        [SerializeField]
        [Tooltip("此实体的重力量缩放系数。")]
        float m_GravityFactor = 1f;
        [SerializeField]
        public Vector3 m_CenterOfMass;
        [SerializeField]
        CustomPhysicsBodyTags m_CustomTags = CustomPhysicsBodyTags.Nothing;
        [Range(0, 1)]
        [Tooltip("使用此值可以指定刚体的初始摩擦力值。实体的“摩擦力”值指示其表面有多光滑，从而指示它沿其他实体滑动的容易程度。一般摩擦力值的范围在0和1之间，但可以更高（最大值为255）。默认值为0.5。")]
        public float m_Friction = 0.5f;
        [Range(0, 1.99f)]
        [Tooltip("这表明物体有多“弹性”——换句话说，物体与物体碰撞后有多少能量。值为1表示对象在碰撞后恢复其所有能量，值为0表示对象将完全停止移动。默认值为0.4。恢复的实现只是一个粗略的近似值，因此您可能希望在游戏中使用不同的值进行实验，以获得所需的效果。")]
        [SerializeField]
        private float m_Restitution = 0.4f;

        private IntPtr ptr = IntPtr.Zero;

        /// <summary>
        /// 获取或设置刚体的类型
        /// </summary>
        public MotionMotionType MotionType {
            get => m_MotionType; 
            set {
                if(m_MotionType != value) {
                    m_MotionType = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigdBodyMotionType(ptr, (int)Convert(m_MotionType));
                }
            }
        }
        /// <summary>
        /// 获取或设置刚体的碰撞质量（该值在创建刚体之后不能更改）
        /// </summary>
        public CollidableQualityType CollidableQualityType {
            get => m_CollidableQualityType; 
            set => m_CollidableQualityType = value;
        }
        /// <summary>
        /// 获取或设置刚体的初始初始旋转速度（该值在创建刚体之后不能更改）
        /// </summary>
        public Vector3 InitialAngularVelocity
        {
            get => m_InitialAngularVelocity;
            set => m_InitialAngularVelocity = value;
        }
        /// <summary>
        /// 获取或设置刚体的初始线速度（该值在创建刚体之后不能更改）
        /// </summary>
        public Vector3 InitialLinearVelocity
        {
            get => m_InitialLinearVelocity;
            set => m_InitialLinearVelocity = value;
        }
        /// <summary>
        /// 获取或设置刚体的质量
        /// </summary>
        public float Mass {
            get => m_Mass; 
            set {
                if(m_Mass != value) {
                    m_Mass = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigdBodyMass(ptr, value);
                }
            }
        }
        /// <summary>
        /// 获取或设置刚体的自定义标签
        /// </summary>
        public CustomPhysicsBodyTags CustomTags { get => m_CustomTags; set { m_CustomTags = value; } }
        /// <summary>
        /// 获取或设置刚体的质心
        /// </summary>
        public Vector3 CenterOfMass {
            get => m_CenterOfMass; 
            set {
                if(m_CenterOfMass != value) {
                    m_CenterOfMass = value; 
                    if(ptr != IntPtr.Zero) {
                        IntPtr vptr = PhysicsApi.API.CreateVec3(value.x, value.y, value.z);
                        PhysicsApi.API.SetRigdBodyCenterOfMass(ptr, vptr);
                        PhysicsApi.API.DestroyVec3(vptr);
                    }
                }
            }
        }
        /// <summary>
        /// 获取或设置刚体的重力系数
        /// </summary>
        public float GravityFactor {
            get => m_GravityFactor; 
            set {
                if(m_GravityFactor != value) {
                    m_GravityFactor = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigdBodyGravityFactor(ptr, m_GravityFactor);
                }
            }
        }
        /// <summary>
        /// 获取或设置刚体的线速度
        /// </summary>
        public float LinearDamping {
            get => m_LinearDamping; 
            set {
                if(m_LinearDamping != value) {
                    m_LinearDamping = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigdBodyLinearDampin(ptr, m_LinearDamping);
                }
            }
        }
        /// <summary>
        /// 获取或设置刚体的角速度
        /// </summary>
        public float AngularDamping {
            get => m_AngularDamping; 
            set {
                if(m_AngularDamping != value) {
                    m_AngularDamping = value; 
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigdBodyAngularDamping(ptr, m_AngularDamping);
                }
            }
        }
        /// <summary>
        /// 获取或设置刚体的摩擦力
        /// </summary>
        public float Friction {
            get => m_Friction; 
            set {
                if(m_Friction != value) {
                    m_Friction = value;
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigdBodyFriction(ptr, m_Friction);
                }
            }
        }
        /// <summary>
        /// 获取或设置刚体的弹力
        /// </summary>
        public float Restitution {
            get => m_Restitution; 
            set {
                if(m_Restitution != value) {
                    m_Restitution = value;
                    if(ptr != IntPtr.Zero)
                        PhysicsApi.API.SetRigdBodyRestitution(ptr, m_Restitution);
                }
            }
        }

        public PhysicsBody prev { get; set; }
        public PhysicsBody next { get; set; }

        /// <summary>
        /// 重新创建物理刚体，这将导致当前物理状态丢失
        /// </summary>
        public void ForceReCreateShape()
        {
            nextCreateForce = true;
            DestroyBody();
            CreateBody();
        }

        private void Awake() {
            CurrentPhysicsWorld = PhysicsWorld.GetCurrentScensePhysicsWorld();
            CreateBody();
        }
        private void OnDestroy() {
            DestroyBody();
        }

        private void OnEnable()
        {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.ActiveRigdBody(ptr);
        }
        private void OnDisable() 
        {
            if(ptr != IntPtr.Zero)
                PhysicsApi.API.DeactiveRigdBody(ptr);
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

        private IntPtr GetPtr() { return ptr; }
        private IntPtr GetShapeBody() {

            var shape = GetComponent<PhysicsShape>();
            if(shape == null)
            {
                Debug.LogWarning("Not found PhysicsShape on this gameObject, physical function has been disabled.");
                return IntPtr.Zero;
            }

            currentShapeMassProperties = shape.ComputeMassProperties(m_Mass);
            return shape.GetShapeBody(nextCreateForce);
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

            IntPtr posVec3Ptr = PhysicsApi.API.CreateVec3(transform.position.x, transform.position.y, transform.position.z);
            IntPtr rotVec4Ptr = PhysicsApi.API.CreateVec4(transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w);
            IntPtr linearVelocityVec3Ptr = PhysicsApi.API.CreateVec3(m_InitialLinearVelocity.x, m_InitialLinearVelocity.y, m_InitialLinearVelocity.z);
            IntPtr angularVelocityVec3Ptr = PhysicsApi.API.CreateVec3(m_InitialAngularVelocity.x, m_InitialAngularVelocity.y, m_InitialAngularVelocity.z);

            ptr = PhysicsApi.API.CreateRigdBody(
                CurrentPhysicsWorld.GetPtr(),
                GetShapeBody(), 
                posVec3Ptr, 
                rotVec4Ptr,
                Convert(m_MotionType),
                (int)m_CollidableQualityType,
                m_Friction,
                m_Restitution,
                m_Mass, 
                gameObject.activeSelf ? 1 : 0, 
                m_GravityFactor,
                m_LinearDamping,
                m_AngularDamping,
                linearVelocityVec3Ptr,
                angularVelocityVec3Ptr,
                currentShapeMassProperties);

            CurrentPhysicsWorld.AddBody(this);

            PhysicsApi.API.DestroyVec3(linearVelocityVec3Ptr);
            PhysicsApi.API.DestroyVec3(angularVelocityVec3Ptr);
            PhysicsApi.API.DestroyVec3(posVec3Ptr);
            PhysicsApi.API.DestroyVec4(rotVec4Ptr);

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
            PhysicsApi.API.DestroyRigdBody(CurrentPhysicsWorld.GetPtr(), ptr);
            ptr = IntPtr.Zero;
        }

    }
}