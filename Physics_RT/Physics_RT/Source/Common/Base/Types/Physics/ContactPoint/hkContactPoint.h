/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_CONTACT_POINT_H
#define HK_MATH_CONTACT_POINT_H

extern const class hkClass hkContactPointClass;

	/// A type used to store contact point ids
typedef hkUint16 hkContactPointId;

	/// Define an invalid contact point. Typically this is one which is not yet allocated by the hkpContactMgr
#define HK_INVALID_CONTACT_POINT (0xffff)

	/// Enable this to assert all setting of point position and normal are not storing NaNs
//#define HK_CONTACT_POINT_NAN_CHECKS

/// Contact point position, normal and distance. NOTE: All data is in World Space.
///
/// The class uses two hkVector4 variables, and stores the distance for the contact point
/// in the .w component of the m_separating variable.
///
/// m_normal always points such that moving object A in the direction of the normal 'separates'
/// the bodies. In other words, moving object A by -distance units in the direction of the normal
/// will bring the bodies into exact (surface) contact. The direction of the normal does not change
/// if the bodies become penetrating, but the distance will become negative. Thus the normal always points
/// "into" A, and "out of" B.
///
/// m_position is the contact point. It may be anywhere between the two "closest" points, depending on
/// the agent which created it, but usually it's on object B surface. In the penetrating case the "closest points"
/// is the pair which determines the direction of minimum separation.
///
/// The distance (returned by getDistance()) is the distance between "closest points" on A and B.
/// If this distance is negative, the bodies are penetrating.
///
/// NOTE: To be totally precise, moving object A in the positive direction of the normal 'separates' the
/// "closest points", but is not (in the case of concave or compound bodies) guaranteed to separate
/// the bodies themselves.
///
/// NOTE: When this structure is used in the hkpCdPointCollector callback from the hkpCollisionAgent::linearCast function,
/// the "distance" value is actually the parameter between 0 and 1 along the linear cast that the hit occurred
class hkContactPoint
{
	public:

		HK_DECLARE_REFLECTION();

			/// Get the position of the contact point.
		inline const hkVector4& getPosition() const;

			/// Set the position.
		inline void setPosition(const hkVector4& position);

			/// Get a reference to the normal and distance (just shorter name for getSeparatingNormal()).
		inline const hkVector4& getNormal() const;
 
			/// Get a reference to the normal and distance.
		inline const hkVector4& getSeparatingNormal() const;

			/// Sets the normal and separating plane component.
		inline void setSeparatingNormal( const hkVector4& normal, hkReal dist );

			/// Sets the normal and separating plane component.
		inline void setSeparatingNormal( hkVector4Parameter normal, hkSimdRealParameter dist );

			/// Sets the normal and separating plane component. 
			/// The distance must be contained in the third component of \a separatingNormal
		inline void setSeparatingNormal( const hkVector4& separatingNormal );

			/// Set only the normal, the distance is kept as is.
		inline void setNormalOnly( const hkVector4& normal );

			/// Get the distance as a simple scalar.
		inline hkReal getDistance() const;

			/// Get the distance as a scalar value suitable for SIMD processing.
		inline hkSimdReal getDistanceSimdReal() const;

			/// Set the distance.
		inline void setDistance( hkReal d );

			/// Set the distance.
		HK_FORCE_INLINE void setDistanceSimdReal(hkSimdRealParameter newValue);

			/// Set the position, normal and distance.
		inline void set( const hkVector4& position, const hkVector4& normal, hkReal dist );

			/// Set the position, normal and distance.
		HK_FORCE_INLINE void setPositionNormalAndDistance(hkVector4Parameter position, hkVector4Parameter normal, hkSimdRealParameter dist);

			/// Invert the direction of this contact.
			/// The normal is flipped and the contact position adjusted.
		inline void setFlipped( const hkContactPoint& point );

			/// Invert the direction of this contact.
			/// The normal is flipped and the contact position adjusted.
		inline void flip();

	protected:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkContactPoint );
	// Need this for now as the memory tracker definition inserts a public:
	protected:

		hkVector4 m_position;
		hkVector4 m_separatingNormal;			// .w is the the distance
};

#include <Common/Base/Types/Physics/ContactPoint/hkContactPoint.inl>

#endif // HK_MATH_CONTACT_POINT_H

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
