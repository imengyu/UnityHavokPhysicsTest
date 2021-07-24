/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKCD_RAY_BOX_INTERSECTION_H
#define HKCD_RAY_BOX_INTERSECTION_H

#include <Geometry/Internal/Types/hkcdRay.h>

	/// Raycast against an axis aligned box.
	/// See \ref RayCastDocumentation for common input and output parameter descriptions.
HK_FORCE_INLINE hkBool32 HK_CALL hkcdRayCastBox(
	const hkcdRay& ray,
	hkVector4Parameter vHalfExtents,
	hkSimdReal* HK_RESTRICT fractionInOut,
	hkVector4* HK_RESTRICT normalOut);

#include <Geometry/Internal/Algorithms/RayCast/hkcdRayCastBox.inl>

#endif	//	HKCD_RAY_BOX_INTERSECTION_H

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
