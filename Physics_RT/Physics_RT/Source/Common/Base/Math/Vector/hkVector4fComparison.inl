/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


HK_FORCE_INLINE /*static*/ hkVector4ComparisonMask::Mask HK_CALL hkVector4fComparison::getMaskForComponent(int i)
{
	// note check compile time assert in .cpp file
	HK_MATH_ASSERT(0x2337f8c7, (i>=0) && (i<4), "Component index out of range" );
	return hkVector4ComparisonMask::Mask(1 << i);
}

HK_FORCE_INLINE int hkVector4fComparison::getIndexOfLastComponentSet() const
{
#if defined(HK_PLATFORM_SPU)
	const int mask = getMask();
	return ((0xffffaa50)>>(mask<<1))&0x3;
#else
	return hkVector4Comparison_maskToLastIndex[getMask()];
#endif
}

HK_FORCE_INLINE int hkVector4fComparison::getIndexOfFirstComponentSet() const
{
#if defined(HK_PLATFORM_SPU)
	const int mask = getMask();
	return ((0x12131210)>>(mask<<1))&0x3;
#else
	return hkVector4Comparison_maskToFirstIndex[getMask()];
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
