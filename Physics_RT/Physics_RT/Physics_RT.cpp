// Physics_RT.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Physics_RT.h"
#include "Commom.h"

// Math and Base
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/System/Io/Reader/hkStreamReader.h>
#include <Common/Base/System/Io/Writer/hkStreamWriter.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Container/String/hkStringBuf.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>

// MultiThreaded
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

// Parser
#include <Common/Base/System/Io/OptionParser/hkOptionParser.h>

// Dynamics includes
#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
// Dynamics
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

WARP_FUNC(RT_SystemMulitThreadInitInfo, RT_SystemMulitThreadInitInfoRef)

ErrorReportCallback errorReportCallback = nullptr;

typedef struct {
	hkJobThreadPool* threadPool;
	int totalNumThreadsUsed;
	hkJobQueue* jobQueue;
} RT_SystemMulitThreadInitInfo;

static void HK_CALL errorReport(const char* msg, void* userArgGivenToInit)
{
	if (errorReportCallback != nullptr)
		errorReportCallback(msg);
}

//================================================
// RT_API
//================================================

void HAVOK_C_CALL RT_InitializeBaseSystem(ErrorReportCallback errorReportCallback) {
	::errorReportCallback = errorReportCallback;
	hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault(hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(500000));
	hkBaseSystem::init(memoryRouter, errorReport);
}

RT_SystemMulitThreadInitInfoRef HAVOK_C_CALL RT_InitializeMulitThread()
{
	RT_SystemMulitThreadInitInfo* info = new RT_SystemMulitThreadInitInfo();

	hkHardwareInfo hwInfo;
	hkGetHardwareInfo(hwInfo);
	info->totalNumThreadsUsed = hwInfo.m_numThreads;

	// We use one less than this for our thread pool, because we must also use this thread for our simulation
	hkCpuJobThreadPoolCinfo threadPoolCinfo;
	threadPoolCinfo.m_numThreads = info->totalNumThreadsUsed - 1;

	// This line enables timers collection, by allocating 200 Kb per thread.  If you leave this at its default (0),
	// timer collection will not be enabled.
	threadPoolCinfo.m_timerBufferPerThreadAllocation = 200000;
	info->threadPool = new hkCpuJobThreadPool(threadPoolCinfo);

	hkJobQueueCinfo jqInfo;
	jqInfo.m_jobQueueHwSetup.m_numCpuThreads = info->totalNumThreadsUsed;
	info->jobQueue = new hkJobQueue(jqInfo);

	//
	// Enable monitors for this thread.
	//

	// Monitors have been enabled for thread pool threads already (see above comment).
	hkMonitorStream::getInstance().resize(200000);

	return wrap(info);
}
void* HAVOK_C_CALL RT_GetMulitThreadJobQueue(RT_SystemMulitThreadInitInfoRef info) {
	return unwrap(info)->jobQueue;
}
void* HAVOK_C_CALL RT_GetMulitThreadThreadPool(RT_SystemMulitThreadInitInfoRef info) {
	return unwrap(info)->threadPool;
}
int HAVOK_C_CALL RT_GetMulitThreadTotalNumThreadsUsed(RT_SystemMulitThreadInitInfoRef info) {
	return unwrap(info)->totalNumThreadsUsed;
}
void HAVOK_C_CALL RT_DestroyMulitThread(RT_SystemMulitThreadInitInfoRef info) {

	auto _info = unwrap(info);

	delete _info->jobQueue;

	// Clean up the thread pool
	_info->threadPool->removeReference();

	delete info;
}

void HAVOK_C_CALL RT_StepWorld(hkpWorldRef physicsWorld, RT_SystemMulitThreadInitInfoRef info, float timestep) {
	
	if (info) {
		auto _info = unwrap(info);
		// Step the physics world. This single call steps using this thread and all threads
		// in the threadPool. For other products you add jobs, call process all jobs and wait for completion.
		// See the multithreading chapter in the user guide for details
		physicsWorld->stepMultithreaded(_info->jobQueue, _info->threadPool, timestep);

	
		// Step the visual debugger. We first synchronize the timer data
		//context->syncTimers(info->threadPool);
		//vdb->step();

		// Clear accumulated timer data in this thread and all slave threads
		hkMonitorStream::getInstance().reset();
		_info->threadPool->clearTimerData();
	}
	else {
		physicsWorld->stepDeltaTime(timestep);
	}
}

void HAVOK_C_CALL RT_Free(void* info) {
	if (info)
		free(info);
}
void HAVOK_C_CALL RT_Delete(void* info) {
	if (info)
		delete(info);
}