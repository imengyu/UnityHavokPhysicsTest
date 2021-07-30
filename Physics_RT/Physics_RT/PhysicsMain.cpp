#include "stdafx.h"
#include "PhysicsHeader.h"
#include "PhysicsFunctions.h"

static void HK_CALL errorReport(const char* msg, void* userArgGivenToInit);

sInitStruct initStruct;
sApiStruct funStruct;
bool initSuccess = false;
hkJobQueue* jobQueue = nullptr;
hkJobThreadPool* threadPool = nullptr;

/*
* Init function
*/
EXTERN_C_API sApiStruct* init(sInitStruct* initStruct) {
	
	memcpy(&::initStruct, initStruct, sizeof(::initStruct));
		

	// Initialize the base system including our memory system
	// Allocate 0.5MB of physics solver buffer.

	hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault(hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(500000));
	hkBaseSystem::init(memoryRouter, errorReport);

	if (initStruct->mulithread) {

		// Initialize the multi-threading classes, hkJobQueue, and hkJobThreadPool
		// We can cap the number of threads used - here we use the maximum for whatever multithreaded platform we are running on. This variable is
		// set in the following code sections.
		int totalNumThreadsUsed;

#if defined HK_PLATFORM_PS3_PPU

		hkSpuJobThreadPoolCinfo threadPoolCinfo;

		extern CellSpurs* initSpurs();
		HK_CELL_SPURS* spurs = initSpurs();

		hkSpuUtil* spuUtil = new hkSpuUtil(spurs);

		threadPoolCinfo.m_spuUtil = spuUtil;
		threadPoolCinfo.m_maxNumSpus = 5; // Use 5 SPUs for this example

		totalNumThreadsUsed = 1; // only use one CPU thread for PS3.

		// This line enables timers collection, by allocating 200 Kb per thread.  If you leave this at its default (0),
		// timer collection will not be enabled.
		threadPoolCinfo.m_perSpuMonitorBufferSize = 200000;
		threadPool = new hkSpuJobThreadPool(threadPoolCinfo);
		spuUtil->removeReference();

#else

		// Get the number of physical threads available on the system
		hkHardwareInfo hwInfo;
		hkGetHardwareInfo(hwInfo);
		totalNumThreadsUsed = hwInfo.m_numThreads;

		// We use one less than this for our thread pool, because we must also use this thread for our simulation
		hkCpuJobThreadPoolCinfo threadPoolCinfo;
		threadPoolCinfo.m_numThreads = totalNumThreadsUsed - 1;

		// This line enables timers collection, by allocating 200 Kb per thread.  If you leave this at its default (0),
		// timer collection will not be enabled.
		threadPoolCinfo.m_timerBufferPerThreadAllocation = 200000;
		threadPool = new hkCpuJobThreadPool(threadPoolCinfo);

#endif

		// We also need to create a Job queue. This job queue will be used by all Havok modules to run multithreaded work.
		// Here we only use it for physics.
		hkJobQueueCinfo info;
		info.m_jobQueueHwSetup.m_numCpuThreads = totalNumThreadsUsed;
		jobQueue = new hkJobQueue(info);

		//
		// Enable monitors for this thread.
		//

		// Monitors have been enabled for thread pool threads already (see above comment).
		hkMonitorStream::getInstance().resize(200000);
	}
	else {

	}

	InitSmallPool();
	InitFunctions();
	initSuccess = true;
	return &funStruct;
}
/*
* Destroy
*/
EXTERN_C_API int quit() {
	
	if (jobQueue) {
		delete jobQueue;
		jobQueue = nullptr;
	}
	if (threadPool) {
		// Clean up the thread pool
		threadPool->removeReference();
		threadPool = nullptr;
	}
	if (initSuccess) {

		hkBaseSystem::quit();
		hkMemoryInitUtil::quit();

		DestroySmallPool();
		initSuccess = false;
		return 1;
	}
	return 0;
}

//Error Report

static void HK_CALL errorReport(const char* msg, void* userArgGivenToInit)
{
	if (initStruct.errCallback)
		initStruct.errCallback(msg);
#if defined(HK_PLATFORM_WIN32)
#ifndef HK_PLATFORM_WINRT
	OutputDebugStringA(msg);
#else
	// Unicode only 
	int sLen = hkString::strLen(msg) + 1;
	wchar_t* wideStr = hkAllocateStack<wchar_t>(sLen);
	mbstowcs_s(HK_NULL, wideStr, sLen, msg, sLen - 1);
	OutputDebugString(wideStr);
	hkDeallocateStack<wchar_t>(wideStr, sLen);
#endif
#endif
}
