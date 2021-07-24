/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_ACCURATE_INERTIA_TENSOR_COMPUTER_H
#define HK_DYNAMICS2_ACCURATE_INERTIA_TENSOR_COMPUTER_H

#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

void HK_CALL hkpAccurateInertiaTensorComputer_registerSelf();

// A class to accurately calculate the inertia tensor. The default calculation approximates a convex hull by its Aabb
class hkpAccurateInertiaTensorComputer: public hkpInertiaTensorComputer
{
	public:
			/// Calculate mass properties of a convex hull specified by its vertices.
			/// The convex hull might by expanded by 'radius' or automatically if the convex hull is not a value.
			/// Returns HK_FAILURE only if no vertices are provided, else always compute a valid mass properties and HK_SUCCESS
		static hkResult HK_CALL	computeConvexHullMassProperties(const hkStridedVertices& vertices, hkReal radius, hkMassProperties& result);
};

#endif

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
