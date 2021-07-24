/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_BV_SHAPE_H
#define HK_COLLIDE2_BV_SHAPE_H

#include <Physics2012/Collide/Shape/hkpShape.h>
#include <Physics2012/Collide/Shape/hkpShapeContainer.h>

extern const hkClass hkpBvShapeClass;


	/// The idea of a hkpBvShape is to surround a complex shape or shape collection by
	/// a simple bounding volume shape. As long as the bounding volume shape does not collide
	/// we know that the complex shape can't collide.
	/// So, a hkpBvShape needs two hkpShape members, one of which is the child shape, the other
	/// of which describes the bounding volume used for the child shape.
	///
	/// For example, you could use an hkpBvShape to
	/// create a phantom with a spherical bounding volume. In that case, the child shape would be a hkpPhantomCallbackShape
	/// and the bounding volume shape would be a hkpSphereShape.
class hkpBvShape : public hkpShape
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE( hkcdShapeType::BV );

	public:

			/// Constructs the shape. The first parameter is the bounding volume shape, the second is the child shape.
		hkpBvShape( const hkpShape* boundingVolumeShape, const hkpShape* childShape );

#if !defined(HK_PLATFORM_SPU)

			/// Serialization constructor
		hkpBvShape( hkFinishLoadedObjectFlag flag );

			/// Destructor, removes references to child shapes.
		~hkpBvShape();

		virtual const hkpShapeContainer* getContainer() const;

#endif

	public:

			/// Gets the bounding volume shape.
		inline const hkpShape* getBoundingVolumeShape() const;

			/// Gets the child shape.
		inline const hkpShape* getChildShape() const;

	public:

			//	hkpShapeBase interface implementation.
 		virtual void getAabb( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const;

			/// A ray cast. The current implementation directly forwards to the child shape and does not check the bounding volume shape
		virtual hkBool castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results ) const;

			/// hkRayCollector driven raycast implementation using the data driven.
			/// A ray cast. The current implementation directly forwards to the child shape and does not check the bounding volume shape
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

	public:

		const hkpShape*		m_boundingVolumeShape;
		class hkpSingleShapeContainer m_childShape;
};

#include <Physics2012/Collide/Shape/Misc/Bv/hkpBvShape.inl>


#endif // HK_COLLIDE2_BV_SHAPE_H

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
