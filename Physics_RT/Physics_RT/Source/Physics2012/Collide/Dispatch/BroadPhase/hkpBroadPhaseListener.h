/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_BROAD_PHASE_LISTENER
#define HK_BROAD_PHASE_LISTENER

class hkpTypedBroadPhaseHandlePair;

	/// This is an interface class used by an application of the hkCollide lib for dispatching new collision pairs
class hkpBroadPhaseListener
{
	//+hk.MemoryTracker(ignore=True)
	public:
		virtual ~hkpBroadPhaseListener() {}

		virtual void addCollisionPair( hkpTypedBroadPhaseHandlePair& pair ) = 0;

		virtual void removeCollisionPair( hkpTypedBroadPhaseHandlePair& pair ) = 0;

};

#endif // HK_BROAD_PHASE_LISTENER

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
