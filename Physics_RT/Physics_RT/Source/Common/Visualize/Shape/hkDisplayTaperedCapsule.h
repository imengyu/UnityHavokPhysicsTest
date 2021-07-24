/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_VISUALIZE_SHAPE_TAPERED_CAPSULE_H
#define HK_VISUALIZE_SHAPE_TAPERED_CAPSULE_H

#include <Common/Visualize/Shape/hkDisplayGeometry.h>

class hkDisplayTaperedCapsule : public hkDisplayGeometry
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		hkDisplayTaperedCapsule( const hkVector4& top, const hkVector4& bottom, hkReal topRadius, hkReal bottomRadius,
							     int numSides = 6, int numHeightSegments = 3 );

		virtual void buildGeometry();

		virtual void getWireframeGeometry(hkArrayBase<hkVector4>& lines, hkMemoryAllocator& alloc);
		
		const hkVector4& getTop() { return m_top; }
		const hkVector4& getBottom() { return m_bottom; }
		hkReal getTopRadius() { return m_topRadius; }
		hkReal getBottomRadius() { return m_bottomRadius; }
		
		inline int getNumHeightSamples() { return m_numHeightSegments; }
		inline int getNumSides() { return m_numSides; }

	protected:

		hkVector4	m_top;
		hkVector4	m_bottom;
		hkReal		m_topRadius;
		hkReal		m_bottomRadius;

		int m_numSides;
		int m_numHeightSegments;
};


#endif // HK_VISUALIZE_SHAPE_TAPERED_CAPSULE_H

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
