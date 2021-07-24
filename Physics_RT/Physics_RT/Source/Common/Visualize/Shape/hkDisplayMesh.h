/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_VISUALIZE_DISPLAY_MESH_H
#define HK_VISUALIZE_DISPLAY_MESH_H

#include <Common/Visualize/Shape/hkDisplayGeometry.h>
#include <Common/Visualize/hkDisplayGeometryBuilder.h>

class hkMeshBody;

	/// Display geometry that contains a generic mesh body.
class hkDisplayMesh: public hkDisplayGeometry
{
	public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		
			/// Initializes the display mesh with a mesh
		hkDisplayMesh(hkMeshBody* mesh);		

			/// Gets the mesh body which the display mesh wraps
		hkMeshBody* getMesh() const;

			/// hkDisplayGeometry interface. Does nothing.
		virtual void buildGeometry();
			/// hkDisplayGeometry interface. Does nothing.
		virtual void getWireframeGeometry( hkArrayBase<hkVector4>& lines, hkMemoryAllocator& a );		

			/// Serializes the mesh to an internally stored buffer.
		void serializeMeshData();
			/// Frees any serialized mesh data.
		void freeSerializedMeshData();

			/// Gets the size of the buffer that holds the serialized mesh data. serializeMeshData must
			/// be called before this method.
		int getSeriaizedMeshDataSize() const;
			/// Gets the buffer that holds the serialized mesh data. serializeMeshData must
			/// be called before this method.
		const char* getSeriaizedMeshData() const;

	protected:

			/// The mesh which the display mesh wraps.
		hkRefPtr<hkMeshBody> m_mesh;
			/// The mesh serialized to a buffer. This is used in conjunction with the
			/// hkServerDebugDisplayHandler and is needed because the handler does not
			/// buffer the display data before sending it.
		hkArray<char> m_meshAsTagfile;
		
};

	/// Simple geometry builder that given a hkMeshBody wraps the hkMeshBody in a hkDisplayMesh.
class hkForwardingDisplayGeometryBuilder: public hkDisplayGeometryBuilder
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

			/// Builds a hkDisplayMesh from a source
		virtual void buildDisplayGeometries( const hkReferencedObject* source, hkArray<hkDisplayGeometry*>& displayGeometries );	
};

#endif // HK_VISUALIZE_SHAPE_AABB_H

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
