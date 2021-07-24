/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_INTERNAL_LINE_SEGMENT_UTIL_H
#define HK_INTERNAL_LINE_SEGMENT_UTIL_H

class hkContactPoint;

/// Line segment utilities - find the closest point on a line segment, of between a pair of segments
class hkLineSegmentUtil
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkLineSegmentUtil);
		//
		//	EDGE EDGE
		//

		enum 
		{		
			CLSLS_POINTA_START = 1,		
			CLSLS_POINTA_END   = 2,		
			CLSLS_POINTB_START = 4,		
			CLSLS_POINTB_END   = 8		
		};

		struct ClosestLineSegLineSegResult
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_MATH, hkLineSegmentUtil::ClosestLineSegLineSegResult );

			hkVector4 m_closestPointA;
			hkVector4 m_closestAminusClosestB;
			hkPadSpu<hkReal>  m_distanceSquared;
			hkSimdReal  m_t;
			hkSimdReal  m_u;
		};

		/// Computes the closest points between two segments.
		/// Note that the second parameter is not the endpoint of the segment, but the vector from the start point to the end point.
		/// The same is true of the fourth parameter.
		/// returns (see enum): if bit is set, point can be deleted
		static int HK_CALL closestLineSegLineSeg( hkVector4Parameter A, hkVector4Parameter dA, hkVector4Parameter B, hkVector4Parameter dB, ClosestLineSegLineSegResult& result );

		/// Return the three closest points: point0: closest, point1: endPointA, point2 = endpointB.
		/// Expects the points.m_distance to be initialized with the collision.m_tolerance.
		/// The triangle and capsule points are expected to be in the same space (e.g., world space).
		/// In all cases the points[0] separating plane will be correctly set (not the position).
		/// returns (see enum)
		static int HK_CALL capsuleCapsuleManifold( const  hkVector4* capsA, hkReal capsARadius, const hkVector4* capsB, hkReal capsBRadius,	hkContactPoint* pointsOut );


		//
		//	POINT EDGE
		//

		struct ClosestPointLineSegResult
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_MATH, hkLineSegmentUtil::ClosestPointLineSegResult );

			hkVector4 m_pointOnEdge;
		};

		static int HK_CALL closestPointLineSeg( hkVector4Parameter A, hkVector4Parameter B0, hkVector4Parameter B1, ClosestPointLineSegResult& result );

		//
		// Infinite line / infinite line
		//

		struct ClosestPointInfLineInfLineResult
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, ClosestPointInfLineInfLineResult);
			/// The minimum distance squared
			hkPadSpu<hkReal> m_distanceSquared;

				/// The fraction along dA
			hkPadSpu<hkReal> m_fractionA;

				/// The fraction along dB
			hkPadSpu<hkReal> m_fractionB;

				/// The closest point on line A ( equal to A + m_fractionA*dA )
			hkVector4 m_closestPointA;

				/// The closest point on line B ( equal to B + m_fractionB*dB )
			hkVector4 m_closestPointB;
		};

			/// Compute the closest point between two infinite lines (each specified by a point and direction)
		static hkResult HK_CALL closestPointInfLineInfLine( const hkVector4& A, const hkVector4& dA, const hkVector4& B, const hkVector4& dB, ClosestPointInfLineInfLineResult& result);

		//
		// Infinite line / plane
		//

		struct IntersectionInfLinePlaneResult
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_MATH, hkLineSegmentUtil::IntersectionInfLinePlaneResult );

			/// The fraction along dA
			hkPadSpu<hkReal> m_fractionA;

			hkVector4 m_pointOnPlane;
		};

		/// Compute the intersection of an infinite line and a plane
		static hkResult HK_CALL intersectionInfLinePlane( const hkVector4& A, const hkVector4& dA, const hkVector4& planeEquation, IntersectionInfLinePlaneResult& result);

};

#endif // HK_INTERNAL_LINE_SEGMENT_UTIL_H

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
