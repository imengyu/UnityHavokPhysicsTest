#include "stdafx.h"
#include "PhysicsHeader.h"
#include "PhysicsFunctions.h"

extern sInitStruct initStruct;
unsigned int sPhysicsRigdbodyId = 0;

sPhysicsRigdbodyMassProperties* ComputeBoxSurfaceMassProperties(spVec4 halfExtents, float mass, float surfaceThickness) {
	TRY_BEGIN

	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeBoxSurfaceMassProperties(Vec4TohkVec4(halfExtents), mass, surfaceThickness, r->massProperties);
	return r;

	TRY_END(nullptr)
}
sPhysicsRigdbodyMassProperties* ComputeBoxVolumeMassProperties(spVec4 halfExtents, float mass) {
	TRY_BEGIN
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(Vec4TohkVec4(halfExtents), mass, r->massProperties);
	return r;
	TRY_END(nullptr)
}
sPhysicsRigdbodyMassProperties* ComputeCapsuleVolumeMassProperties(spVec4 startAxis, spVec4 endAxis, float radius, float mass) {
	TRY_BEGIN
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeCapsuleVolumeMassProperties(Vec4TohkVec4(startAxis), Vec4TohkVec4(endAxis), radius, mass, r->massProperties);
	return r;
	TRY_END(nullptr)
}
sPhysicsRigdbodyMassProperties* ComputeCylinderVolumeMassProperties(spVec4 startAxis, spVec4 endAxis, float radius, float mass) {
	TRY_BEGIN
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeCylinderVolumeMassProperties(Vec4TohkVec4(startAxis), Vec4TohkVec4(endAxis), radius, mass, r->massProperties);
	return r;
	TRY_END(nullptr)
}
sPhysicsRigdbodyMassProperties* ComputeSphereVolumeMassProperties(float radius, float sphereMass) {
	TRY_BEGIN
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeSphereVolumeMassProperties(radius, sphereMass, r->massProperties);
	return r;
	TRY_END(nullptr)
}
sPhysicsRigdbodyMassProperties* ComputeSphereSurfaceMassProperties(float radius, float mass, float surfaceThickness) {
	TRY_BEGIN
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeSphereSurfaceMassProperties(radius, mass, surfaceThickness, r->massProperties);
	return r;
	TRY_END(nullptr)
}
sPhysicsRigdbodyMassProperties* ComputeTriangleSurfaceMassProperties(spVec4 v0, spVec4 v1, spVec4 v2, float mass, float surfaceThickness) {
	TRY_BEGIN
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeTriangleSurfaceMassProperties(Vec4TohkVec4(v0), Vec4TohkVec4(v1), Vec4TohkVec4(v2), mass, surfaceThickness, r->massProperties);
	return r;
	TRY_END(nullptr)
}
sPhysicsRigdbodyMassProperties* ComputeShapeVolumeMassProperties(sPhysicsShape* shape, float mass) {
	TRY_BEGIN
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(shape->shape, mass, r->massProperties);
	return r;
	TRY_END(nullptr)
}

sPhysicsRigdbody* CreateRigdBody(sPhysicsWorld* world, sPhysicsShape* shape, spVec3 position, spVec4 rotation,
	int motionType, int qualityType, float friction, float restitution, float mass, int active,
	float gravityFactor, float linearDamping, float angularDamping,
	spVec3 linearVelocity, spVec3 angularVelocity, sPhysicsRigdbodyMassProperties* massProperties)
{
	TRY_BEGIN

	hkpRigidBodyCinfo info;
	info.m_shape = shape->shape;
	info.m_position.set(position->x, position->y, position->z);
	info.m_rotation = hkQuaternion(rotation->x, rotation->y, rotation->z, rotation->w);
	info.m_motionType = (hkpMotion::MotionType)motionType;;
	info.m_qualityType = (hkpCollidableQualityType)qualityType;
	info.m_linearDamping = linearDamping;
	info.m_angularDamping = angularDamping;
	info.m_gravityFactor = gravityFactor;
	info.m_friction = friction;
	info.m_restitution = restitution;
	info.m_mass = mass;
	
	info.m_angularVelocity = hkVector4(angularVelocity->x, angularVelocity->y, angularVelocity->z);
	info.m_linearVelocity = hkVector4(linearVelocity->x, linearVelocity->y, linearVelocity->z);

	if (massProperties) {
		info.m_centerOfMass = massProperties->massProperties.m_centerOfMass;
		info.m_inertiaTensor = massProperties->massProperties.m_inertiaTensor;
		info.m_mass = massProperties->massProperties.m_mass;
	}
	else {
		info.m_mass = mass;
	}

	hkpRigidBody* newRigidBody = new hkpRigidBody(info);

	if(initStruct.mulithread) world->physicsWorld->markForWrite();
	world->physicsWorld->addEntity(newRigidBody, active ? HK_ENTITY_ACTIVATION_DO_ACTIVATE : HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE);
	newRigidBody->removeReference();
	if (initStruct.mulithread) world->physicsWorld->unmarkForWrite();

	sPhysicsRigdbody* body = new sPhysicsRigdbody();
	body->rigidBody = newRigidBody; 
	body->active = active;
	body->id = ++sPhysicsRigdbodyId;

	world->bodyList.add(body);
	return body;
	TRY_END(nullptr)
}
void ActiveRigdBody(sPhysicsRigdbody* body)
{
	TRY_BEGIN
	body->rigidBody->activate();
	body->active = true;
	TRY_END_NORET
}
void DeactiveRigdBody(sPhysicsRigdbody* body)
{
	TRY_BEGIN
	body->rigidBody->requestDeactivation();
	body->active = false;
	TRY_END_NORET
}
void SetRigdBodyMass(sPhysicsRigdbody* body, float mass)
{
	TRY_BEGIN
	body->rigidBody->setMass(mass);
	TRY_END_NORET
}
void SetRigdBodyFriction(sPhysicsRigdbody* body, float friction)
{
	TRY_BEGIN
	body->rigidBody->setFriction(friction);
	TRY_END_NORET
}
void SetRigdBodyMotionType(sPhysicsRigdbody* body, int newState)
{
	TRY_BEGIN
	body->rigidBody->setMotionType((hkpMotion::MotionType)newState);
	TRY_END_NORET
}
void SetRigdBodyRestitution(sPhysicsRigdbody* body, float restitution)
{
	TRY_BEGIN
	body->rigidBody->setRestitution(restitution);
	TRY_END_NORET
}
void SetRigdBodyAngularDamping(sPhysicsRigdbody* body, float angularDamping)
{
	TRY_BEGIN
	body->rigidBody->setAngularDamping(angularDamping);
	TRY_END_NORET
}
void SetRigdBodyLinearDampin(sPhysicsRigdbody* body, float linearDamping)
{
	TRY_BEGIN
	body->rigidBody->setLinearDamping(linearDamping);
	TRY_END_NORET
}
void SetRigdBodyCenterOfMass(sPhysicsRigdbody* body, spVec3 centerOfMass)
{
	TRY_BEGIN
	body->rigidBody->setCenterOfMassLocal(hkVector4(centerOfMass->x, centerOfMass->y, centerOfMass->z));
	TRY_END_NORET
}
void SetRigdBodyGravityFactor(sPhysicsRigdbody* body, float gravityFactor)
{
	TRY_BEGIN
	body->rigidBody->setGravityFactor(gravityFactor);
	TRY_END_NORET
}
void SetRigdBodyPosition(sPhysicsRigdbody* body, spVec3 pos)
{
	TRY_BEGIN
	body->rigidBody->setPosition(hkVector4(pos->x, pos->y, pos->z));
	TRY_END_NORET
}
void SetRigdBodyPositionAndRotation(sPhysicsRigdbody* body, spVec3 pos, spVec4 roate)
{
	TRY_BEGIN
	body->rigidBody->setPositionAndRotation(
		hkVector4(pos->x, pos->y, pos->z),
		hkQuaternion(roate->x, roate->y, roate->z, roate->w)
	);
	TRY_END_NORET
}
void DestroyRigdBody(sPhysicsWorld* world, sPhysicsRigdbody*body)
{
	TRY_BEGIN
	if (initStruct.mulithread) world->physicsWorld->markForWrite();
	world->physicsWorld->removeEntity(body->rigidBody);
	if (initStruct.mulithread) world->physicsWorld->unmarkForWrite();

	world->bodyList.remove(body);
	delete body;
	TRY_END_NORET
}