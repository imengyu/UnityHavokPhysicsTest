/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

inline void hkpMoppCode::initialize( const hkpMoppCode::CodeInfo& info, const hkUint8* moppData, int moppBytes, BuildType buildType )
{
	m_info = info;
	m_data.setDataAutoFree(const_cast<hkUint8*>(moppData), moppBytes, moppBytes);
	m_buildType = buildType;
}

#if !defined(HK_PLATFORM_SPU)
inline hkpMoppCode::hkpMoppCode( const hkpMoppCode::CodeInfo& info, const hkUint8* moppData, int moppBytes, BuildType buildType )
	:	m_info(info),
		m_data( const_cast<hkUint8*>(moppData), moppBytes, moppBytes)
{
	m_buildType = buildType;
}
#endif

inline hkReal hkpMoppCode::CodeInfo::getScale() const
{
	return m_offset(3);
}

inline void hkpMoppCode::CodeInfo::setScale( hkReal inVal )
{
	m_offset(3) = inVal;
}

inline hkInt32 hkpMoppCode::getCodeSize() const 
{ 
	return m_data.getSize(); 
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
