/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKSCENEDATA_MESH_HKXMESHSECTION_HKCLASS_H
#define HKSCENEDATA_MESH_HKXMESHSECTION_HKCLASS_H

/// hkxMeshSection meta information
extern const class hkClass hkxMeshSectionClass;

#include <Common/SceneData/Mesh/hkxIndexBuffer.h>
#include <Common/SceneData/Mesh/hkxVertexBuffer.h>
#include <Common/SceneData/Mesh/hkxVertexAnimation.h>
#include <Common/SceneData/Material/hkxMaterial.h>

/// A serialization wrapper for the relationship between a Vertex buffer and a set
/// of primitives.
class hkxMeshSection : public hkReferencedObject
{
	//+vtable(true)
	//+version(4)
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA );
		HK_DECLARE_REFLECTION();
	
		hkxMeshSection() { }
		hkxMeshSection(const hkxMeshSection& other);
		hkxMeshSection(hkFinishLoadedObjectFlag f ) : hkReferencedObject(f), m_vertexBuffer(f), m_indexBuffers(f), m_material(f), m_userChannels(f), m_vertexAnimations(f), m_linearKeyFrameHints(f) { }

		//
		// Members
		//
	public:
		
			/// The vertex buffer used by this section of the mesh.
		hkRefPtr< class hkxVertexBuffer > m_vertexBuffer;
		
			/// The set of primitives that use the vertex buffer.
		hkArray< hkRefPtr<hkxIndexBuffer> > m_indexBuffers;
		
			/// The material to use for this mesh. May be a multi material or a plain single
			/// material, or null.
		hkRefPtr< class hkxMaterial > m_material;

			/// User channels are expected to contain per-vertex, per-edge or per-face information.
			/// It will remove ref on them
		hkArray< hkRefVariant > m_userChannels;

			/// A frame-based alteration to the vertex buffer above
			/// Used for vertex animations and morph targets
		hkArray< hkRefPtr<hkxVertexAnimation> > m_vertexAnimations;

			/// The points in time that there were keyframes in seconds.
		hkArray< float > m_linearKeyFrameHints;
		
	public:

		/// Returns the number of triangles
		hkUint32 getNumTriangles () const;

		void getTriangleIndices (hkUint32 triIndex, hkUint32& indexAOut, hkUint32& indexBOut, hkUint32& indexCOut) const;


		//
		// Utility methods
		//

			/// Collects all vertex positions to the given array.
		void collectVertexPositions (hkArray<hkVector4>& verticesInOut) const;

			/// Constructs a hkGeometry object based on this mesh section and merges it with geometryInOut.
		void appendGeometry (struct hkGeometry& geometryInOut, int materialIndex = -1);
};

#endif // HKSCENEDATA_MESH_HKXMESHSECTION_HKCLASS_H

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
