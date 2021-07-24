/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_STORAGEEXTENDEDMESHSHAPE_H
#define HK_STORAGEEXTENDEDMESHSHAPE_H

#include <Physics2012/Collide/Shape/Compound/Collection/ExtendedMeshShape/hkpExtendedMeshShape.h>

extern const class hkClass hkpStorageExtendedMeshShapeMaterialClass;

//#include <Physics2012/Collide/Shape/Compound/Collection/Mesh/hkpMeshMaterial.h>
#include <Physics2012/Collide/Shape/Compound/Collection/Mesh/hkpNamedMeshMaterial.h>
//#include <Common/Base/Container/String/hkString.h>
extern const hkClass hkpStorageExtendedMeshShapeClass;
extern const hkClass hkpStorageExtendedMeshShapeMeshSubpartStorageClass;
extern const hkClass hkpStorageExtendedMeshShapeShapeSubpartStorageClass;

//class hkString;

/// An extended mesh shape which stores its data.
/// NOTE: it is very error prone to modify the subparts of an
/// hkpStorageExtendedMeshShape directly because the subpart pointers need to
/// be updated if the storage is resized.
/// This class is primarily used internally, for taking snapshots of a world containing hkExtendedMeshShapes.
/// All hkExtendedMeshShapes are converted into hkpStorageExtendedMeshShape for serialization.
class hkpStorageExtendedMeshShape : public hkpExtendedMeshShape
{
	//+hk.ReflectedFile("hkpExtendedMeshShape")
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();

			/// Default constructor.
			/// The data for this shape is public, so simply fill in the
			/// member data after construction.
		hkpStorageExtendedMeshShape( hkReal radius = hkConvexShapeDefaultRadius, int numBitsForSubpartIndex = 12 );

			/// Copy the mesh into this mesh.
		hkpStorageExtendedMeshShape( const hkpExtendedMeshShape* mesh );

			///
		~hkpStorageExtendedMeshShape();

			/// Add the part and copy its data internally.
			/// NOTE: it is not recommended to modify a subpart after it
			/// has been added.
			/// NOTE: materials are not copied.
		virtual void addTrianglesSubpart( const TrianglesSubpart& part );
		virtual int addShapesSubpart( const ShapesSubpart& part );

	public:

		hkpStorageExtendedMeshShape( hkFinishLoadedObjectFlag flag );

		struct Material : public hkpMeshMaterial
		{
			// +version(1)
			HK_DECLARE_REFLECTION();
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CDINFO, Material);

			hkHalf m_restitution;
			hkHalf m_friction;
			hkUlong m_userData;
		};

		struct MeshSubpartStorage : public hkReferencedObject
		{
			public:
				// +version(3)

				HK_DECLARE_REFLECTION();
				HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);

				MeshSubpartStorage() {}
				virtual ~MeshSubpartStorage() {}

				hkArray<hkVector4> m_vertices;
				hkArray<hkUint8> m_indices8;
				hkArray<hkUint16> m_indices16;
				hkArray<hkUint32> m_indices32;
				hkArray<hkUint8> m_materialIndices; //materialIndices8
				hkArray<struct Material> m_materials;
				/// When the createRigidBodyFilter exports a mesh with "export triangle selections as materials" checked, then
				/// this array will store the names of the selections.
				hkArray<class hkpNamedMeshMaterial> m_namedMaterials;
				hkArray<hkUint16> m_materialIndices16;

			public:

				MeshSubpartStorage( hkFinishLoadedObjectFlag flag );
		};

		struct ShapeSubpartStorage : public hkReferencedObject
		{
			public:
				//+version(2)

				HK_DECLARE_REFLECTION();
				HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);

				ShapeSubpartStorage() {}
				virtual ~ShapeSubpartStorage() {}

				hkArray<hkUint8> m_materialIndices; //materialIndices8
				hkArray<struct Material> m_materials;
				hkArray<hkUint16> m_materialIndices16;

			public:

				ShapeSubpartStorage( hkFinishLoadedObjectFlag flag );
		};


	protected:

		friend class hkpShapeDisplayBuilder;
		hkArray<struct MeshSubpartStorage*> m_meshstorage;
		hkArray<struct ShapeSubpartStorage*> m_shapestorage;
};

#endif //HK_STORAGEEXTENDEDMESHSHAPE_H

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
