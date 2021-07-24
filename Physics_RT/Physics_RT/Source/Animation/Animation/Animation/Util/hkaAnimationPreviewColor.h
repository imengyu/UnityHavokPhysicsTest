/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_ANIMATION_PREVIEW_COLOR_H
#define HK_ANIMATION_PREVIEW_COLOR_H

#include <Common/Base/Types/Color/hkColor.h>

/// hkaAnimationBinding meta information
extern const class hkClass hkaAnimationPreviewColorClass;
extern const class hkClass hkaAnimationPreviewColorContainerClass;


// Utility class to store hkaAnimationPreviewColor objects
class hkaAnimationPreviewColorContainer : public hkReferencedObject
{

public:
	// +version(1)

	HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_DATA );
	HK_DECLARE_REFLECTION();

	hkaAnimationPreviewColorContainer();

	virtual ~hkaAnimationPreviewColorContainer();

	// Adds a new color to this container
	void newPreviewColor( hkColor::Argb color );

	// Storage for hkaAnimationPreviewColor objects
	hkArray< hkColor::Argb > m_previewColor;

	public:

		// Constructor for initialisation of vtable fixup
		HK_FORCE_INLINE hkaAnimationPreviewColorContainer( hkFinishLoadedObjectFlag flag ) : hkReferencedObject(flag), m_previewColor(flag) {}
};

#endif // HK_ANIMATION_PREVIEW_COLOR_H

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
