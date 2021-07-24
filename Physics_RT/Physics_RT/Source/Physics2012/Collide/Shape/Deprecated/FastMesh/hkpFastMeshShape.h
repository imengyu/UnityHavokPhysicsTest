/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_FAST_MESH_SHAPE_H
#define HK_COLLIDE2_FAST_MESH_SHAPE_H

#include <Physics2012/Collide/Shape/Deprecated/Mesh/hkpMeshShape.h>

extern const hkClass hkpFastMeshShapeClass;


/// DEPRECATED. This shape will be removed in future releases of Havok Physics.
///
/// A specialized mesh, which implements a faster version of getChildShape() by
/// using a number of special requirements:
/// - only one subpart is allowed.
/// - all the vertices must be aligned on a 16 byte boundary
/// - only 16 bit triangle indices are used
class hkpFastMeshShape: public hkpMeshShape
{
	//+hk.ReflectedFile("hkpMeshShape")
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::TRIANGLE_COLLECTION);

		hkpFastMeshShape( hkReal radius = hkConvexShapeDefaultRadius, int numBitsForSubpartIndex = 12 );

#if !defined(HK_PLATFORM_SPU)

			/// Serialization constructor
		hkpFastMeshShape( hkFinishLoadedObjectFlag flag );

#endif

			//	hkpShapeCollection interface implementation.
			/// Because the hkpMeshShape references into your data,
			/// it must create a new hkpTriangleShape to return to the caller when this function is called.
			/// This triangle is stored in the char* buffer.
			/// Degenerate triangles in the client data are handled gracefully through this method.
		virtual const hkpShape* getChildShape( hkpShapeKey key, hkpShapeBuffer& buffer ) const;
};

#endif // HK_COLLIDE2_FAST_MESH_SHAPE_H

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
