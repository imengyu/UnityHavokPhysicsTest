#pragma once

// Math and base include
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Container/String/hkStringBuf.h>
#include <Common/Base/Types/Geometry/hkStridedVertices.h>


// Dynamics includes
#include <Physics2012/Collide/hkpCollide.h>										
#include <Physics2012/Collide/Agent/ConvexAgent/SphereBox/hkpSphereBoxAgent.h>
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>					

#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>			
#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>	
#include <Physics2012/Collide/Filter/Group/hkpGroupFilter.h>

#include <Physics2012/Dynamics/World/hkpWorld.h>								
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>					
#include <Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>		
#include <Physics2012/Dynamics/Constraint/Breakable/hkpBreakableConstraintData.h>
#include <Physics2012/Dynamics/Constraint/Breakable/hkpBreakableListener.h>

#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>	
#include <Physics2012/Utilities/Collide/TriggerVolume/hkpTriggerVolume.h> 

#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>
#if defined(HK_PLATFORM_HAS_SPU)
#	include <Common/Base/Thread/Job/ThreadPool/Spu/hkSpuJobThreadPool.h>
#endif
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

// Visual Debugger includes
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>