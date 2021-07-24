/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SHAPE_RAY_CAST_RESULTS
#define HK_SHAPE_RAY_CAST_RESULTS

#include <Physics2012/Collide/Shape/Query/hkpShapeRayCastCollectorOutput.h>

#if defined(HK_PLATFORM_SPU)
#	define hkpShapeRayCastCollectorOutput hkpShapeRayCastCollectorOutputPpu
#	define hkpShapeRayCastOutput hkpShapeRayCastOutputPpu
#endif

	/// The structure used for hkpShape::castRay results.
	/// Note: the structure can be used only for one raycast.
	/// If you want to reuse it, you have to call reset()
struct hkpShapeRayCastOutput : public hkpShapeRayCastCollectorOutput
{
	public:

			/// Maximum depth of key hierarchy.
		enum { MAX_HIERARCHY_DEPTH = 8 };

	public:

#if !defined(HK_PLATFORM_SPU)

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpShapeRayCastOutput );

			/// Create an initialized output.
		HK_FORCE_INLINE hkpShapeRayCastOutput();

			// Internal. Used for shapes containing child shapes.
		HK_FORCE_INLINE void changeLevel(int delta);

			// Internal. Used with changeLevel().
		HK_FORCE_INLINE void setKey(hkpShapeKey key);

			// Internal. Used with changeLevel().
		HK_FORCE_INLINE int getLevel() const;

#endif

			/// Resets this structure if you want to reuse it for another raycast, by setting the hitFraction to 1
		HK_FORCE_INLINE void reset();

	private:

		HK_FORCE_INLINE void _reset();

	public:

			/// The shapekeys of all the intermediate shapes down to the leaf shape which has been hit.
			/// The list ends with HK_INVALID_SHAPE_KEY. See the "Raycast Hit Hierarchy" section of the user guide.
		hkpShapeKey m_shapeKeys[MAX_HIERARCHY_DEPTH];

	private:

		int m_shapeKeyIndex;

};


#if !defined(HK_PLATFORM_SPU)
	typedef hkpShapeRayCastOutput hkpShapeRayCastOutputPpu;
#	include <Physics2012/Collide/Shape/Query/hkpShapeRayCastOutput.inl>
#else
#	undef hkpShapeRayCastOutput
#	undef hkpShapeRayCastCollectorOutput
#	include <Physics2012/Collide/Shape/Query/hkpShapeRayCastOutputSpu.h>
#endif

// Need to make sure this is declared AFTER the above preprocessor stuff
struct hkpShapeRayBundleCastOutput
{
	hkpShapeRayCastOutput m_outputs[4];
	void reset() { m_outputs[0].reset(); m_outputs[1].reset(); m_outputs[2].reset(); m_outputs[3].reset(); }
};



#endif //HK_SHAPE_RAY_CAST_RESULTS

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
