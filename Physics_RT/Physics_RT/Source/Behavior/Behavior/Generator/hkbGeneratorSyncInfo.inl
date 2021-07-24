/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkbGeneratorSyncInfo::hkbGeneratorSyncInfo( const hkbGeneratorSyncInfo& syncInfo )
{
	hkString::memCpy( this, &syncInfo, sizeof(hkbGeneratorSyncInfo) );

	m_isMirrored = false;
}

HK_FORCE_INLINE void hkbGeneratorSyncInfo::operator = ( const hkbGeneratorSyncInfo& syncInfo )
{
	hkString::memCpy( this, &syncInfo, sizeof(hkbGeneratorSyncInfo) );

	m_isMirrored = false;
}

HK_FORCE_INLINE void hkbGeneratorSyncInfo::setUnsyncable()
{
	m_numSyncPoints = 0;
	m_duration = 0.0f;
	m_localTime = 0.0f;
	m_playbackSpeed = 1.0f;	
	m_activeInterval.reset();
}

HK_FORCE_INLINE bool hkbGeneratorSyncInfo::canSync() const
{
	return ( m_duration != 0.0f );
}

HK_FORCE_INLINE bool hkbGeneratorSyncInfo::isAdditive() const
{
	return m_isAdditive;
}

HK_FORCE_INLINE hkReal hkbGeneratorSyncInfo::getDuration() const
{
	return m_duration;
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
