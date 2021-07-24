/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


hkSubString::hkSubString(const char* cur)
{
	m_start = cur;
	m_end = cur + hkString::strLen(cur);
}

hkSubString::hkSubString(const char* start, const char* end):
	m_start(start),
	m_end(end)
{
}

hkSubString::hkSubString(const char* start, int len):
	m_start(start),
	m_end(start + len)
{
	HK_ASSERT(0x24344a32, len >= 0);
}


hkSubString::hkSubString(const hkSubString& rhs):
	m_start(rhs.m_start),
	m_end(rhs.m_end)
{
}


hkSubString::hkSubString():
	m_start(HK_NULL),
	m_end(HK_NULL)
{
}

void hkSubString::set(const char* cur, int len)
{
	m_start = cur;
	m_end = cur + len;
}

void hkSubString::set(const char* cur, const char* end)
{
	m_start = cur;
	m_end = end;
}

void hkSubString::operator=(const hkSubString& rhs)
{
	m_start = rhs.m_start;
	m_end = rhs.m_end;
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
