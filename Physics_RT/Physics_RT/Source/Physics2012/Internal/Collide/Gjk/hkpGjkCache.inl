/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

/***
 *** INLINE FUNCTION DEFINITIONS
 ***/

inline hkpGjkCache::hkpGjkCache()
{
	rSize = 0;	
}

inline void hkpGjkCache::reset()
{
	rSize = 0;	
}

inline void hkpGjkCache::swap (hkVector4* M, int i, int j)
{
	hkcdVertex tmp = Ra[i];
	Ra[i] = Ra[j];
	Ra[j] = tmp;

	tmp = Rb[i];
	Rb[i] = Rb[j];
	Rb[j] = tmp;

	hkVector4 m = M[i];
	M[i] = M[j];
	M[j] = m;
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
