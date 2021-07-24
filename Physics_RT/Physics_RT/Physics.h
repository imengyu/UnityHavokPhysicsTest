#ifndef _HAVOK_C_HKPHYSICS_H_
#define _HAVOK_C_HKPHYSICS_H_ 1

#include "Commom.h"
#include "MathHeader.h"

#ifdef __cplusplus
extern "C"
{
#endif

	HAVOK_C_API hkpWorldRef HAVOK_C_CALL hkpWorld_new(int8_t simulationType, float broadPhaseWorldSize, hkVector4Ref gravity, float collisionTolerance, int solverIterations);
	HAVOK_C_API void HAVOK_C_CALL hkpWorld_markForWrite(hkpWorldRef physicsWorld);
	HAVOK_C_API void HAVOK_C_CALL hkpWorld_unmarkForWrite(hkpWorldRef physicsWorld);

	HAVOK_C_API hkpCollisionDispatcherRef HAVOK_C_CALL hkpWorld_getCollisionDispatcher(hkpWorldRef physicsWorld);
	HAVOK_C_API void HAVOK_C_CALL hkpWorld_registerWithJobQueue(hkJobQueueRef jobQueue);

	HAVOK_C_API hkpEntityRef HAVOK_C_CALL hkpWorld_addEntity(hkpWorldRef physicsWorld, hkpEntityRef entity, int8_t initialActivationState);
	HAVOK_C_API bool HAVOK_C_CALL hkpWorld_removeEntity(hkpWorldRef physicsWorld, hkpEntityRef entity);

	HAVOK_C_API int8_t HAVOK_C_CALL hkpWorld_initMtStep(hkpWorldRef physicsWorld, hkJobQueueRef jobQueue, float physicsDeltaTime);
	HAVOK_C_API int8_t HAVOK_C_CALL hkpWorld_finishMtStep(hkpWorldRef physicsWorld);
	HAVOK_C_API void HAVOK_C_CALL hkpWorld_removeReference(hkpWorldRef physicsWorld);
	HAVOK_C_API void HAVOK_C_CALL hkpAgentRegisterUtil_registerAllAgents(hkpCollisionDispatcherRef dis);

	HAVOK_C_API hkpConvexShapeRef HAVOK_C_CALL hkpBoxShape_new(hkVector4Ref halfExtents, float radius);
	HAVOK_C_API hkpConvexShapeRef HAVOK_C_CALL hkpSphereShape_new(float radius);
	HAVOK_C_API hkpConvexShapeRef HAVOK_C_CALL hkpTriangleShape_new(hkVector4Ref v0, hkVector4Ref v1, hkVector4Ref v2, float radius);
	HAVOK_C_API hkpConvexShapeRef HAVOK_C_CALL hkpCapsuleShape_new(float height, float radius);
	HAVOK_C_API hkpConvexShapeRef HAVOK_C_CALL hkpConvexVerticesShape_new(hkVector4Ref* vertices, int verticesCount);
	HAVOK_C_API hkpConvexShapeRef HAVOK_C_CALL hkpCylinderShape_new(float height, float radius, float convexRadius);
	HAVOK_C_API hkpShapeRef HAVOK_C_CALL hkpSimpleMeshShape_new(float radius);

	HAVOK_C_API void HAVOK_C_CALL hkpShape_removeReference(hkpShapeRef shape);

	HAVOK_C_API void HAVOK_C_CALL hkpEntity_removeReference(hkpEntityRef entity);
	HAVOK_C_API void HAVOK_C_CALL hkpEntity_addReference(hkpEntityRef entity);
	HAVOK_C_API void HAVOK_C_CALL hkpEntity_activate(hkpEntityRef entity);
	HAVOK_C_API void HAVOK_C_CALL hkpEntity_deactivate(hkpEntityRef entity);

	HAVOK_C_API hkpEntityRef HAVOK_C_CALL hkpRigidBody_new(hkpShapeRef shape, hkVector4Ref position, float mass, int8_t motionType, int8_t qualityType, float linearDamping, float angularDamping, hkVector4Ref linearVelocity, hkVector4Ref angularVelocity, float gravityFactor);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_getPosition(hkpEntityRef entity, hkVector4Ref positionOut);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_getRotation(hkpEntityRef entity, hkQuaternionRef quaternionOut);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setPosition(hkpEntityRef entity, hkVector4Ref position);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setRotation(hkpEntityRef entity, hkQuaternionRef quaternion);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setMotionType(hkpEntityRef entity, int8_t motionType);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setMass(hkpEntityRef entity, float mass);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setFriction(hkpEntityRef entity, float friction);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setRestitution(hkpEntityRef entity, float restitution);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setAngularDamping(hkpEntityRef entity, float d);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setLinearDamping(hkpEntityRef entity, float d);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setLinearVelocity(hkpEntityRef entity, hkVector4Ref newVel);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setAngularVelocity(hkpEntityRef entity, hkVector4Ref newVel);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setGravityFactor(hkpEntityRef entity, float f);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setCenterOfMassLocal(hkpEntityRef entity, hkVector4Ref centerOfMass);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setInertiaLocal(hkpEntityRef entity, hkMatrix3Ref inertiaInv);
	HAVOK_C_API void HAVOK_C_CALL hkpRigidBody_setShape(hkpEntityRef entity, hkpShapeRef shape);

	HAVOK_C_API void HAVOK_C_CALL hkpEntity_removeReference(hkpEntityRef entity);

	HAVOK_C_API void HAVOK_C_CALL hkpPhysicsContext_registerAllPhysicsProcesses();
	HAVOK_C_API hkProcessContextRef HAVOK_C_CALL hkpPhysicsContext_new();
	HAVOK_C_API void HAVOK_C_CALL hkpPhysicsContext_addWorld(hkProcessContextRef context, hkpWorldRef physicsWorld);
	HAVOK_C_API void HAVOK_C_CALL hkpPhysicsContext_removeReference(hkProcessContextRef context);
#ifdef __cplusplus
}
#endif

#endif