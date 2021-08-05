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

MyCollisionResolution::MyCollisionResolution(sPhysicsWorld* world)
{
    this->world = world;
}
void MyCollisionResolution::contactPointCallback(const hkpContactPointEvent& event)
{
	HK_ASSERT2(0xf455ea07, event.m_source != hkpCollisionEvent::SOURCE_WORLD, "Do not add this listener to the world.");
    
    if (event.m_lastCallbackForFullManifold && event.m_source == hkpCollisionEvent::SOURCE_A)
    {
        auto source = event.getBody(0);
        auto other = event.getBody(1);
        auto body = (sPhysicsRigidbody*)source->getUserData();
        auto bodyOther = (sPhysicsRigidbody*)other->getUserData();
        if (world && world->physicsWorld && body && bodyOther) {
            auto& pos = event.m_contactPoint->getPosition();
            auto& normal = event.m_contactPoint->getNormal();
            auto& snormal = event.m_contactPoint->getSeparatingNormal();

            sPhysicsBodyContactData data;
            data.distance = event.m_contactPoint->getDistance();
            data.separatingVelocity = event.getSeparatingVelocity();
            data.pos[0] = pos.getComponent<0>();
            data.pos[1] = pos.getComponent<1>();
            data.pos[2] = pos.getComponent<2>();
            data.normal[0] = normal.getComponent<0>();
            data.normal[1] = normal.getComponent<1>();
            data.normal[2] = normal.getComponent<2>();
            data.separatingNormal[0] = snormal.getComponent<0>();
            data.separatingNormal[1] = snormal.getComponent<1>();
            data.separatingNormal[2] = snormal.getComponent<2>();

            world->callbacks.onBodyContactEventCallback(body, bodyOther, body->id, bodyOther->id, &data);
        }
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
        if (world->callbacks.onBodyTriggerEeventCallback) {
            auto sotherBody = (sPhysicsRigidbody*)otherBody->getUserData();
            world->callbacks.onBodyTriggerEeventCallback(body, sotherBody, body->id, sotherBody->id, 1);
        }
    }
    if (type & LEFT_EVENT)
    {
        if (world->callbacks.onBodyTriggerEeventCallback) {
            auto sotherBody = (sPhysicsRigidbody*)otherBody->getUserData();
            world->callbacks.onBodyTriggerEeventCallback(body, sotherBody, body->id, sotherBody->id, 0);
        }
    }
}
