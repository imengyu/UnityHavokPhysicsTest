#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"
#include "SimpleLinkedList.hpp"

typedef void(__cdecl* fnOnConstraintBreakingCallback)(struct sPhysicsConstraints* constraint, int id, float forceMagnitude, int removed);
typedef void(__cdecl* fnOnBodyTriggerEnterCallback)(struct sPhysicsRigidbody* body, struct sPhysicsRigidbody* bodyOther, int id, int otherId);
typedef void(__cdecl* fnOnBodyTriggerLeaveCallback)(struct sPhysicsRigidbody* body, struct sPhysicsRigidbody* bodyOther, int id, int otherId);

struct sPhysicsWorldCallbacks {
	fnOnConstraintBreakingCallback onConstraintBreakingCallback;
	fnOnBodyTriggerEnterCallback onBodyTriggerEnterCallback;
	fnOnBodyTriggerLeaveCallback onBodyTriggerLeaveCallback;
};

struct sPhysicsWorld {
	hkpWorld* physicsWorld;
	hkVisualDebugger* vdb;
	hkpPhysicsContext* context;
	hkpGroupFilter* filter;
	struct MyBreakableListener* breakableListener;

	sPhysicsWorldCallbacks callbacks;
	SimpleLinkedList<sPhysicsRigidbody> bodyList;
	sPhysicsRigidbody* bodyCurrent;
	int bodyCurrentIndex;
};

struct sRayCastResult {
	float hitFraction;
	float normal[3];
	float pos[3];
	int bodyId;
	sPhysicsRigidbody* body;
};

sPhysicsWorld* CreatePhysicsWorld(spVec3 gravity, int solverIterationCount, float broadPhaseWorldSize, float collisionTolerance,
	bool bContinuous, bool bVisualDebugger, unsigned int layerMask, unsigned int* layerToMask,
	fnOnConstraintBreakingCallback onConstraintBreakingCallback, fnOnBodyTriggerEnterCallback onBodyTriggerEnterCallback, fnOnBodyTriggerLeaveCallback onBodyTriggerLeaveCallback);
void DestroyPhysicsWorld(sPhysicsWorld* world);
void StepPhysicsWorld(sPhysicsWorld* world, float timestep);
void SetPhysicsWorldGravity(sPhysicsWorld* world, spVec3 gravity);
void SetPhysicsWorldCollisionLayerMasks(sPhysicsWorld* world, unsigned int layerId, unsigned int toMask, int enable, int forceUpdate);
int ReadPhysicsWorldBodys(sPhysicsWorld* world, float* buffer, int count);

int PhysicsWorldRayCastBody(sPhysicsWorld* world, spVec3 from, spVec3 to, int rayLayer, sRayCastResult** outResult);
int PhysicsWorldRayCastHit(sPhysicsWorld* world, spVec3 from, spVec3 to, int rayLayer, int castAll, sRayCastResult** outResult);

void TestAssert();
