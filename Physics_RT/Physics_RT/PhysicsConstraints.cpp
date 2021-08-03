#include "stdafx.h"
#include "PhysicsHeader.h"
#include "PhysicsFunctions.h"

#include <Physics/Constraint/Data/BallAndSocket/hkpBallAndSocketConstraintData.h>
#include <Physics/Constraint/Data/Fixed/hkpFixedConstraintData.h>
#include <Physics/Constraint/Data/Hinge/hkpHingeConstraintData.h>
#include <Physics/Constraint/Data/LimitedHinge/hkpLimitedHingeConstraintData.h>
#include <Physics/Constraint/Data/PointToPath/hkpPointToPathConstraintData.h>
#include <Physics/Constraint/Data/PointToPlane/hkpPointToPlaneConstraintData.h>
#include <Physics/Constraint/Data/Prismatic/hkpPrismaticConstraintData.h>
#include <Physics/Constraint/Data/Pulley/hkpPulleyConstraintData.h>
#include <Physics/Constraint/Data/Wheel/hkpWheelConstraintData.h>
#include <Physics/Constraint/Data/WheelFriction/hkpWheelFrictionConstraintData.h>
#include <Physics/Constraint/Data/CogWheel/hkpCogWheelConstraintData.h>
#include <Physics/Constraint/Data/StiffSpring/hkpStiffSpringConstraintData.h>

void SetupWorldConstraintListener(sPhysicsWorld* world) {
	auto listener = new MyBreakableListener(world);
	world->physicsWorld->addConstraintListener(listener);
}
void DestroyWorldConstraintListener(sPhysicsWorld* world) {
	if (world->breakableListener) {
		world->physicsWorld->removeConstraintListener(world->breakableListener);
		delete world->breakableListener;
		world->breakableListener = nullptr;
	}
}

void CreateConstraintCheck(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody) {
	CHECK_PARAM_PTR(body);
	CHECK_PARAM_PTR(otherBody);

	if (!body->world->physicsWorld)
		throw std::exception("physicsWorld is destroyed");
	if (body->world->physicsWorld != otherBody->world->physicsWorld)
		throw std::exception("Two bodies belong to different worlds");
}
sPhysicsConstraints* CreateConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, hkpConstraintData* data, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse) {
	auto rs = new sPhysicsConstraints();

	if (breakable) {

		hkpBreakableConstraintData* breaker = new hkpBreakableConstraintData(data);
		breaker->setThreshold(10); 
		breaker->setRemoveWhenBroken(false); 
		breaker->setMaximumAngularImpulse(maximumAngularImpulse);
		breaker->setMaximumLinearImpulse(maximumLinearImpulse);
		data->removeReference();

		rs->instance = body->world->physicsWorld->createAndAddConstraintInstance(body->rigidBody, body->rigidBody, breaker);
		rs->instance->removeReference();
		rs->instance->setUserData((hkUlong)rs);
		rs->breaker = breaker;
	}
	else {
		rs->instance = body->world->physicsWorld->createAndAddConstraintInstance(body->rigidBody, body->rigidBody, data);
		rs->instance->removeReference();
	}
	rs->world = body->world;
	rs->breakable = breakable;

	data->removeReference();

	return rs;
}

void DestoryConstraints(sPhysicsConstraints* constraint) {
	TRY_BEGIN
		CHECK_PARAM_PTR(constraint);

	if (!constraint->world->physicsWorld) {
		delete constraint;
		throw std::exception("physicsWorld is destroyed");
	}

	constraint->world->physicsWorld->removeConstraint(constraint->instance);
	delete constraint;

	TRY_END_NORET
}
int IsConstraintBroken(sPhysicsConstraints* constraint)
{
	if (constraint && constraint->breakable)
		return constraint->breaker->getIsBroken(constraint->instance);
	return false;
}
void SetConstraintBroken(sPhysicsConstraints* constraint, bool broken, float force)
{
	TRY_BEGIN
		CHECK_PARAM_PTR(constraint)

	if (constraint->breakable)
		return constraint->breaker->setBroken(constraint->instance, broken, force);
	else 
		throw std::exception("constraint is not breakable");

	TRY_END_NORET
}
sPhysicsConstraints* CreateBallAndSocketConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 povit, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse)
{
	TRY_BEGIN
		
	CreateConstraintCheck(body, otherBody);


	// Create the constraint
	auto data = new hkpBallAndSocketConstraintData();
	data->setInWorldSpace(body->rigidBody->getTransform(), body->rigidBody->getTransform(), Vec3TohkVec4(povit));

	return CreateConstraint(body, otherBody, data, breakable, breakable, maximumAngularImpulse, maximumLinearImpulse);

	TRY_END_NORET
}
sPhysicsConstraints* CreateFixedConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse)
{
	TRY_BEGIN
		
	CreateConstraintCheck(body, otherBody);

	// Create the constraint
	auto data = new hkpFixedConstraintData();
	data->setInBodySpace(body->rigidBody->getTransform(), body->rigidBody->getTransform());

	return CreateConstraint(body, otherBody, data, breakable, breakable, maximumAngularImpulse, maximumLinearImpulse);

	TRY_END_NORET
}
sPhysicsConstraints* CreateStiffSpringConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 povitAW, spVec3 povitBW, float springMin, float springMax, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse)
{
	TRY_BEGIN
		
	CreateConstraintCheck(body, otherBody);

	// Create the constraint
	auto data = new hkpStiffSpringConstraintData();
	data->setInWorldSpace(body->rigidBody->getTransform(), body->rigidBody->getTransform(), Vec3TohkVec4(povitAW), Vec3TohkVec4(povitBW));
	data->setSpringLength(springMin, springMax);

	return CreateConstraint(body, otherBody, data, breakable, breakable, maximumAngularImpulse, maximumLinearImpulse);

	TRY_END_NORET
}
sPhysicsConstraints* CreateHingeConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 povit, spVec3 axis, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse)
{
	TRY_BEGIN
		
	CreateConstraintCheck(body, otherBody);

	// Create the constraint
	auto data = new hkpHingeConstraintData();
	data->setInWorldSpace(body->rigidBody->getTransform(), body->rigidBody->getTransform(), Vec3TohkVec4(povit), Vec3TohkVec4(axis));

	return CreateConstraint(body, otherBody, data, breakable, breakable, maximumAngularImpulse, maximumLinearImpulse);

	TRY_END_NORET
}
sPhysicsConstraints* CreateLimitedHingeConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 povit, spVec3 axis, float agularLimitMin, float agularLimitMax, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse)
{
	TRY_BEGIN

	CreateConstraintCheck(body, otherBody);

	// Create the constraint
	auto data = new hkpLimitedHingeConstraintData();
	data->setInWorldSpace(body->rigidBody->getTransform(), body->rigidBody->getTransform(), Vec3TohkVec4(povit), Vec3TohkVec4(axis));
	data->setMinAngularLimit(agularLimitMin);
	data->setMaxAngularLimit(agularLimitMax);

	return CreateConstraint(body, otherBody, data, breakable, breakable, maximumAngularImpulse, maximumLinearImpulse);

	TRY_END_NORET
}
sPhysicsConstraints* CreateWheelConstraint(sPhysicsRigidbody* wheelRigidBody, sPhysicsRigidbody* chassis, spVec3 axle, spVec3 suspension, spVec3 steering, float suspensionLimitMin, float suspensionLimitMax, float suspensionStrength, float suspensionDamping, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse)
{
	TRY_BEGIN

	CreateConstraintCheck(wheelRigidBody, chassis);

	auto rs = new sPhysicsConstraints();

	// Create the constraint
	auto data = new hkpWheelConstraintData();
	data->setInWorldSpace(wheelRigidBody->rigidBody->getTransform(), chassis->rigidBody->getTransform(), wheelRigidBody->rigidBody->getPosition(), Vec3TohkVec4(axle), Vec3TohkVec4(suspension), Vec3TohkVec4(steering));
	data->setSuspensionMaxLimit(suspensionLimitMin);
	data->setSuspensionMinLimit(suspensionLimitMax);
	data->setSuspensionStrength(suspensionStrength);
	data->setSuspensionDamping(suspensionDamping);

	return CreateConstraint(wheelRigidBody, chassis, data, breakable, breakable, maximumAngularImpulse, maximumLinearImpulse);

	TRY_END_NORET
}
sPhysicsConstraints* CreatePulleyConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 bodyPivot0, spVec3 bodyPivots1, spVec3 worldPivots0, spVec3 worldPivots1, float leverageRatio, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse)
{
	TRY_BEGIN

	CreateConstraintCheck(body, otherBody);

	// Create the constraint
	auto data = new hkpPulleyConstraintData();
	data->setInWorldSpace(body->rigidBody->getTransform(), body->rigidBody->getTransform(), Vec3TohkVec4(bodyPivot0), Vec3TohkVec4(bodyPivots1), Vec3TohkVec4(worldPivots0), Vec3TohkVec4(worldPivots1), leverageRatio);

	return CreateConstraint(body, otherBody, data, breakable, breakable, maximumAngularImpulse, maximumLinearImpulse);

	TRY_END_NORET
}
sPhysicsConstraints* CreatePrismaticConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 povit, spVec3 axis, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse)
{
	TRY_BEGIN

	CreateConstraintCheck(body, otherBody);

	// Create the constraint
	auto data = new hkpPrismaticConstraintData();
	data->setInWorldSpace(body->rigidBody->getTransform(), body->rigidBody->getTransform(), Vec3TohkVec4(povit), Vec3TohkVec4(axis));

	return CreateConstraint(body, otherBody, data, breakable, breakable, maximumAngularImpulse, maximumLinearImpulse);

	TRY_END_NORET
}
sPhysicsConstraints* CreateCogWheelConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 rotationPivotA, spVec3 rotationAxisA, float radiusA, spVec3 rotationPivotB, spVec3 rotationAxisB, float radiusB, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse)
{
	TRY_BEGIN

	CreateConstraintCheck(body, otherBody);

	// Create the constraint
	auto data = new hkpCogWheelConstraintData();
	data->setInWorldSpace(body->rigidBody->getTransform(), body->rigidBody->getTransform(), Vec3TohkVec4(rotationPivotA), Vec3TohkVec4(rotationAxisA), radiusA, Vec3TohkVec4(rotationPivotB), Vec3TohkVec4(rotationAxisB), radiusB);

	return CreateConstraint(body, otherBody, data, breakable, breakable, maximumAngularImpulse, maximumLinearImpulse);

	TRY_END_NORET
}