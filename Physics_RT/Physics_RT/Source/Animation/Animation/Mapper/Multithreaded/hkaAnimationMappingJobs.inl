/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

hkaAnimationMappingJob::hkaAnimationMappingJob( hkaAnimationMappingJob::JobSubType subType, hkUint16 size )
: hkJob(HK_JOB_TYPE_ANIMATION_MAPPING, subType, size)
{
}

hkaAnimationMapPoseJob::hkaAnimationMapPoseJob() : hkaAnimationMappingJob(ANIMATION_MAPPING_JOB_MAP_POSE, sizeof(hkaAnimationMapPoseJob))
{
	m_mapper = HK_NULL;
	m_poseAIn = HK_NULL;
	m_poseBInOut = HK_NULL;
	m_poseBLocalSpaceIn = HK_NULL;
	m_source = hkaSkeletonMapper::NO_CONSTRAINTS;
	m_partitionIndicesA = HK_NULL;
	m_numPartitionsIndices = 0;
	m_numPartitionTransformsA = 0;
	m_numPartitionTransformsB = 0;

	m_mapToFullPose = true;

	m_isAdditive = false;

	m_jobDoneSemaphore = HK_NULL;
	m_jobDoneFlag = 0;
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
