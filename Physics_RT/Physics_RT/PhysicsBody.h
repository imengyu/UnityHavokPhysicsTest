#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"

struct sPhysicsWorld;
struct sPhysicsShape;

struct sPhysicsRigdbody {
	hkpRigidBody* rigidBody;
	sPhysicsWorld* world;
	unsigned int id;
	int active;
	struct sPhysicsRigdbody* prev;
	struct sPhysicsRigdbody* next;
};
struct sPhysicsRigdbodyMassProperties {
	hkMassProperties massProperties;
};

sPhysicsRigdbody* CreateRigdBody(sPhysicsWorld* world, sPhysicsShape* shape, spVec3 position, spVec4 rotation,
	int motionType, int qualityType, float friction, float restitution, float mass, int active, int layer,
	float gravityFactor, float linearDamping, float angularDamping,
	spVec3 linearVelocity, spVec3 angularVelocity, sPhysicsRigdbodyMassProperties* massProperties);
void ActiveRigdBody(sPhysicsRigdbody* body);
void DeactiveRigdBody(sPhysicsRigdbody* body);
void SetRigdBodyMass(sPhysicsRigdbody* body, float mass);
void SetRigdBodyFriction(sPhysicsRigdbody* body, float friction);
void SetRigdBodyMotionType(sPhysicsRigdbody* body, int newState);
void SetRigdBodyRestitution(sPhysicsRigdbody* body, float restitution);
void SetRigdBodyCenterOfMass(sPhysicsRigdbody* body, spVec3 centerOfMass);
void SetRigdBodyLayer(sPhysicsRigdbody* body, int layer);
void SetRigdBodyPosition(sPhysicsRigdbody* body, spVec3 pos);
void SetRigdBodyPositionAndRotation(sPhysicsRigdbody* body, spVec3 pos, spVec4 roate);
void SetRigdBodyAngularDamping(sPhysicsRigdbody* body, float angularDamping);
void SetRigdBodyLinearDampin(sPhysicsRigdbody* body, float linearDamping);
void SetRigdBodyGravityFactor(sPhysicsRigdbody* body, float gravityFactor);
void DestroyRigdBody(sPhysicsRigdbody* body);

sPhysicsRigdbodyMassProperties* ComputeShapeVolumeMassProperties(sPhysicsShape* shape, float mass);
sPhysicsRigdbodyMassProperties* ComputeBoxSurfaceMassProperties(spVec4 halfExtents, float mass, float surfaceThickness);
sPhysicsRigdbodyMassProperties* ComputeBoxVolumeMassProperties(spVec4 halfExtents, float mass);
sPhysicsRigdbodyMassProperties* ComputeCapsuleVolumeMassProperties(spVec4 startAxis, spVec4 endAxis, float radius, float mass);
sPhysicsRigdbodyMassProperties* ComputeCylinderVolumeMassProperties(spVec4 startAxis, spVec4 endAxis, float radius, float mass);
sPhysicsRigdbodyMassProperties* ComputeSphereVolumeMassProperties(float radius, float sphereMass);
sPhysicsRigdbodyMassProperties* ComputeSphereSurfaceMassProperties(float radius, float mass, float surfaceThickness);
sPhysicsRigdbodyMassProperties* ComputeTriangleSurfaceMassProperties(spVec4 v0, spVec4 v1, spVec4 v2, float mass, float surfaceThickness);