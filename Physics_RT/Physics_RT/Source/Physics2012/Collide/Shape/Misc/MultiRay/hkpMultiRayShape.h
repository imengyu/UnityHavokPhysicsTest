/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_MULTI_RAY_SHAPE_H
#define HK_COLLIDE2_MULTI_RAY_SHAPE_H

#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

extern const class hkClass hkpMultiRayShapeRayClass;

extern const hkClass hkpMultiRayShapeClass;

	/// A shape that allows you to cast multiple rays.
	/// If you use this shape as a normal shape as part of a hkpRigidBody, this
	/// shape will generate it's contact points using a rayCast.
	/// As a result, the rays are treated like solid objects.
class hkpMultiRayShape : public hkpShape
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::MULTI_RAY);

		///A ray from m_start to m_end.
		struct Ray
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpMultiRayShape::Ray );
			HK_DECLARE_REFLECTION();

			hkVector4 m_start;
			hkVector4 m_end;
		};

	public:

			/// Creates a new hkpMultiRayShape with the specified rays and a rayPenetrationDistance (See hkMultiRayShapeCinfo for more details).
		hkpMultiRayShape( const Ray* rays, int nRays, hkReal rayPenetrationDistance = 0.0f );

#if !defined(HK_PLATFORM_SPU)

			/// Serialization constructor
		hkpMultiRayShape( hkFinishLoadedObjectFlag flag );

#endif

	public:

			/// Returns the shape's rays extended by the shapes tolerance.
		inline const hkArray<Ray>& getRays() const{ return m_rays; }

			/// Returns the shape's ray penetration distance i.e., the distance each ray will be extended by and the distance that the physics system will allow each ray penetrate objects by. This helps to reduce jitter.
		inline hkReal getRayPenetrationDistance() const{ return m_rayPenetrationDistance; }

			// hkpShape implementation.
 		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

			/// Finds the closest intersection between the shape and a ray defined in the shape's local space, starting at fromLocal, ending at toLocal.
		virtual hkBool castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results ) const;

			/// a callback driven raycast
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

	protected:
			// The rays defined in local space
		hkArray<struct Ray> m_rays;

                        // The ray penetration distance
		hkReal m_rayPenetrationDistance;
};


#endif // HK_COLLIDE2_LINE_SEGMENT_SHAPE_H

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
