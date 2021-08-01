#pragma once
#include "PhysicsHeader.h"
#include "PhysicsCommon.h"
#include "SimpleLinkedList.hpp"

struct sPhysicsWorld {
	hkpWorld* physicsWorld;
	hkVisualDebugger* vdb;
	hkpPhysicsContext* context;

	SimpleLinkedList<sPhysicsRigdbody> bodyList;
	sPhysicsRigdbody* bodyCurrent;
	int bodyCurrentIndex;
};

sPhysicsWorld* CreatePhysicsWorld(spVec3 gravity, int solverIterationCount, float broadPhaseWorldSize, float collisionTolerance,
	bool bContinuous, bool bVisualDebugger);
void DestroyPhysicsWorld(sPhysicsWorld* world);
void StepPhysicsWorld(sPhysicsWorld* world, float timestep);
void SetPhysicsWorldGravity(sPhysicsWorld* world, spVec3 gravity);
int ReadPhysicsWorldBodys(sPhysicsWorld* world, float* buffer, int count);

void TestAssert();
