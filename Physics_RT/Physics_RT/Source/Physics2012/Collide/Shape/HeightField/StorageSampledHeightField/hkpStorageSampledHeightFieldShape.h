/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE_STORAGESAMPLEDHEIGHTFIELDSHAPE_H
#define HK_COLLIDE_STORAGESAMPLEDHEIGHTFIELDSHAPE_H

#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.h>
#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldBaseCinfo.h>

extern const hkClass hkpStorageSampledHeightFieldShapeClass;

/// A heightfield shape which stores the heights as an array of hkReals.
/// This class is most useful for debug snapshots in the same way as hkpStorageMeshShape.
/// Normally the heightfield data would be stored in a more memory efficient manner,
/// possibly shared with other components.
///
/// hkpStorageSampledHeightFieldShape is also used as a simple heightfield implementation on the SPU
class hkpStorageSampledHeightFieldShape : public hkpSampledHeightFieldShape
{
	//+hk.ReflectedFile("hkpHeightField")
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();

		hkpStorageSampledHeightFieldShape( const hkpSampledHeightFieldShape* hf );

		hkpStorageSampledHeightFieldShape( const hkpSampledHeightFieldBaseCinfo& info, hkArray<hkReal>& samples );

		HK_FORCE_INLINE HKP_SHAPE_VIRTUAL hkReal getHeightAtImpl( HKP_SHAPE_VIRTUAL_THIS int x, int z ) HKP_SHAPE_VIRTUAL_CONST;

		HK_FORCE_INLINE HKP_SHAPE_VIRTUAL hkBool getTriangleFlipImpl(HKP_SHAPE_VIRTUAL_THIS2) HKP_SHAPE_VIRTUAL_CONST;

		virtual void collideSpheres( const CollideSpheresInput& input, SphereCollisionOutput* outputArray) const;

#if !defined(HK_PLATFORM_SPU)

		hkpStorageSampledHeightFieldShape( hkFinishLoadedObjectFlag f )
		:	hkpSampledHeightFieldShape(f)
		,	m_storage(f)
		{
			if( f.m_finishing )
			{
				m_heightfieldType = hkpSampledHeightFieldShape::HEIGHTFIELD_STORAGE;
			}
		}

			/// hkpShape Interface
		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;

#endif

	public:

		hkArray<hkReal> m_storage;
		hkBool m_triangleFlip;
};

#include <Physics2012/Collide/Shape/HeightField/StorageSampledHeightField/hkpStorageSampledHeightFieldShape.inl>

#endif // HK_COLLIDE_STORAGESAMPLEDHEIGHTFIELDSHAPE_H

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
