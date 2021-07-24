#include "Physics.h"

// Collide
#include <Physics2012/Collide/hkpCollide.h>
#include <Physics2012/Collide/Agent/ConvexAgent/SphereBox/hkpSphereBoxAgent.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics2012/Collide/Shape/Convex/Triangle/hkpTriangleShape.h>
#include <Physics2012/Collide/Shape/Convex/Capsule/hkpCapsuleShape.h>
#include <Physics2012/Collide/Shape/Convex/Cylinder/hkpCylinderShape.h>
#include <Physics2012/Collide/Shape/Compound/Collection/SimpleMesh/hkpSimpleMeshShape.h>
#include <Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.h>
#include <Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics2012/Collide/Shape/Misc/Transform/hkpTransformShape.h>
#include <Physics2012/Collide/Shape/HeightField/Plane/hkpPlaneShape.h>
#include <Physics2012/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Common/Base/Types/Geometry/hkStridedVertices.h>
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>
#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>

// Dynamics
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

// MultiThreaded
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

// Visual Debugger
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>

#include <assert.h>

//=======================================
// Wrap fuctions
//=======================================

WARP_FUNC(hkpWorld, hkpWorldRef)
WARP_FUNC(hkpCollisionDispatcher, hkpCollisionDispatcherRef)
WARP_FUNC(hkpShape, hkpShapeRef)
WARP_FUNC(hkpEntity, hkpEntityRef)
WARP_FUNC(hkJobQueue, hkJobQueueRef)
WARP_FUNC(hkProcessContext, hkProcessContextRef)
WARP_FUNC(hkVector4, hkVector4Ref)
WARP_FUNC(hkQuaternion, hkQuaternionRef)
WARP_FUNC(hkMatrix3, hkMatrix3Ref)
WARP_FUNC(hkRotation, hkRotationRef)
WARP_FUNC(hkpConvexShape, hkpConvexShapeRef)


//=======================================
// API
//=======================================

hkpWorldRef HAVOK_C_CALL hkpWorld_new(int8_t simulationType, float broadPhaseWorldSize, hkVector4Ref gravity, float collisionTolerance, int solverIterations)
{
	// The world cinfo contains global simulation parameters, including gravity, solver settings etc.
	hkpWorldCinfo worldInfo;
	worldInfo.m_simulationType = static_cast<hkpWorldCinfo::SimulationType>(simulationType);
	worldInfo.m_gravity.setXYZ(*unwrap(gravity));
	worldInfo.setBroadPhaseWorldSize(broadPhaseWorldSize);
	worldInfo.setupSolverInfo( hkpWorldCinfo::SOLVER_TYPE_4ITERS_MEDIUM );
	worldInfo.m_collisionTolerance = collisionTolerance;
	worldInfo.m_solverIterations = solverIterations;

	hkpWorld *physicsWorld = new hkpWorld(worldInfo);
	return wrap(physicsWorld);
}
void HAVOK_C_CALL hkpWorld_markForWrite(hkpWorldRef physicsWorld)
{
	return unwrap(physicsWorld)->markForWrite();
}
void HAVOK_C_CALL hkpWorld_unmarkForWrite(hkpWorldRef physicsWorld)
{
	return unwrap(physicsWorld)->unmarkForWrite();
}

hkpCollisionDispatcherRef HAVOK_C_CALL hkpWorld_getCollisionDispatcher(hkpWorldRef physicsWorld)
{
	return wrap(unwrap(physicsWorld)->getCollisionDispatcher());
}
void HAVOK_C_CALL hkpWorld_registerWithJobQueue(hkJobQueueRef jobQueue)
{
	return hkpWorld::registerWithJobQueue(unwrap(jobQueue));
}

hkpEntityRef HAVOK_C_CALL hkpWorld_addEntity(hkpWorldRef physicsWorld, hkpEntityRef entity, int8_t initialActivationState)
{
	return wrap(unwrap(physicsWorld)->addEntity(unwrap(entity), static_cast<hkpEntityActivation>(initialActivationState)));
}
bool HAVOK_C_CALL hkpWorld_removeEntity(hkpWorldRef physicsWorld, hkpEntityRef entity)
{
	return unwrap(physicsWorld)->removeEntity(unwrap(entity));
}
int8_t HAVOK_C_CALL hkpWorld_initMtStep(hkpWorldRef physicsWorld, hkJobQueueRef jobQueue, float physicsDeltaTime)
{
	//World\Simulation\Multithreaded\hkpMultithreadedSimulation.cpp(754): [0x67F55434] Assert: If you are managing the processing of jobs yourself (i.e. no threadPool specified) you should set the queue to not release threads
	hkpStepResult _res = unwrap(physicsWorld)->initMtStep(unwrap(jobQueue), physicsDeltaTime);
	return _res;
}
int8_t HAVOK_C_CALL hkpWorld_finishMtStep(hkpWorldRef physicsWorld)
{
	hkpStepResult _res = unwrap(physicsWorld)->finishMtStep(HK_NULL, HK_NULL);
	return _res;
}
void HAVOK_C_CALL hkpWorld_removeReference(hkpWorldRef physicsWorld)
{
	return unwrap(physicsWorld)->removeReference();
}

void HAVOK_C_CALL hkpAgentRegisterUtil_registerAllAgents(hkpCollisionDispatcherRef dis)
{
	return hkpAgentRegisterUtil::registerAllAgents(unwrap(dis));
}

hkpConvexShapeRef HAVOK_C_CALL hkpBoxShape_new(hkVector4Ref halfExtents, float radius)
{
	hkpConvexShape*shape = new hkpBoxShape(*unwrap(halfExtents), radius);
	return wrap(shape);
}
hkpConvexShapeRef HAVOK_C_CALL hkpSphereShape_new(float radius)
{
	hkpConvexShape*shape = new hkpSphereShape(radius);
	return wrap(shape);
}
hkpConvexShapeRef HAVOK_C_CALL hkpTriangleShape_new(hkVector4Ref v0, hkVector4Ref v1, hkVector4Ref v2, float radius)
{
	hkpConvexShape* shape = new hkpTriangleShape(*unwrap(v0), *unwrap(v1), *unwrap(v2), radius);
	return wrap(shape);
}
hkpConvexShapeRef HAVOK_C_CALL hkpCapsuleShape_new(float height, float radius)
{
	hkVector4 start(0, -height / 2, 0);
	hkVector4 end(0, height / 2, 0);
	hkpConvexShape* shape = new hkpCapsuleShape(start, end, radius);
	return wrap(shape);
}
hkpConvexShapeRef HAVOK_C_CALL hkpConvexVerticesShape_new(hkVector4Ref* vertices, int verticesCount)
{
	hkArray<hkVector4> verticesArr;
	for (int i = 0; i < verticesCount; i++)
		verticesArr.pushBack(*unwrap(vertices[i])); 

	hkpConvexShape* shape = new hkpConvexVerticesShape(hkStridedVertices(verticesArr));
	return wrap(shape);
}
hkpConvexShapeRef HAVOK_C_CALL hkpCylinderShape_new(float height, float radius, float convexRadius)
{
	hkVector4 start(0, -height / 2, 0);
	hkVector4 end(0, height / 2, 0);
	hkpConvexShape* shape = new hkpCylinderShape(start, end, radius, convexRadius);
	return wrap(shape);
}
hkpShapeRef HAVOK_C_CALL hkpSimpleMeshShape_new(float radius) {
	hkpShape* shape = new hkpSimpleMeshShape(radius);
	return wrap(shape);
}
hkpShapeRef HAVOK_C_CALL hkpPlaneShape_new(hkVector4Ref center, hkVector4Ref halfExtents) {
	hkVector4 direction(0, 0, 0);
	hkpShape* shape = new hkpPlaneShape(direction, *unwrap(center), *unwrap(halfExtents));
	return wrap(shape);
}

hkpShapeRef HAVOK_C_CALL hkpConvexTranslateShape_new(hkpConvexShapeRef childShape, hkVector4Ref translation) {
	hkVector4 _translation;
	_translation.setXYZ(*unwrap(translation));
	hkpShape* shape = new hkpConvexTranslateShape(unwrap(childShape), _translation);
	return wrap(shape);
}
hkpShapeRef HAVOK_C_CALL hkpConvexTransformShape_new(hkpConvexShapeRef childShape, hkVector4Ref translation, hkVector4Ref rotation, hkVector4Ref scale) {
	hkQuaternion _rotation; 
	_rotation.setFromEulerAngles(unwrap(rotation)->getComponent(0), unwrap(rotation)->getComponent(1), unwrap(rotation)->getComponent(2));
	hkQsTransform transform(*unwrap(translation), _rotation, *unwrap(scale));
	hkpShape* shape = new hkpConvexTransformShape(unwrap(childShape), transform);
	return wrap(shape);
}
hkpShapeRef HAVOK_C_CALL hkpTransformShape_new(hkpShapeRef childShape, hkVector4Ref translation, hkVector4Ref rotation) {
	hkQuaternion _rotation;
	_rotation.setFromEulerAngles(unwrap(rotation)->getComponent(0), unwrap(rotation)->getComponent(1), unwrap(rotation)->getComponent(2));
	hkTransform transform(_rotation, *unwrap(translation));
	hkpShape* shape = new hkpTransformShape(unwrap(childShape), transform);
	return wrap(shape);
}

void HAVOK_C_CALL hkpShape_delete(hkpShapeRef shape)
{
	delete shape;
}
void HAVOK_C_CALL hkpShape_removeReference(hkpShapeRef shape)
{
	return unwrap(shape)->removeReference();
}

hkpEntityRef HAVOK_C_CALL hkpRigidBody_new(hkpShapeRef shape, hkVector4Ref position, float mass, int8_t motionType, int8_t qualityType, float linearDamping, float angularDamping, hkVector4Ref linearVelocity, hkVector4Ref angularVelocity, float gravityFactor)
{
	hkpRigidBodyCinfo info;
	info.m_shape = unwrap(shape);
	info.m_position = *unwrap(position);
	info.m_mass = mass;
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(unwrap(shape), mass, info);
	info.m_motionType = static_cast<hkpMotion::MotionType>(motionType);
	info.m_qualityType = static_cast<hkpCollidableQualityType>(qualityType);
	info.m_linearDamping = linearDamping;
	info.m_angularDamping = angularDamping;
	info.m_gravityFactor = gravityFactor;
	info.m_linearVelocity = *unwrap(linearVelocity);
	info.m_angularVelocity = *unwrap(angularVelocity);

	hkpEntity *pShape = new hkpRigidBody(info);
	return wrap(pShape);
}

void HAVOK_C_CALL hkpRigidBody_getPosition(hkpEntityRef entity, hkVector4Ref positionOut)
{
	assert(dynamic_cast<hkpRigidBody *>(unwrap(entity)) != NULL);
	hkVector4 const &position = static_cast<hkpRigidBody *>(unwrap(entity))->getPosition();
	unwrap(positionOut)->setXYZ(position);
}
void HAVOK_C_CALL hkpRigidBody_getRotation(hkpEntityRef entity, hkQuaternionRef quaternionOut)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	hkQuaternion const& quaternion = static_cast<hkpRigidBody*>(unwrap(entity))->getRotation();
	*unwrap(quaternionOut) = quaternion;
}
void HAVOK_C_CALL hkpRigidBody_setPosition(hkpEntityRef entity, hkVector4Ref position)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setPosition(*unwrap(position));
}
void HAVOK_C_CALL hkpRigidBody_setRotation(hkpEntityRef entity, hkQuaternionRef quaternion)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setRotation(*unwrap(quaternion));
}
void HAVOK_C_CALL hkpRigidBody_setMotionType(hkpEntityRef entity, int8_t motionType)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setMotionType(static_cast<hkpMotion::MotionType>(motionType));
}
void HAVOK_C_CALL hkpRigidBody_setMass(hkpEntityRef entity, float mass)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setMass(mass);
}
void HAVOK_C_CALL hkpRigidBody_setFriction(hkpEntityRef entity, float friction)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setFriction(friction);
}
void HAVOK_C_CALL hkpRigidBody_setRestitution(hkpEntityRef entity, float restitution)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setRestitution(restitution);
}
void HAVOK_C_CALL hkpRigidBody_setAngularDamping(hkpEntityRef entity, float d)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setAngularDamping(d);
}
void HAVOK_C_CALL hkpRigidBody_setLinearDamping(hkpEntityRef entity, float d)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setLinearDamping(d);
}
void HAVOK_C_CALL hkpRigidBody_setLinearVelocity(hkpEntityRef entity, hkVector4Ref newVel)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setLinearVelocity(*unwrap(newVel));
}
void HAVOK_C_CALL hkpRigidBody_setAngularVelocity(hkpEntityRef entity, hkVector4Ref newVel)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setAngularVelocity(*unwrap(newVel));
}
void HAVOK_C_CALL hkpRigidBody_setGravityFactor(hkpEntityRef entity, float f)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setGravityFactor(f);
}
void HAVOK_C_CALL hkpRigidBody_setCenterOfMassLocal(hkpEntityRef entity, hkVector4Ref centerOfMass)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setCenterOfMassLocal(*unwrap(centerOfMass));
}
void HAVOK_C_CALL hkpRigidBody_setInertiaLocal(hkpEntityRef entity, hkMatrix3Ref inertiaInv)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setInertiaLocal(*unwrap(inertiaInv));
}
void HAVOK_C_CALL hkpRigidBody_setShape(hkpEntityRef entity, hkpShapeRef shape)
{
	assert(dynamic_cast<hkpRigidBody*>(unwrap(entity)) != NULL);
	static_cast<hkpRigidBody*>(unwrap(entity))->setShape(unwrap(shape));
}

void HAVOK_C_CALL hkpEntity_removeReference(hkpEntityRef entity)
{
	return unwrap(entity)->removeReference();
}
void HAVOK_C_CALL hkpEntity_addReference(hkpEntityRef entity)
{
	return unwrap(entity)->addReference();
}
void HAVOK_C_CALL hkpEntity_activate(hkpEntityRef entity)
{
	return unwrap(entity)->activate();
}
void HAVOK_C_CALL hkpEntity_deactivate(hkpEntityRef entity)
{
	return unwrap(entity)->deactivate();
}

void HAVOK_C_CALL hkpPhysicsContext_registerAllPhysicsProcesses()
{
	return hkpPhysicsContext::registerAllPhysicsProcesses();
}
hkProcessContextRef HAVOK_C_CALL hkpPhysicsContext_new()
{
	hkProcessContext *context = new hkpPhysicsContext();
	return wrap(context);
}
void HAVOK_C_CALL hkpPhysicsContext_addWorld(hkProcessContextRef context, hkpWorldRef physicsWorld)
{
	assert(dynamic_cast<hkpPhysicsContext *>(unwrap(context)) != NULL);
	return static_cast<hkpPhysicsContext *>(unwrap(context))->addWorld(unwrap(physicsWorld));
}
void HAVOK_C_CALL hkpPhysicsContext_removeReference(hkProcessContextRef context)
{
	assert(dynamic_cast<hkpPhysicsContext *>(unwrap(context)) != NULL);
	return static_cast<hkpPhysicsContext *>(unwrap(context))->removeReference();
}