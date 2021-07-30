#include "PhysicsHeader.h"
#include "PhysicsFunctions.h"

extern hkJobQueue* jobQueue;
extern hkJobThreadPool* threadPool;
extern sInitStruct initStruct;

sPhysicsWorld* CreatePhysicsWorld(spVec3 gravity, int solverIterationCount, float broadPhaseWorldSize, float collisionTolerance)
{
	hkpWorld* physicsWorld = nullptr;
	{
		// The world cinfo contains global simulation parameters, including gravity, solver settings etc.
		hkpWorldCinfo worldInfo;

		worldInfo.m_gravity = hkVector4(gravity->x, gravity->y, gravity->z);
		worldInfo.m_solverIterations = solverIterationCount;
		worldInfo.m_collisionTolerance = collisionTolerance;
		worldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_FIX_ENTITY;
		worldInfo.setBroadPhaseWorldSize(broadPhaseWorldSize);

		if (initStruct.mulithread) {

			// Set the simulation type of the world to multi-threaded.
			worldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_MULTITHREADED;
			physicsWorld = new hkpWorld(worldInfo);

			// Disable deactivation, so that you can view timers in the VDB. This should not be done in your game.
			physicsWorld->m_wantDeactivation = false;


			// When the simulation type is SIMULATION_TYPE_MULTITHREADED, in the debug build, the sdk performs checks
			// to make sure only one thread is modifying the world at once to prevent multithreaded bugs. Each thread
			// must call markForRead / markForWrite before it modifies the world to enable these checks.
			physicsWorld->markForWrite();


			// Register all collision agents, even though only box - box will be used in this particular example.
			// It's important to register collision agents before adding any entities to the world.
			hkpAgentRegisterUtil::registerAllAgents(physicsWorld->getCollisionDispatcher());

			// We need to register all modules we will be running multi-threaded with the job queue
			physicsWorld->registerWithJobQueue(jobQueue);
		}
		else {
			physicsWorld = new hkpWorld(worldInfo);

			// Register all collision agents, even though only box - box will be used in this particular example.
			// It's important to register collision agents before adding any entities to the world.
			{
				hkpAgentRegisterUtil::registerAllAgents(physicsWorld->getCollisionDispatcher());
			}
		}
	}


	//
	// Initialize the VDB
	//
	hkArray<hkProcessContext*> contexts;


	// <PHYSICS-ONLY>: Register physics specific visual debugger processes
	// By default the VDB will show debug points and lines, however some products such as physics and cloth have additional viewers
	// that can show geometries etc and can be enabled and disabled by the VDB app.
	hkpPhysicsContext* context;
	{
		// The visual debugger so we can connect remotely to the simulation
		// The context must exist beyond the use of the VDB instance, and you can make
		// whatever contexts you like for your own viewer types.
		context = new hkpPhysicsContext();
		hkpPhysicsContext::registerAllPhysicsProcesses(); // all the physics viewers
		context->addWorld(physicsWorld); // add the physics world so the viewers can see it
		contexts.pushBack(context);

		// Now we have finished modifying the world, release our write marker.
		physicsWorld->unmarkForWrite();
	}

	hkVisualDebugger* vdb = new hkVisualDebugger(contexts);
	vdb->serve();

	sPhysicsWorld* def = new sPhysicsWorld();
	def->physicsWorld = physicsWorld;
	def->vdb = vdb;
	def->context = context;
	return def;
}
void DestroyPhysicsWorld(sPhysicsWorld* world) {
	if (world) {
		//
		// Clean up physics and graphics
		//

		// <PHYSICS-ONLY>: cleanup physics
		{
			if (initStruct.mulithread)
				world->physicsWorld->markForWrite();
			world->physicsWorld->removeReference();
		}
		world->vdb->removeReference();

		// Contexts are not reference counted at the base class level by the VDB as
		// they are just interfaces really. So only delete the context after you have
		// finished using the VDB.
		world->context->removeReference();
		world->bodyList.clear();
		delete world;
	}
}
void SetPhysicsWorldGravity(sPhysicsWorld* world, spVec3 gravity)
{
	world->physicsWorld->setGravity(hkVector4(gravity->x, gravity->y, gravity->z));
}


void StepPhysicsWorld(sPhysicsWorld* world, float timestep) {
	if (initStruct.mulithread) {

		// <PHYSICS-ONLY>:
		// Step the physics world. This single call steps using this thread and all threads
		// in the threadPool. For other products you add jobs, call process all jobs and wait for completion.
		// See the multithreading chapter in the user guide for details
		{
			world->physicsWorld->stepMultithreaded(jobQueue, threadPool, timestep);
		}

		// Step the visual debugger. We first synchronize the timer data
		world->context->syncTimers(threadPool);
		world->vdb->step();

		// Clear accumulated timer data in this thread and all slave threads
		hkMonitorStream::getInstance().reset();
		threadPool->clearTimerData();
	}
	else {
		world->physicsWorld->stepDeltaTime(timestep);
		// Step the debugger
		world->vdb->step();
		// Reset internal profiling info for next frame
		hkMonitorStream::getInstance().reset();
	}

	world->bodyCurrent = world->bodyList.begin;
	world->bodyCurrentIndex = 0;
}
int ReadPhysicsWorldBodys(sPhysicsWorld* world, float *buffer, int count)
{
	int currentCount = 0, currentPos = 0;
	auto* ptr = world->bodyCurrent;
	while (ptr && currentCount < count) {

		auto &pos = ptr->rigidBody->getPosition();
		auto &rot = ptr->rigidBody->getRotation();

		currentPos = currentCount * 7;
		buffer[currentPos] = pos.getComponent(0);
		buffer[currentPos + 1] = pos.getComponent(1);
		buffer[currentPos + 2] = pos.getComponent(2);

		buffer[currentPos + 3] = rot.getComponent<0>();
		buffer[currentPos + 4] = rot.getComponent<1>();
		buffer[currentPos + 5] = rot.getComponent<2>();
		buffer[currentPos + 6] = rot.getComponent<3>();

		currentCount++;
		ptr = ptr->next;
		world->bodyCurrent = ptr;
		world->bodyCurrentIndex++;
	}
	return world->bodyList.getSize() - world->bodyCurrentIndex;
}


