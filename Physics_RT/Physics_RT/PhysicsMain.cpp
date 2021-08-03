#include "stdafx.h"
#include "PhysicsHeader.h"
#include "PhysicsFunctions.h"
#include "MyErrorHandler.h"
#include <Common/Compat/hkHavokVersions.h>

#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_SERIALIZE_MIN_COMPATIBLE_VERSION HK_HAVOK_VERSION_Current

// Keycode
#include <Common/Base/keycode.cxx>
#include <Common/Base/Config/hkProductFeatures.cxx>

//Lib
#pragma comment(lib, "hkBase.lib")
#pragma comment(lib, "hkcdCollide.lib")
#pragma comment(lib, "hkcdInternal.lib")
#pragma comment(lib, "hkGeometryUtilities.lib")
#pragma comment(lib, "hkCompat.lib")
#pragma comment(lib, "hkInternal.lib")
#pragma comment(lib, "hkpCollide.lib")
#pragma comment(lib, "hkpConstraint.lib")
#pragma comment(lib, "hkpConstraintSolver.lib")
#pragma comment(lib, "hkpDynamics.lib")
#pragma comment(lib, "hkpInternal.lib")
#pragma comment(lib, "hkpPhysicsMigrationUtils.lib")
#pragma comment(lib, "hkpUtilities.lib")
#pragma comment(lib, "hkpVehicle.lib")
#pragma comment(lib, "hkSceneData.lib")
#pragma comment(lib, "hkSerialize.lib")
#pragma comment(lib, "hkVisualize.lib")

static void HK_CALL errorReport(const char* msg, void* userArgGivenToInit)
{
	APIErrorReport(msg, userArgGivenToInit);
}

void initCrashHandler();
void lateDeleteWordInfo();

sInitStruct initStruct;
void** apiArray = nullptr;
bool initSuccess = false;
hkJobQueue* jobQueue = nullptr;
hkJobThreadPool* threadPool = nullptr;

/*
* 获取是否初始化
*/
EXTERN_C_API int isInitSuccess() {
	return initSuccess;
}
/*
* Init function
*/
EXTERN_C_API void** init(sInitStruct* initStruct) {
	memcpy(&::initStruct, initStruct, sizeof(::initStruct));

	if (initSuccess)
		return apiArray;

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
	// Flush all denormal/subnormal numbers (2^-1074 to 2^-1022) to zero.
	// Typically operations on denormals are very slow, up to 100 times slower than normal numbers.
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif

	initCrashHandler();

	// Initialize the base system including our memory system
	// Allocate 0.5MB of physics solver buffer.

	
	hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault(hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(500000));
	hkBaseSystem::init(memoryRouter, errorReport);

	hkError::replaceInstance(new MyErrorHandler(errorReport, nullptr));

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
	return apiArray;
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

		lateDeleteWordInfo();
		DestroyFunctions();
		DestroySmallPool();
		initSuccess = false;
		return 1;
	}
	return 0;
}

#ifdef _WINDOWS

#include <stdio.h>
#include <stdlib.h>
#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")

BOOL GenerateCrashInfo(PEXCEPTION_POINTERS pExInfo, LPCWSTR info_file_name, LPCWSTR file_name, SYSTEMTIME tm, LPCWSTR dir) {

	FILE* fp = NULL;
	_wfopen_s(&fp, info_file_name, L"w");
	if (fp) {
		fwprintf_s(fp, L"=== Exception ===== %04d/%02d/%02d %02d:%02d:%02d ===========", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
		fwprintf_s(fp, L"\r\nAddress : 0x%08x  Code : 0x%08X  (0x%08X)",
			(ULONG_PTR)pExInfo->ExceptionRecord->ExceptionAddress, pExInfo->ExceptionRecord->ExceptionCode,
			pExInfo->ExceptionRecord->ExceptionFlags);
		fclose(fp);
		return TRUE;
	}
	return FALSE;
}
LONG GenerateMiniDump(PEXCEPTION_POINTERS pExInfo)
{
	TCHAR dmp_path[MAX_PATH];
	GetTempPath(MAX_PATH, dmp_path);

	SYSTEMTIME tm;
	GetLocalTime(&tm);//获取时间
	TCHAR file_name[128];
	swprintf_s(file_name, L"%s\\PhysicsRTCrashDump%d%02d%02d-%02d%02d%02d.dmp", dmp_path,
		tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);//设置dmp文件名称
	TCHAR info_file_name[128];
	swprintf_s(info_file_name, L"%s\\PhysicsRTCrashInfo%d%02d%02d-%02d%02d%02d.txt", dmp_path,
		tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);

	//Create file
	HANDLE hFile = CreateFile(file_name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	//Generate Crash info
	BOOL hasCrashInfo = GenerateCrashInfo(pExInfo, info_file_name, file_name, tm, dmp_path);

	//Gen Dump File and show dialog

	TCHAR expInfo[128];
	swprintf_s(expInfo, L"Exception !!! Address : 0x%08x  Code : 0x%08X  (0x%08X)",
		(ULONG_PTR)pExInfo->ExceptionRecord->ExceptionAddress, pExInfo->ExceptionRecord->ExceptionCode,
		pExInfo->ExceptionRecord->ExceptionFlags);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION expParam;
		expParam.ThreadId = GetCurrentThreadId();
		expParam.ExceptionPointers = pExInfo;
		expParam.ClientPointers = FALSE;
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithDataSegs, (pExInfo ? &expParam : NULL), NULL, NULL);
		CloseHandle(hFile);

		TCHAR info[300];
		swprintf_s(info, L"Dump file: %s \nLast Error : %d", file_name, GetLastError());
		MessageBox(NULL, info, L"GenerateMiniDump", MB_ICONERROR | MB_SYSTEMMODAL);
	}
	else
	{
		TCHAR info[300];
		swprintf_s(info, L"Fail to create dump file: %s \nLast Error : %d", file_name, GetLastError());
		MessageBox(NULL, info, L"GenerateMiniDump", MB_ICONERROR | MB_SYSTEMMODAL);
	}
	return EXCEPTION_EXECUTE_HANDLER;
}
LONG WINAPI AppUnhandledExceptionFilter(PEXCEPTION_POINTERS pExInfo)
{
	if (IsDebuggerPresent())
		return EXCEPTION_CONTINUE_SEARCH;
	return GenerateMiniDump(pExInfo);
}

#endif // _WINDOWS

void initCrashHandler() {
#ifdef _WINDOWS
	SetUnhandledExceptionFilter(AppUnhandledExceptionFilter);
#endif // _WINDOWS
}

void setBuildUUID(char* uuid) {

}