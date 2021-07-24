/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_COLLIDE2_TYPED_BROAD_PHASE_HANDLE_PAIR_H
#define HK_COLLIDE2_TYPED_BROAD_PHASE_HANDLE_PAIR_H

#include <Physics2012/Collide/BroadPhase/hkpBroadPhaseHandlePair.h>
#include <Physics2012/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseHandle.h>


///	A structure holding the result of a broadphase query.
class hkpTypedBroadPhaseHandlePair : public hkpBroadPhaseHandlePair
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BROAD_PHASE, hkpTypedBroadPhaseHandlePair );

			/// Get the first element.
		HK_FORCE_INLINE hkpTypedBroadPhaseHandle* getElementA() const;

			/// Get the second element.
		HK_FORCE_INLINE hkpTypedBroadPhaseHandle* getElementB() const;

			/// Given either elementA or elementB, get the other element.
		HK_FORCE_INLINE hkpTypedBroadPhaseHandle* getOther(hkpTypedBroadPhaseHandle* elem) const;

};

#include <Physics2012/Collide/Dispatch/BroadPhase/hkpTypedBroadPhaseHandlePair.inl>

#endif // HK_COLLIDE2_BROAD_PHASE_HANDLE_PAIR_H

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
