/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_CPU_COLLISION_QUERY_WORLD_GET_CLOSEST_POINTS_JOB_H
#define HK_CPU_COLLISION_QUERY_WORLD_GET_CLOSEST_POINTS_JOB_H


#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Physics2012/Collide/Agent/hkpProcessCollisionInput.h>

#include <Physics2012/Collide/BroadPhase/hkpBroadPhaseCastCollector.h>


class hkpGroupFilter;
class hkpFixedBufferCdPointCollector;


class hkCpuWorldGetClosestPointsCollector : public hkpBroadPhaseCastCollector
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkCpuWorldGetClosestPointsCollector);

	protected:

		hkReal addBroadPhaseHandle( const hkpBroadPhaseHandle* broadphaseHandle, int castIndex );

	public:

		// global, command-independent data
		const hkpGroupFilter*				m_filter;
		hkpFixedBufferCdPointCollector*		m_castCollector;

		// command-dependent data
		const hkpCollidable*				m_collidable;		// the collidable to be cast
		hkpShapeType						m_shapeType;
		hkpLinearCastCollisionInput			m_input;
};

hkJobQueue::JobStatus HK_CALL hkCpuWorldGetClosestPointsJob( hkJobQueue& jobQueue, hkJobQueue::JobQueueEntry& nextJobOut );


#endif // HK_CPU_COLLISION_QUERY_WORLD_GET_CLOSEST_POINTS_JOB_H

/*
 * Havok SDK - Base file, BUILD(#20131218)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2013
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available from salesteam@havok.com.
 * 
 */
