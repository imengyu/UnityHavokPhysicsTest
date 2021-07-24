/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_VISUALIZE_SHAPE_PLANE_H
#define HK_VISUALIZE_SHAPE_PLANE_H

#include <Common/Visualize/Shape/hkDisplayGeometry.h>

class hkDisplayPlane : public hkDisplayGeometry
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		hkDisplayPlane();	
		hkDisplayPlane(const hkVector4& normal, const hkVector4& perpToNormal, 
			const hkVector4& center, const hkVector4& extents);


		virtual void buildGeometry();
		
		virtual void getWireframeGeometry( hkArrayBase<hkVector4>& lines, hkMemoryAllocator& a );
	
		void setParameters(const hkVector4& normal, const hkVector4& perpToNormal, 
						   const hkVector4& center,  const hkVector4& extents);

		hkVector4& getNormal();

		hkVector4& getCenter();

		hkVector4& getPerpToNormal();

		hkVector4& getExtents();

	protected:

		hkVector4 m_normal;
		hkVector4 m_center;
		hkVector4 m_perpToNormal;
		hkVector4 m_extent;

};

#endif // HK_VISUALIZE_SHAPE_PLANE_H

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
