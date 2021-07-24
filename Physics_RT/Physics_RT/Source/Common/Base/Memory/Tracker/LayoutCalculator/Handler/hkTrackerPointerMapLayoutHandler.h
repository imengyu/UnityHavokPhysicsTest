/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_POINTERMAP_LAYOUT_HANDLER_H
#define HKBASE_POINTERMAP_LAYOUT_HANDLER_H

#include <Common/Base/Memory/Tracker/LayoutCalculator/hkTrackerLayoutCalculator.h>

class hkTrackerPointerMapLayoutHandler: public hkTrackerLayoutHandler
{
	public: 
		//+hk.MemoryTracker(ignore=True)
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

		virtual void getReferences(
			hkTrackerLayoutBlock* curBlock,
			const void* curData,
			const hkTrackerTypeTreeNode* curType,
			hkTrackerLayoutCalculator* layoutCalc,
			hkArray<const hkTrackerLayoutBlock*>::Temp& newBlocks );
		virtual hk_size_t getSize(
			const hkTrackerTypeTreeNode* curType,
			hkTrackerLayoutCalculator* layoutCalc );
};

#endif // HKBASE_POINTERMAP_LAYOUT_HANDLER_H

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
