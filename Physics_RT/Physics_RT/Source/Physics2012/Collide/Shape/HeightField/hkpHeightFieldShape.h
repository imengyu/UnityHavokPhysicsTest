/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_HEIGHT_FIELD_SHAPE_H
#define HK_COLLIDE2_HEIGHT_FIELD_SHAPE_H


#include <Physics2012/Collide/Shape/hkpShape.h>
#include <Physics2012/Collide/Shape/Query/hkpShapeRayCastInput.h>


extern const hkClass hkpHeightFieldShapeClass;

	/// An interface for a shape, which can collide with an array of spheres.
	///
	/// Behaviour:
	///   -  Per sphere only a single contact is reported.
	///   -  If the distance between a sphere and the heightfield is less than tolerance,
	///      than the normal and the distance is reported.
	///   -  If the distance is bigger than the tolerance,
	///      only a distance bigger than the tolerance is reported (not necessarily the correct distance)
	///      and the normal may be invalid.
class hkpHeightFieldShape: public hkpShape
{
	//+hk.ReflectedFile("hkpHeightField")

	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::HEIGHT_FIELD);

	public:

		struct CollideSpheresInput
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpHeightFieldShape::CollideSpheresInput );

				/// A pointer to the spheres
			class hkSphere* m_spheres;

				/// The number of the spheres
			int		  m_numSpheres;

				/// The extra tolerance, probably the hkpCollisionInput::m_tolerance
			hkReal	  m_tolerance;
		};

		typedef hkVector4 SphereCollisionOutput;


			/// Collide a number of spheres.
			///
			/// Rules:
			///     - Per sphere only a single contact is reported.
			///     - If the distance between a sphere and the heightfield is less than tolerance,
			///       then the normal and the distance is reported.
			///     - If the distance is bigger than the tolerance,
			///       a distance bigger than the tolerance is reported (not necessarily the correct distance)
			///       and the normal is invalid.
			///
			/// Note: if you call this function, you have to make sure that outputArray is big
			/// enough to hold all your data
		virtual void collideSpheres( const CollideSpheresInput& input, SphereCollisionOutput* outputArray) const = 0;

		struct hkpSphereCastInput: public hkpShapeRayCastInput
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpHeightFieldShape::hkpSphereCastInput );

			hkReal m_radius;
			hkReal m_maxExtraPenetration;
		};

		/// Cast a single sphere.
		/// Notes:
		///     - read the hkpCollisionAgent::linearCast for the behaviour of this function
		virtual void castSphere( const hkpSphereCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const = 0;

	public:

		hkpHeightFieldShape( ShapeType type )
		:	hkpShape( type )
		{}

#ifndef HK_PLATFORM_SPU

		hkpHeightFieldShape( hkFinishLoadedObjectFlag flag )
		:	hkpShape(flag)
		{
			setType(HKCD_SHAPE_TYPE_FROM_CLASS(hkpHeightFieldShape));
		}

#endif
};

#endif // HK_COLLIDE2_HEIGHT_FIELD_SHAPE_H

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
