/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKA_ANIMATION_VDB_CONTEXT_H
#define HKA_ANIMATION_VDB_CONTEXT_H

#include <Common/Visualize/hkProcessContext.h>


	/// This context is currently used to store timer data
class hkaAnimationContext : public hkReferencedObject, public hkProcessContext
{	
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_VDB);

		hkaAnimationContext( ) {}
		virtual ~hkaAnimationContext() {}
		
			/// As there can be any number of different user types
			/// of data contexts, the type is simply identified by string.
		virtual const char* getType() HK_OVERRIDE { return "animation"; }
};

#endif // HKA_ANIMATION_VDB_CONTEXT_H

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
