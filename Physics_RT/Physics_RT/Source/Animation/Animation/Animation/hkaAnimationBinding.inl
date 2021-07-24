/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkaAnimationBinding::hkaAnimationBinding()
:	m_blendHint(NORMAL)
{
}

HK_FORCE_INLINE hkaAnimationBinding::hkaAnimationBinding(const hkaAnimationBinding& other)
:	hkReferencedObject(other),
	m_originalSkeletonName(other.m_originalSkeletonName),
	m_animation(other.m_animation),
	m_blendHint(other.m_blendHint)
{
	m_transformTrackToBoneIndices = other.m_transformTrackToBoneIndices;
	m_floatTrackToFloatSlotIndices = other.m_floatTrackToFloatSlotIndices;
	m_partitionIndices = other.m_partitionIndices;
}

HK_FORCE_INLINE hkaAnimationBinding::hkaAnimationBinding( hkFinishLoadedObjectFlag flag )
:	hkReferencedObject(flag),
	m_originalSkeletonName(flag),
	m_animation(flag),
	m_transformTrackToBoneIndices( flag ),
	m_floatTrackToFloatSlotIndices( flag ),
	m_partitionIndices( flag )
{
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
