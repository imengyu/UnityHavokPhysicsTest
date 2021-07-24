/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_CONVEX_PIECE_SHAPE_H
#define HK_COLLIDE2_CONVEX_PIECE_SHAPE_H

#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.h>
#include <Physics2012/Collide/Shape/Deprecated/Mesh/hkpMeshShape.h>

extern hkReal hkConvexShapeDefaultRadius;

/// DEPRECATED. This shape will be removed in future releases of Havok Physics.
class hkpConvexPieceShape : public hkpConvexShape, protected hkpShapeContainer
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		hkpConvexPieceShape( hkReal radius = hkConvexShapeDefaultRadius );

		//
		// hkpConvexShape implementation
		//

			// hkpConvexShape::getSupportingVertex() interface implementation.
		virtual void getSupportingVertex( hkVector4Parameter direction, hkcdVertex& supportingVertex ) const;

			// hkpConvexShape interface implementation.
		virtual void convertVertexIdsToVertices( const hkpVertexId* ids, int numIds, hkcdVertex* verticesOut) const;

			// hkpConvexShape interface implementation
		virtual void getFirstVertex(hkVector4& v) const;


		//
		// hkpShape implementation
		//
		
			/// Used to pre-calculate the AABB for this shape.
		void calcAabb();

			// hkpShape interface implementation.
		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

			/// hkpShape interface implementation.
		virtual hkBool castRay( const hkpShapeRayCastInput& input,hkpShapeRayCastOutput& results) const;

			// hkpShape interface implementation.
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;


		//
		// hkpSphereRepShape implementation
		//

			/// hkpSphereRepShape implementation
		virtual int getNumCollisionSpheres() const;

			/// hkpSphereRepShape implementation
		virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;

		//
		// Shape Container
		//

#if !defined(HK_PLATFORM_SPU)

			/// 
		virtual const hkpShapeContainer* getContainer() const;

#endif

		virtual hkpShapeKey getFirstKey() const;

		virtual hkpShapeKey getNextKey( hkpShapeKey oldKey ) const;

		virtual const hkpShape* getChildShape(hkpShapeKey key, hkpShapeBuffer& buffer) const;

	public:

			/// Array of vertices on the perimeter of this convex piece
		hkVector4* m_vertices;

			/// The number of vertices in this convex piece.
		int m_numVertices;

			/// The underlying display mesh.
		const hkpShapeCollection* m_displayMesh;

			/// ShapeKeys for the triangles in the underlying display mesh that form this convex piece.
		const hkpShapeKey* m_displayShapeKeys;

			/// The number of triangles in this convex piece.
		int m_numDisplayShapeKeys;
};


#endif // HK_COLLIDE2_CONVEX_PIECE_SHAPE_H

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
