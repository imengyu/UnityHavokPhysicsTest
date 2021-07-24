/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SHAPE_BUFFER_H
#define HK_SHAPE_BUFFER_H

/// Attributes of the buffer used in getChildShape.
enum hkpBufferSize
{
#if !defined(HK_PLATFORM_HAS_SPU)
	HK_SHAPE_BUFFER_SIZE = 512 
#else
	HK_SHAPE_BUFFER_SIZE = 256 
#endif
};

/// A buffer type, allocated locally on the stack by calling functions,
/// to be passed to getChildShape.
typedef HK_ALIGN_REAL( char hkpShapeBuffer[HK_SHAPE_BUFFER_SIZE] );

#endif // HK_SHAPE_BUFFER_H

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
