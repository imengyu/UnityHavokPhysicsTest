/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

hkpBvTreeShape::hkpBvTreeShape(ShapeType type, BvTreeType bvType )
:	hkpShape( type )
,	m_bvTreeType(bvType)
{}

inline hkUint32 hkpBvTreeShape::queryAabb(const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys ) const
{
#ifdef HK_PLATFORM_SPU
	HK_ASSERT(0x70d90357, m_bvTreeType >= 0 && m_bvTreeType < BVTREE_MAX);
	return (*s_bvTreeFunctions[m_bvTreeType].m_queryAabbFunc)(this, aabb, hits, maxNumKeys);
#else
	return queryAabbImpl(aabb, hits, maxNumKeys);
#endif
}

inline void hkpBvTreeShape::castAabb(const hkAabb& from, hkVector4Parameter to, hkpAabbCastCollector& collector) const
{
#ifdef HK_PLATFORM_SPU
	HK_ASSERT(0x70d90357, m_bvTreeType >= 0 && m_bvTreeType < BVTREE_MAX);
	(*s_bvTreeFunctions[m_bvTreeType].m_castAabbFunc)(this, from, to, collector);
#else
	castAabbImpl(from, to, collector);
#endif
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
