#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"

struct sPhysicsWorld;
struct sPhysicsShape;

class MyCollisionResolution;
struct sPhysicsRigidbody {
	hkpRigidBody* rigidBody;
	sPhysicsWorld* world;
	unsigned int id;
	int active;
	struct sPhysicsRigidbody* prev;
	struct sPhysicsRigidbody* next;
	MyCollisionResolution* collisionListener;
};
struct sPhysicsRigidbodyMassProperties {
	hkMassProperties massProperties;
};

sPhysicsRigidbody* CreateRigidBody(sPhysicsWorld* world, sPhysicsShape* shape, spVec3 position, spVec4 rotation,
	int motionType, int qualityType, float friction, float restitution, float mass, int active, int layer, int isTiggerVolume, int addContactListener,
	float gravityFactor, float linearDamping, float angularDamping, spVec3 centerOfMass, spMatrix4 inertiaTensor,
	spVec3 linearVelocity, spVec3 angularVelocity, float maxLinearVelocity, float maxAngularVelocity, sPhysicsRigidbodyMassProperties* massProperties);
int GetRigidBodyId(sPhysicsRigidbody* body);
void ActiveRigidBody(sPhysicsRigidbody* body);
void DeactiveRigidBody(sPhysicsRigidbody* body);
void SetRigidBodyMass(sPhysicsRigidbody* body, float mass);
void SetRigidBodyFriction(sPhysicsRigidbody* body, float friction);
void SetRigidBodyMotionType(sPhysicsRigidbody* body, int newState);
void SetRigidBodyLayer(sPhysicsRigidbody* body, int layer);
void SetRigidBodyRestitution(sPhysicsRigidbody* body, float restitution);
void SetRigidBodyAngularDamping(sPhysicsRigidbody* body, float angularDamping);
void SetRigidBodyLinearDampin(sPhysicsRigidbody* body, float linearDamping);
void SetRigidBodyLinearVelocity(sPhysicsRigidbody* body, spVec3 v);
void SetRigidBodyAngularVelocity(sPhysicsRigidbody* body, spVec3 v);
void SetRigidBodyCenterOfMass(sPhysicsRigidbody* body, spVec3 centerOfMass);
void SetRigidBodyInertiaTensor(sPhysicsRigidbody* body, spMatrix4 inertiaTensor);
void SetRigidBodyGravityFactor(sPhysicsRigidbody* body, float gravityFactor);
void SetRigidBodyPosition(sPhysicsRigidbody* body, spVec3 pos);
void SetRigidBodyPositionAndRotation(sPhysicsRigidbody* body, spVec3 pos, spVec4 rotation);
void DestroyRigidBody(sPhysicsRigidbody* body);
void GetRigidBodyPosition(sPhysicsRigidbody* body, spVec3 outPos);
void GetRigidBodyRotation(sPhysicsRigidbody* body, spVec4 outRot);
void GetRigidBodyAngularVelocity(sPhysicsRigidbody* body, spVec3 outPos);
void GetRigidBodyLinearVelocity(sPhysicsRigidbody* body, spVec3 outPos);
void GetRigidBodyCenterOfMassInWorld(sPhysicsRigidbody* body, spVec3 outPos);
void GetRigidBodyPointVelocity(sPhysicsRigidbody* body, spVec3 pt, spVec3 outPos);
void RigidBodyResetCenterOfMass(sPhysicsRigidbody* body);
void RigidBodyResetInertiaTensor(sPhysicsRigidbody* body);
void SetRigidBodyMaxLinearVelocity(sPhysicsRigidbody* body, float v);
void SetRigidBodyMaxAngularVelocity(sPhysicsRigidbody* body, float v);
void RigidBodyApplyForce(sPhysicsRigidbody* body, float delteTime, spVec3 force);
void RigidBodyApplyForceAtPoint(sPhysicsRigidbody* body, float delteTime, spVec3 force, spVec3 point);
void RigidBodyApplyTorque(sPhysicsRigidbody* body, float delteTime, spVec3 torque);
void RigidBodyApplyAngularImpulse(sPhysicsRigidbody* body, spVec3 imp);
void RigidBodyApplyLinearImpulse(sPhysicsRigidbody* body, spVec3 imp);
void RigidBodyApplyPointImpulse(sPhysicsRigidbody* body, spVec3 imp, spVec3 point);

sPhysicsRigidbodyMassProperties* ComputeShapeVolumeMassProperties(sPhysicsShape* shape, float mass);
sPhysicsRigidbodyMassProperties* ComputeBoxSurfaceMassProperties(spVec4 halfExtents, float mass, float surfaceThickness);
sPhysicsRigidbodyMassProperties* ComputeBoxVolumeMassProperties(spVec4 halfExtents, float mass);
sPhysicsRigidbodyMassProperties* ComputeCapsuleVolumeMassProperties(spVec4 startAxis, spVec4 endAxis, float radius, float mass);
sPhysicsRigidbodyMassProperties* ComputeCylinderVolumeMassProperties(spVec4 startAxis, spVec4 endAxis, float radius, float mass);
sPhysicsRigidbodyMassProperties* ComputeSphereVolumeMassProperties(float radius, float sphereMass);
sPhysicsRigidbodyMassProperties* ComputeSphereSurfaceMassProperties(float radius, float mass, float surfaceThickness);
sPhysicsRigidbodyMassProperties* ComputeTriangleSurfaceMassProperties(spVec4 v0, spVec4 v1, spVec4 v2, float mass, float surfaceThickness);