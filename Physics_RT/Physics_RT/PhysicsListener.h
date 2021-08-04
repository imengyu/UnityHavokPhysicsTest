#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"

class MyBreakableListener : public hkpConstraintListener {
public:
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER, MyBreakableListener);
	MyBreakableListener(sPhysicsWorld* world);
	void constraintBreakingCallback(hkpBreakableConstraintEvent& event);
private:
	sPhysicsWorld* world;
};

class MyTriggerVolume : public hkpTriggerVolume {
public:
	MyTriggerVolume(sPhysicsRigidbody* body);
	void triggerEventCallback(hkpRigidBody* body, EventType type);

private:
	sPhysicsRigidbody* body;
	sPhysicsWorld* world;
};