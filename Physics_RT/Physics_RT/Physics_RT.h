#if defined(__GNUC__)
#ifndef HAVOK_C_API
#define HAVOK_C_API __attribute__((visibility("default")))
#endif
#define HAVOK_C_CALL 
#define HAVOK_C_PTR
#elif defined(_MSC_VER) 
#ifndef HAVOK_C_API
#define HAVOK_C_API __declspec(dllexport)
#endif
#define HAVOK_C_CALL __cdecl
#define HAVOK_C_PTR
#else
#error
#endif

#include <stddef.h>
#include <stdint.h>
#include <memory.h>

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

#include "MathHeader.h"

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct hkpWorld* hkpWorldRef;
	typedef struct RT_SystemMulitThreadInitInfo* RT_SystemMulitThreadInitInfoRef;

	typedef void (HAVOK_C_CALL* ErrorReportCallback)(const char* msg);

	HAVOK_C_API void HAVOK_C_CALL RT_InitializeBaseSystem(ErrorReportCallback errorReportCallback);
	HAVOK_C_API RT_SystemMulitThreadInitInfoRef HAVOK_C_CALL RT_InitializeMulitThread();
	HAVOK_C_API void* HAVOK_C_CALL RT_GetMulitThreadJobQueue(RT_SystemMulitThreadInitInfoRef info);
	HAVOK_C_API void* HAVOK_C_CALL RT_GetMulitThreadThreadPool(RT_SystemMulitThreadInitInfoRef info);
	HAVOK_C_API int HAVOK_C_CALL RT_GetMulitThreadTotalNumThreadsUsed(RT_SystemMulitThreadInitInfoRef info);
	HAVOK_C_API void HAVOK_C_CALL RT_DestroyMulitThread(RT_SystemMulitThreadInitInfoRef info);

	HAVOK_C_API void HAVOK_C_CALL RT_StepWorld(hkpWorldRef physicsWorld, RT_SystemMulitThreadInitInfoRef info, float timestep);

	HAVOK_C_API void HAVOK_C_CALL RT_Free(void* info);
	HAVOK_C_API void HAVOK_C_CALL RT_Delete(void* info);
#ifdef __cplusplus
}
#endif