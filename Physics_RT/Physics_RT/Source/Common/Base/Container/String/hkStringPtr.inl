/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

inline const char* hkStringPtr::cString() const
{
	return hkClearBits(m_stringAndFlag, OWNED_FLAG);
}

inline hkStringPtr::operator const char*() const
{
	return cString();
}

inline int hkStringPtr::compareTo(const char* s) const
{
	const char* t = cString();
	if( t && s ) // both non null
	{
		return hkString::strCmp(t, s);
	}
	return t ? 1 : (s ? -1 : 0); // at least one null. null is "less" than all other non null strings
}

inline hkBool32 hkStringPtr::operator==(const char* cptr) const
{
	return compareTo(cptr) == 0;
}

inline hkBool32 hkStringPtr::operator!=(const char* cptr) const
{
	return compareTo(cptr) != 0;
}

inline hkBool32 hkStringPtr::startsWith(const char* s) const
{
	return hkString::beginsWith(cString(), s);
}

inline hkBool32 hkStringPtr::endsWith(const char* s) const 
{
	return hkString::endsWith(cString(), s);
}

inline char hkStringPtr::operator[](int idx) const
{
	const char* strAddr = this->cString();
	HK_ASSERT(0x2216fadd, strAddr != HK_NULL);
	HK_ON_DEBUG(bool idxInRange = (0 <= idx) && (idx < hkString::strLen(strAddr)) );
    HK_ASSERT(0x73c986fd, idxInRange );
	return strAddr[idx];
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
