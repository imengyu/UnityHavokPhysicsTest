#include "stdafx.h"
#include "PhysicsHeader.h"
#include "PhysicsFunctions.h"

extern sInitStruct initStruct;

sPhysicsRigdbodyMassProperties* ComputeBoxSurfaceMassProperties(spVec4 halfExtents, float mass, float surfaceThickness) {
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeBoxSurfaceMassProperties(Vec4TohkVec4(halfExtents), mass, surfaceThickness, r->massProperties);
	return r;
}
sPhysicsRigdbodyMassProperties* ComputeBoxVolumeMassProperties(spVec4 halfExtents, float mass) {
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeBoxVolumeMassProperties(Vec4TohkVec4(halfExtents), mass, r->massProperties);
	return r;
}
sPhysicsRigdbodyMassProperties* ComputeCapsuleVolumeMassProperties(spVec4 startAxis, spVec4 endAxis, float radius, float mass) {
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeCapsuleVolumeMassProperties(Vec4TohkVec4(startAxis), Vec4TohkVec4(endAxis), radius, mass, r->massProperties);
	return r;
}
sPhysicsRigdbodyMassProperties* ComputeCylinderVolumeMassProperties(spVec4 startAxis, spVec4 endAxis, float radius, float mass) {
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeCylinderVolumeMassProperties(Vec4TohkVec4(startAxis), Vec4TohkVec4(endAxis), radius, mass, r->massProperties);
	return r;
}
sPhysicsRigdbodyMassProperties* ComputeSphereVolumeMassProperties(float radius, float sphereMass) {
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeSphereVolumeMassProperties(radius, sphereMass, r->massProperties);
	return r;
}
sPhysicsRigdbodyMassProperties* ComputeSphereSurfaceMassProperties(float radius, float mass, float surfaceThickness) {
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeSphereSurfaceMassProperties(radius, mass, surfaceThickness, r->massProperties);
	return r;
}
sPhysicsRigdbodyMassProperties* ComputeTriangleSurfaceMassProperties(spVec4 v0, spVec4 v1, spVec4 v2, float mass, float surfaceThickness) {
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeTriangleSurfaceMassProperties(Vec4TohkVec4(v0), Vec4TohkVec4(v1), Vec4TohkVec4(v2), mass, surfaceThickness, r->massProperties);
	return r;
}
sPhysicsRigdbodyMassProperties* ComputeShapeVolumeMassProperties(sPhysicsShape* shape, float mass) {
	sPhysicsRigdbodyMassProperties* r = new sPhysicsRigdbodyMassProperties();
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(shape->shape, mass, r->massProperties);
	return r;
}

sPhysicsRigdbody* CreateRigdBody(sPhysicsWorld* world, sPhysicsShape* shape, spVec3 position,
	int motionType, int qualityType, float friction, float restitution, float mass, int active,
	float gravityFactor, float linearDamping, float angularDamping,
	spVec3 linearVelocity, spVec3 angularVelocity, sPhysicsRigdbodyMassProperties* massProperties)
{
	hkpRigidBodyCinfo info;
	info.m_shape = shape->shape;
	info.m_position.set(position->x, position->y, position->z);
	info.m_motionType = (hkpMotion::MotionType)motionType;
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

	world->bodyList.add(body);
	return body;
}
void ActiveRigdBody(sPhysicsRigdbody* body)
{
	body->rigidBody->activate();
}
void DeactiveRigdBody(sPhysicsRigdbody* body)
{
	body->rigidBody->deactivate();
}
void SetRigdBodyMass(sPhysicsRigdbody* body, float mass)
{
	body->rigidBody->setMass(mass);
}
void SetRigdBodyFriction(sPhysicsRigdbody* body, float friction)
{
	body->rigidBody->setFriction(friction);
}
void SetRigdBodyMotionType(sPhysicsRigdbody* body, int newState)
{
	body->rigidBody->setMotionType((hkpMotion::MotionType)newState);
}
void SetRigdBodyRestitution(sPhysicsRigdbody* body, float restitution)
{
	body->rigidBody->setRestitution(restitution);
}
void SetRigdBodyAngularDamping(sPhysicsRigdbody* body, float angularDamping)
{
	body->rigidBody->setAngularDamping(angularDamping);
}
void SetRigdBodyLinearDampin(sPhysicsRigdbody* body, float linearDamping)
{
	body->rigidBody->setLinearDamping(linearDamping);
}
void SetRigdBodyCenterOfMass(sPhysicsRigdbody* body, spVec3 centerOfMass)
{
	body->rigidBody->setCenterOfMassLocal(hkVector4(centerOfMass->x, centerOfMass->y, centerOfMass->z));
}
void SetRigdBodyPosition(sPhysicsRigdbody* body, spVec3 pos)
{
	body->rigidBody->setPosition(hkVector4(pos->x, pos->y, pos->z));
}
void SetRigdBodyPositionAndRotation(sPhysicsRigdbody* body, spVec3 pos, spVec4 roate)
{
	body->rigidBody->setPositionAndRotation(
		hkVector4(pos->x, pos->y, pos->z),
		hkQuaternion(roate->x, roate->y, roate->z, roate->w)
	);
}
void DestroyRigdBody(sPhysicsWorld* world, sPhysicsRigdbody*body)
{
	if (initStruct.mulithread) world->physicsWorld->markForWrite();
	world->physicsWorld->removeEntity(body->rigidBody);
	if (initStruct.mulithread) world->physicsWorld->unmarkForWrite();

	world->bodyList.remove(body);
	delete body;
}