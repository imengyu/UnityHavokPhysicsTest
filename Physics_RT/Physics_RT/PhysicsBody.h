#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"

struct sPhysicsWorld;
struct sPhysicsShape;

struct sPhysicsRigdbody {
	hkpRigidBody* rigidBody;
	unsigned int id;
	struct sPhysicsRigdbody* prev;
	struct sPhysicsRigdbody* next;
};
struct sPhysicsRigdbodyMassProperties {
	hkMassProperties massProperties;
};

typedef sPhysicsRigdbody* (__cdecl* fnCreateRigdBody)(sPhysicsWorld* world, sPhysicsShape* shape, spVec3 position,
	int motionType, int qualityType, float friction, float restitution, float mass, int active,
	float gravityFactor, float linearDamping, float angularDamping,
	spVec3 linearVelocity, spVec3 angularVelocity, sPhysicsRigdbodyMassProperties* massProperties);
typedef void(__cdecl* fnActiveRigdBody)(sPhysicsRigdbody* body);
typedef void(__cdecl* fnDeactiveRigdBody)(sPhysicsRigdbody* body);
typedef void(__cdecl* fnSetRigdBodyMass)(sPhysicsRigdbody* body, float mass);
typedef void(__cdecl* fnSetRigdBodyFriction)(sPhysicsRigdbody* body, float friction);
typedef void(__cdecl* fnSetRigdBodyRestitution)(sPhysicsRigdbody* body, float restitution);
typedef void(__cdecl* fnSetRigdBodyCenterOfMass)(sPhysicsRigdbody* body, spVec3 centerOfMass);
typedef void(__cdecl* fnSetRigdBodyPosition)(sPhysicsRigdbody* body, spVec3 pos);
typedef void(__cdecl* fnSetRigdBodyPositionAndRotation)(sPhysicsRigdbody* body, spVec3 pos, spVec4 roate);
typedef void(__cdecl* fnSetRigdBodyAngularDamping)(sPhysicsRigdbody* body, float angularDamping);
typedef void(__cdecl* fnSetRigdBodyLinearDampin)(sPhysicsRigdbody* body, float linearDamping);
typedef void(__cdecl* fnDestroyRigdBody)(sPhysicsWorld* world, sPhysicsRigdbody* body);
typedef void(__cdecl* fnSetRigdBodyMotionType)(sPhysicsRigdbody* body, int newState);
typedef void(__cdecl* fnSetRigdBodyGravityFactor)(sPhysicsRigdbody* body, float gravityFactor);

sPhysicsRigdbody* CreateRigdBody(sPhysicsWorld* world, sPhysicsShape* shape, spVec3 position,
	int motionType, int qualityType, float friction, float restitution, float mass, int active,
	float gravityFactor, float linearDamping, float angularDamping,
	spVec3 linearVelocity, spVec3 angularVelocity, sPhysicsRigdbodyMassProperties* massProperties);
void ActiveRigdBody(sPhysicsRigdbody* body);
void DeactiveRigdBody(sPhysicsRigdbody* body);
void SetRigdBodyMass(sPhysicsRigdbody* body, float mass);
void SetRigdBodyFriction(sPhysicsRigdbody* body, float friction);
void SetRigdBodyMotionType(sPhysicsRigdbody* body, int newState);
void SetRigdBodyRestitution(sPhysicsRigdbody* body, float restitution);
void SetRigdBodyCenterOfMass(sPhysicsRigdbody* body, spVec3 centerOfMass);
void SetRigdBodyPosition(sPhysicsRigdbody* body, spVec3 pos);
void SetRigdBodyPositionAndRotation(sPhysicsRigdbody* body, spVec3 pos, spVec4 roate);
void SetRigdBodyAngularDamping(sPhysicsRigdbody* body, float angularDamping);
void SetRigdBodyLinearDampin(sPhysicsRigdbody* body, float linearDamping);
void SetRigdBodyGravityFactor(sPhysicsRigdbody* body, float gravityFactor);
void DestroyRigdBody(sPhysicsWorld* world, sPhysicsRigdbody* body);

typedef sPhysicsRigdbodyMassProperties* (__cdecl* fnComputeShapeVolumeMassProperties)(sPhysicsShape* shape, float mass);
typedef sPhysicsRigdbodyMassProperties* (__cdecl* fnComputeBoxSurfaceMassProperties)(spVec4 halfExtents, float mass, float surfaceThickness);
typedef sPhysicsRigdbodyMassProperties* (__cdecl* fnComputeBoxVolumeMassProperties)(spVec4 halfExtents, float mass);
typedef sPhysicsRigdbodyMassProperties* (__cdecl* fnComputeCapsuleVolumeMassProperties)(spVec4 startAxis, spVec4 endAxis, float radius, float mass);
typedef sPhysicsRigdbodyMassProperties* (__cdecl* fnComputeCylinderVolumeMassProperties)(spVec4 startAxis, spVec4 endAxis, float radius, float mass);
typedef sPhysicsRigdbodyMassProperties* (__cdecl* fnComputeSphereVolumeMassProperties)(float radius, float sphereMass);
typedef sPhysicsRigdbodyMassProperties* (__cdecl* fnComputeSphereSurfaceMassProperties)(float radius, float mass, float surfaceThickness);
typedef sPhysicsRigdbodyMassProperties* (__cdecl* fnComputeTriangleSurfaceMassProperties)(spVec4 v0, spVec4 v1, spVec4 v2, float mass, float surfaceThickness);

sPhysicsRigdbodyMassProperties* ComputeShapeVolumeMassProperties(sPhysicsShape* shape, float mass);
sPhysicsRigdbodyMassProperties* ComputeBoxSurfaceMassProperties(spVec4 halfExtents, float mass, float surfaceThickness);
sPhysicsRigdbodyMassProperties* ComputeBoxVolumeMassProperties(spVec4 halfExtents, float mass);
sPhysicsRigdbodyMassProperties* ComputeCapsuleVolumeMassProperties(spVec4 startAxis, spVec4 endAxis, float radius, float mass);
sPhysicsRigdbodyMassProperties* ComputeCylinderVolumeMassProperties(spVec4 startAxis, spVec4 endAxis, float radius, float mass);
sPhysicsRigdbodyMassProperties* ComputeSphereVolumeMassProperties(float radius, float sphereMass);
sPhysicsRigdbodyMassProperties* ComputeSphereSurfaceMassProperties(float radius, float mass, float surfaceThickness);
sPhysicsRigdbodyMassProperties* ComputeTriangleSurfaceMassProperties(spVec4 v0, spVec4 v1, spVec4 v2, float mass, float surfaceThickness);