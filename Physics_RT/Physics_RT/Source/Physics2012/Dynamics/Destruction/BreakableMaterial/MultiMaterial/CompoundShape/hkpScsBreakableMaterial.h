/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_STATIC_COMPOUND_SHAPE_BREAKABLE_MATERIAL_H
#define HK_DYNAMICS2_STATIC_COMPOUND_SHAPE_BREAKABLE_MATERIAL_H

#include <Physics2012/Dynamics/Destruction/BreakableMaterial/MultiMaterial/hkpBreakableMultiMaterial.h>
#include <Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.h>

extern const hkClass hkpStaticCompoundShapeBreakableMaterialClass;

	//
	/// Multi-material specialized to work with a static compound shape.
class hkpStaticCompoundShapeBreakableMaterial : public hkpBreakableMultiMaterial
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012);

		typedef hkpStaticCompoundShape	StaticCompoundShape;

	public:

			/// Constructor
		hkpStaticCompoundShapeBreakableMaterial(const hkArray<hkpBreakableMaterial*>& subMaterials, hkReal strength = 0.0f);

			/// Copy constructor
		hkpStaticCompoundShapeBreakableMaterial(const hkpStaticCompoundShapeBreakableMaterial& other);

			/// Serialization constructor
		hkpStaticCompoundShapeBreakableMaterial(class hkFinishLoadedObjectFlag flag);

	public:

#ifndef HK_PLATFORM_SPU

			/// Returns the class type
		virtual const hkClass* getClassType() const;

			/// Clones the given material
		virtual hkpBreakableMaterial* duplicate();

			/// Sets the default mapping
		virtual void setDefaultMapping();

			/// Returns the index of the sub-material belonging to the given sub-shape.
		virtual MaterialId getSubShapeMaterialIndex(const hkcdShape* rootShape, hkUint32 subShapeId) const;

			/// Returns the material set on the given shape key
		virtual hkpBreakableMaterial* getShapeKeyMaterial(const hkcdShape* shapePpu, hkpShapeKey shapeKey) const;

			/// Converts a shape key into a sub-shape id the material is working with.
		virtual hkUint32 convertShapeKeyToSubShapeId(hkpShapeKey shapeKey) const;

			/// Converts a set of shape keys into their corresponding sub-shape ids in-place
		virtual void convertShapeKeysToSubShapeIds(hkArray<hkpShapeKey>& shapeKeysInOut) const;

			/// Collects the shape keys belonging to the given sub-shape
		virtual void getShapeKeysForSubShapes(const hkcdShape* rootShape, const hkUint32* subShapeIdPtr, int numSubShapeIds, ShapeKeyCollector* collector) const;

			/// Appends the sub-material indices set on the given sub-shapes to the given array
		virtual void getSubShapeMaterialIndices(const hkcdShape* rootShape, const hkArray<hkUint32>& subShapeIdsIn, hkArray<MaterialId>& subMaterialsOut) const;

			/// Disables a set of sub-shapes based on their sub-material Id
		virtual void disableSubShapes(hkcdShape* rootShape, const MaterialId* subMaterialIndices, int numSubMaterialIndices);

#endif
};

#endif	//	HK_DYNAMICS2_STATIC_COMPOUND_SHAPE_BREAKABLE_MATERIAL_H

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
