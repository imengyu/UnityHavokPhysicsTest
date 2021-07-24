
using System;
using UnityEngine;

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

[AddComponentMenu("PhysicsRT/Physics Body")]
[DefaultExecutionOrder(150)]
[DisallowMultipleComponent]
public class PhysicsBody : MonoBehaviour {

    const float MinimumMass = 0.001f;

    private hkpMotionMotionType Convert(MotionMotionType m) {
        switch(m) {
            case MotionMotionType.BoxInertia: return hkpMotionMotionType.MOTION_BOX_INERTIA;
            case MotionMotionType.Character: return hkpMotionMotionType.MOTION_CHARACTER;
            case MotionMotionType.Dynamic: return hkpMotionMotionType.MOTION_DYNAMIC;
            case MotionMotionType.Fixed: return hkpMotionMotionType.MOTION_FIXED;
            case MotionMotionType.Keyframed: return hkpMotionMotionType.MOTION_KEYFRAMED;
            case MotionMotionType.SphereInertia: return hkpMotionMotionType.MOTION_SPHERE_INERTIA;
            case MotionMotionType.ThinBoxInertia: return hkpMotionMotionType.MOTION_THIN_BOX_INERTIA;
        }
        return hkpMotionMotionType.MOTION_INVALID;
    }

    [SerializeField]
    MotionMotionType m_MotionType = MotionMotionType.Fixed;
    [SerializeField]
    float m_Mass = 1.0f;
    [SerializeField]
    [Tooltip("This is applied to a body's linear velocity reducing it over time.")]
    float m_LinearDamping = 0.01f;
    [SerializeField]
    [Tooltip("This is applied to a body's angular velocity reducing it over time.")]
    float m_AngularDamping = 0.05f;
    [SerializeField]
    [Tooltip("The initial linear velocity of the body in world space")]
    Vector3 m_InitialLinearVelocity = Vector3.zero;
    [SerializeField]
    [Tooltip("This represents the initial rotation speed around each axis in the local motion space of the body i.e. around the center of mass")]
    Vector3 m_InitialAngularVelocity = Vector3.zero;
    [SerializeField]
    [Tooltip("Scales the amount of gravity to apply to this body.")]
    float m_GravityFactor = 1f;
    [SerializeField]
    public Vector3 m_CenterOfMass;
    [SerializeField]
    CustomPhysicsBodyTags m_CustomTags = CustomPhysicsBodyTags.Nothing;
    [Range(0, 1)]
    [Tooltip("You use this value to specify an initial friction value for the hkpRigidBody. A body’s friction value indicates how smooth its surface is and hence how easily it will slide along other bodies. General friction values range between 0 and 1, but can be higher (a maximum of 255) The default value is 0.5.")]
    public float m_Friction = 0.5f;
    [Range(0, 1.99f)]
    [Tooltip("This indicates how \"bouncy\" the object is - in other words, how much energy it has after colliding with something. A value of 1 means that the object gets all its energy back after a collision, a value of 0 means that it will stop moving completely. The default value is 0.4. You can see the effects of changing restitution values in the RestitutionApi demo. The implementation of the restitution is only a rough approximation, therefore you might want to experiment with different values in your game to get the desired effect.")]
    [SerializeField]
    private float m_Restitution = 0.4f;

    private IntPtr ptr = IntPtr.Zero;

    public IntPtr Ptr => ptr;
    public MotionMotionType MotionType {
        get => m_MotionType; 
        set {
            if(m_MotionType != value) {
                m_MotionType = value; 
                PhysicsApi.hkpRigidBody_setMotionType(ptr, Convert(m_MotionType));
            }
        }
    }
    public float Mass {
        get => m_Mass; 
        set {
            if(m_Mass != value) {
                m_Mass = value; 
                PhysicsApi.hkpRigidBody_setMass(ptr, value);
            }
        }
    }
    public CustomPhysicsBodyTags CustomTags { get => m_CustomTags; set { m_CustomTags = value; } }
    public Vector3 CenterOfMass {
        get => m_CenterOfMass; 
        set {
            if(m_CenterOfMass != value) {
                m_CenterOfMass = value; 
                using(var v = new hkVector4(m_CenterOfMass))
                    PhysicsApi.hkpRigidBody_setCenterOfMassLocal(ptr, v.Ptr);
            }
        }
    }
    public float GravityFactor {
        get => m_GravityFactor; 
        set {
            if(m_GravityFactor != value) {
                m_GravityFactor = value; 
                using(var v = new hkVector4(m_CenterOfMass))
                    PhysicsApi.hkpRigidBody_setGravityFactor(ptr, m_GravityFactor);
            }
        }
    }
    public float LinearDamping {
        get => m_LinearDamping; 
        set {
            if(m_LinearDamping != value) {
                m_LinearDamping = value; 
                PhysicsApi.hkpRigidBody_setLinearDamping(ptr, m_LinearDamping);
            }
        }
    }
    public float AngularDamping {
        get => m_AngularDamping; 
        set {
            if(m_AngularDamping != value) {
                m_AngularDamping = value; 
                PhysicsApi.hkpRigidBody_setAngularDamping(ptr, m_AngularDamping);
            }
        }
    }
    public float Friction {
        get => m_Friction; 
        set {
            if(m_Friction != value) {
                m_Friction = value;
                PhysicsApi.hkpRigidBody_setFriction(ptr, m_Friction);
            }
        }
    }
    public float Restitution {
        get => m_Restitution; 
        set {
            if(m_Restitution != value) {
                m_Restitution = value;
                PhysicsApi.hkpRigidBody_setRestitution(ptr, m_Restitution);
            }
        }
    }


    private void Awake() {
        CreateBody();
    }
    private void OnDestroy() {
        DestroyBody();
    }

    private void OnEnable()
    {
        if(ptr != IntPtr.Zero)
            PhysicsApi.hkpEntity_activate(ptr);
    }
    private void OnDisable() 
    {
        if(ptr != IntPtr.Zero)
            PhysicsApi.hkpEntity_deactivate(ptr);
    }
    private void OnValidate()
    {
        Mass = Mathf.Max(MinimumMass, Mass);
        m_LinearDamping = Mathf.Max(m_LinearDamping, 0f);
        m_AngularDamping = Mathf.Max(m_AngularDamping, 0f);
    }
    
    private IntPtr GetShapeBody() {


        return IntPtr.Zero;
    }
    private void CreateBody() {
        if(PhysicsWorld.Inastance == null)
            return;

        ptr = PhysicsApi.hkpRigidBody_new(
            GetShapeBody(), 
            new hkVector4(transform.position).Ptr, 
            m_Mass, 
            Convert(m_MotionType), 
            hkpCollidableQualityType.HK_COLLIDABLE_QUALITY_INVALID, 
            m_LinearDamping,
            m_AngularDamping,
            new hkVector4(m_InitialLinearVelocity).Ptr,
            new hkVector4(m_InitialAngularVelocity).Ptr,
            m_GravityFactor);
        
        using(var v = new hkVector4(m_CenterOfMass))
            PhysicsApi.hkpRigidBody_setCenterOfMassLocal(ptr, v.Ptr);
        PhysicsApi.hkpRigidBody_setFriction(ptr, m_Friction);
        PhysicsApi.hkpRigidBody_setRestitution(ptr, m_Restitution);

        PhysicsWorld.Inastance.AddBody(this);
    }
    private void DestroyBody() {
        if(PhysicsWorld.Inastance == null || ptr == IntPtr.Zero)
            return;

        PhysicsWorld.Inastance.RemoveBody(this);
        PhysicsApi.hkpEntity_removeReference(ptr);
        ptr = IntPtr.Zero;
    }

}