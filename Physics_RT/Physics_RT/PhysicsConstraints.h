#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"

struct sPhysicsConstraints {
	hkpConstraintInstance* instance;
	hkpBreakableConstraintData* breaker;
	sPhysicsWorld* world;
	bool breakable;
};

void SetupWorldConstraintListener(sPhysicsWorld* world);
void DestroyWorldConstraintListener(sPhysicsWorld* world);

void DestoryConstraints(sPhysicsConstraints* constraint);
int IsConstraintBroken(sPhysicsConstraints* constraint);
void SetConstraintBroken(sPhysicsConstraints* constraint, bool broken, float force);
sPhysicsConstraints* CreateBallAndSocketConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 povit, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse);
sPhysicsConstraints* CreateFixedConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse);
sPhysicsConstraints* CreateStiffSpringConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 povitAW, spVec3 povitBW, float springMin, float springMax, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse);
sPhysicsConstraints* CreateHingeConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 povit, spVec3 axis, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse);
sPhysicsConstraints* CreateLimitedHingeConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 povit, spVec3 axis, float agularLimitMin, float agularLimitMax, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse);
sPhysicsConstraints* CreateWheelConstraint(sPhysicsRigidbody* wheelRigidBody, sPhysicsRigidbody* chassis, spVec3 axle, spVec3 suspension, spVec3 steering, float suspensionLimitMin, float suspensionLimitMax, float suspensionStrength, float suspensionDamping, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse);
sPhysicsConstraints* CreatePulleyConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 bodyPivot0, spVec3 bodyPivots1, spVec3 worldPivots0, spVec3 worldPivots1, float leverageRatio, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse);
sPhysicsConstraints* CreatePrismaticConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 povit, spVec3 axis, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse);
sPhysicsConstraints* CreateCogWheelConstraint(sPhysicsRigidbody* body, sPhysicsRigidbody* otherBody, spVec3 rotationPivotA, spVec3 rotationAxisA, float radiusA, spVec3 rotationPivotB, spVec3 rotationAxisB, float radiusB, int breakable, float threshold, float maximumAngularImpulse, float maximumLinearImpulse);