#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"

class MyBreakableListener : public hkpConstraintListener {
public:
	MyBreakableListener(sPhysicsWorld* world);
	void constraintBreakingCallback(hkpBreakableConstraintEvent& event);
private:
	sPhysicsWorld* world
};

class MyTriggerVolume : public hkpTriggerVolume {
public:
	MyTriggerVolume(sPhysicsRigidbody* body);
	void triggerEventCallback(hkpRigidBody* body, EventType type);

private:
	sPhysicsRigidbody* body;
	sPhysicsWorld* world;
};