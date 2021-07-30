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

typedef sPhysicsWorld* (__cdecl* fnCreatePhysicsWorld)(spVec3 gravity, int solverIterationCount, float broadPhaseWorldSize, float collisionTolerance);
typedef void(__cdecl* fnDestroyPhysicsWorld)(sPhysicsWorld* world);
typedef void(__cdecl* fnStepPhysicsWorld)(sPhysicsWorld* world, float timestep);
typedef void(__cdecl* fnSetPhysicsWorldGravity)(sPhysicsWorld* world, spVec3 gravity);
typedef int(__cdecl* fnReadPhysicsWorldBodys)(sPhysicsWorld* world, float* buffer, int count);


sPhysicsWorld* CreatePhysicsWorld(spVec3 gravity, int solverIterationCount, float broadPhaseWorldSize);
void DestroyPhysicsWorld(sPhysicsWorld* world);
void StepPhysicsWorld(sPhysicsWorld* world, float timestep);
void SetPhysicsWorldGravity(sPhysicsWorld* world, spVec3 gravity);
int ReadPhysicsWorldBodys(sPhysicsWorld* world, float* buffer, int count);
