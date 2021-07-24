/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifdef HK_PLATFORM_SPU
#	include <Common/Base/Memory/PlatformUtils/Spu/SpuDmaCache/hkSpu4WayCache.h>
#	include <Physics2012/Dynamics/World/Simulation/Multithreaded/Spu/hkpSpuConfig.h>

const void* HK_CALL GetArrayElemWithByteStridingHalfCacheSize( const void* base, int index, int elemsize, int dmaGroup = HK_SPU_DMA_GROUP_STALL, bool waitForCompletion = true  );

#define FETCH_DMA( TYPE, base, index ) (const TYPE*)GetArrayElemWithByteStridingHalfCacheSize( base, index, sizeof(TYPE) )

template <typename TYPE>
HK_ALWAYS_INLINE const TYPE* HK_CALL fetchDma( const TYPE* base, int index, 
											  int dmaGroup = HK_SPU_DMA_GROUP_STALL , bool waitForDmaCompletion = true )
{
	extern hkSpu4WayCache* g_SpuCollideUntypedCache;
	return hkGetArrayElemUsingCacheHalfSizeOutOfLine<TYPE>(base, index, g_SpuCollideUntypedCache,  HK_SPU_AGENT_SECTOR_JOB_MAX_UNTYPED_CACHE_LINE_SIZE );
}
#else
#	define FETCH_DMA( TYPE, base, index ) &base[index]
#endif

hkReal hkpCompressedMeshShape::getRadius() const
{
	return m_radius;
}


void hkpCompressedMeshShape::setRadius(hkReal r )
{
	m_radius = r;
}

void hkpCompressedMeshShape::getBigTriangle( int index, hkVector4& v0, hkVector4& v1, hkVector4& v2, hkUint16* welding ) const
{
	const BigTriangle* triangle = FETCH_DMA( BigTriangle, m_bigTriangles.begin(), index );
	if ( welding != HK_NULL )
	{
		*welding = triangle->m_weldingInfo;
	}

	v0 = *FETCH_DMA( hkVector4, m_bigVertices.begin(), triangle->m_a );
	v1 = *FETCH_DMA( hkVector4, m_bigVertices.begin(), triangle->m_b );
	v2 = *FETCH_DMA( hkVector4, m_bigVertices.begin(), triangle->m_c );

	if ( triangle->m_transformIndex != HK_CMS_NULL_REF )
	{
		hkQsTransform transform = *FETCH_DMA( hkQsTransform, m_transforms.begin(), triangle->m_transformIndex );
		v0.setTransformedPos( transform, v0 );
		v1.setTransformedPos( transform, v1 );
		v2.setTransformedPos( transform, v2 );
	}
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
