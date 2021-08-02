#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"
#include "SimpleLinkedList.hpp"

struct sPhysicsWorld {
	hkpWorld* physicsWorld;
	hkVisualDebugger* vdb;
	hkpPhysicsContext* context;
	hkpGroupFilter* filter;

	SimpleLinkedList<sPhysicsRigdbody> bodyList;
	sPhysicsRigdbody* bodyCurrent;
	int bodyCurrentIndex;
};

sPhysicsWorld* CreatePhysicsWorld(spVec3 gravity, int solverIterationCount, float broadPhaseWorldSize, float collisionTolerance,
	bool bContinuous, bool bVisualDebugger, unsigned int layerMask, unsigned int* layerToMask);
void DestroyPhysicsWorld(sPhysicsWorld* world);
void StepPhysicsWorld(sPhysicsWorld* world, float timestep);
void SetPhysicsWorldGravity(sPhysicsWorld* world, spVec3 gravity);
void SetPhysicsWorldCollisionLayerMasks(sPhysicsWorld* world, unsigned int layerId, unsigned int toMask, int enable, int forceUpdate);
int ReadPhysicsWorldBodys(sPhysicsWorld* world, float* buffer, int count);

void TestAssert();
