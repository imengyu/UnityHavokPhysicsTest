/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SHAPE_RAY_COLLECTOR_OUTPUT_H
#define HK_SHAPE_RAY_COLLECTOR_OUTPUT_H

#include <Physics2012/Collide/Shape/hkpShape.h>

#if defined(HK_PLATFORM_SPU)
#	define hkpShapeRayCastCollectorOutput hkpShapeRayCastCollectorOutputPpu
#endif

	/// The structure used for hkpShape::castRayWithCollector results.
	/// Note: the structure can be used only for one raycast.
	/// If you want to reuse it, you have to call reset().
struct hkpShapeRayCastCollectorOutput
{
#if !defined(HK_PLATFORM_SPU)

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpShapeRayCastCollectorOutput );

		/// Constructor initializes the hitFraction to 1
	inline hkpShapeRayCastCollectorOutput();

		/// Returns true, if the ray had hit
	inline hkBool hasHit() const;

#endif

		/// Resets this structure if you want to reuse it for another raycast, by setting the hitFraction to 1
	inline void reset();

		/// The normalized normal of the surface hit by the ray. This normal is in the space of the ray.
	hkVector4 m_normal;

		/// This value will be in the range of [0..1]. It determines where along the ray the hit occurred, where 1 is the end position
		/// of the ray and 0 is the start position of the ray. It is also used as an "early out" value and has to be initialized with 1.0f
	hkReal m_hitFraction;

		/// Optional shape-dependent extra information.
		/// E.g., heightfields store the packed x and y coordinates of the triangle hit. Multisphere shapes store the index of the sphere.
		/// See the shapes castRay documentation to see which shapes support extraInfo.
	int m_extraInfo;

		/// Pad to multiple of 16 bytes
	int m_pad[2];
};


#if !defined(HK_PLATFORM_SPU)
	typedef hkpShapeRayCastCollectorOutput hkpShapeRayCastCollectorOutputPpu;
#	include <Physics2012/Collide/Shape/Query/hkpShapeRayCastCollectorOutput.inl>
#else
#	undef hkpShapeRayCastCollectorOutput
#	include <Physics2012/Collide/Shape/Query/hkpShapeRayCastCollectorOutputSpu.h>
#endif


#endif //HK_SHAPE_RAY_COLLECTOR_OUTPUT_H

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
