/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


hkpWorld* hkpSimulationIsland::getWorld()
{
	return m_world;
}


inline hkBool hkpSimulationIsland::wasActiveLastFrame() const
{
	return m_isInActiveIslandsArray;
}

inline hkBool hkpSimulationIsland::isFixed() const
{
	return m_storageIndex == HK_INVALID_OBJECT_INDEX;
}

inline const hkArray<hkpEntity*>& hkpSimulationIsland::getEntities() const 
{ 
	return m_entities; 
}

inline const hkArray<hkpAction*>& hkpSimulationIsland::getActions() const 
{ 
	return m_actions; 
}


int hkpSimulationIsland::getStorageIndex()
{
	return m_storageIndex;
}

extern int HK_CALL hkpConstraintSolverSetup_calcBufferSize( const hkpSimulationIsland& island );

inline int hkpSimulationIsland::getMemUsageForIntegration()
{
	int sizeForElemTemp = m_constraintInfo.m_numSolverElemTemps * hkSizeOf(hkpSolverElemTemp) + 2 * hkSizeOf(hkpSolverElemTemp);
	int sizeForAccumulators = getEntities().getSize() * hkSizeOf(hkpVelocityAccumulator) + hkSizeOf(hkpVelocityAccumulator) + HK_REAL_ALIGNMENT; // fixed rigid body + end tag (16 byte aligned)
	int sizeForSchemas = m_constraintInfo.m_sizeOfSchemas + hkpJacobianSchemaInfo::End::Sizeof;

	int extraTasksDueToMt = 0;
#if HK_CONFIG_THREAD == HK_CONFIG_MULTI_THREADED
	{
		int minNumConstraintsPerTask = 80; //hkpBuildJacobianTask::MAX_NUM_ATOM_INFOS;
#		if defined(HK_PLATFORM_HAS_SPU)
		{
			int minNumConstraintBecauseOfAccumOverflow = (hkpSolveConstraintBatchTask::MAX_NUM_ACCUMULATORS_PER_TASK-1-1)/2;
			minNumConstraintsPerTask = hkMath::min2( minNumConstraintsPerTask, minNumConstraintBecauseOfAccumOverflow );
		}
#		endif

		extraTasksDueToMt = (m_numConstraints/minNumConstraintsPerTask) +1;
		extraTasksDueToMt += HKP_MAX_NUMBER_OF_CHAIN_CONSTRAINTS_IN_ISLAND_WHEN_MULTITHREADING;
		extraTasksDueToMt += 3;  // one task is the ppu only constraints + for high-normal constraints switch + also another task -- for ppu-high-normal switch
		extraTasksDueToMt *= 2; // multiply the num by 2 -- in the worst case you have a full task followed by a one-constraint task in every batch
	}
#endif
	sizeForSchemas += hkpJacobianSchemaInfo::End::Sizeof * extraTasksDueToMt;
	sizeForElemTemp += extraTasksDueToMt * (3*sizeof(hkReal));// (potential padding)
	sizeForElemTemp = HK_NEXT_MULTIPLE_OF(HK_REAL_ALIGNMENT, sizeForElemTemp);

	int totalSize = 	sizeForAccumulators + 
						sizeForSchemas +
						sizeForElemTemp;


#if defined(HK_DEBUG)
	int realSize = hkpConstraintSolverSetup_calcBufferSize( *this );
	HK_ASSERT2( 0xf0462376, realSize <= totalSize, "Inconsistent internal memory check. You can disable this warning but you should contact Havok support" );
#endif
	return totalSize;
}

inline void hkpSimulationIsland::markAllEntitiesReadOnly() const
{
#ifdef HK_DEBUG_MULTI_THREADING
	hkMultiThreadCheck::globalCriticalSectionLock();
	for ( int i = 0; i < m_entities.getSize(); ++i )
	{
		m_entities[i]->markForRead();
	}
	hkMultiThreadCheck::globalCriticalSectionUnlock();
#endif
}

// helper functions for debugging multithreading
inline void hkpSimulationIsland::unmarkAllEntitiesReadOnly() const
{
#ifdef HK_DEBUG_MULTI_THREADING
	hkMultiThreadCheck::globalCriticalSectionLock();
	for ( int i = 0; i < m_entities.getSize(); ++i )
	{
		m_entities[i]->unmarkForRead();
	}
	hkMultiThreadCheck::globalCriticalSectionUnlock();
#endif
}

inline void hkpSimulationIsland::unmarkForWrite()
{
	m_multiThreadCheck.unmarkForWrite();
}

inline hkpAgentNnTrack* hkpSimulationIsland::getAgentNnTrack( hkpAgentNnTrackType nnTrackType )
{
	return ( nnTrackType == HK_AGENT3_NARROWPHASE_TRACK ) ? &m_narrowphaseAgentTrack : &m_midphaseAgentTrack;
}

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
