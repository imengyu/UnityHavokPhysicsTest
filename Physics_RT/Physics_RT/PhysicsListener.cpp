#include "stdafx.h"
#include "PhysicsHeader.h"
#include "PhysicsFunctions.h"

MyBreakableListener::MyBreakableListener(sPhysicsWorld* world)
{
	this->world = world;
}
void MyBreakableListener::constraintBreakingCallback(hkpBreakableConstraintEvent& event)
{
    if (world->callbacks.onConstraintBreakingCallback) {
        auto s = (sPhysicsConstraints*)event.m_constraintInstance->getUserData();
        world->callbacks.onConstraintBreakingCallback(s, s->id, event.m_forceMagnitude, event.m_removed);
    }
}

MyTriggerVolume::MyTriggerVolume(sPhysicsRigidbody* body) : hkpTriggerVolume(body->rigidBody)
{
    this->body = body;    
    world = body->world;
}
void MyTriggerVolume::triggerEventCallback(hkpRigidBody* otherBody, EventType type)
{
    if (type & ENTERED_EVENT)
    {
        if (world->callbacks.onBodyTriggerEnterCallback) {
            auto sotherBody = (sPhysicsRigidbody*)otherBody->getUserData();
            world->callbacks.onBodyTriggerEnterCallback(body, sotherBody, body->id, sotherBody->id);
        }
    }
    if (type & LEFT_EVENT)
    {
        if (world->callbacks.onBodyTriggerLeaveCallback) {
            auto sotherBody = (sPhysicsRigidbody*)otherBody->getUserData();
            world->callbacks.onBodyTriggerLeaveCallback(body, sotherBody, body->id, sotherBody->id);
        }
    }
}
