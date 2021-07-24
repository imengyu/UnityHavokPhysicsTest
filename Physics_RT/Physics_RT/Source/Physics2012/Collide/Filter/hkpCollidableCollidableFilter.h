/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_COLLIDABLE_COLLIDABLE_FILTER_H
#define HK_COLLIDE2_COLLIDABLE_COLLIDABLE_FILTER_H


extern const class hkClass hkpCollidableCollidableFilterClass;

class hkpCollidable;

	/// A filter of this type is called whenever two collidables are considered for collision testing.
	/// This happens when a new broadphase overlap is detected.
class hkpCollidableCollidableFilter
{
	//+hk.MemoryTracker(ignore=True)
	public:
		HK_DECLARE_REFLECTION();

		virtual ~hkpCollidableCollidableFilter() { }

			/// Returns true if the specified objects can collide.
		virtual hkBool isCollisionEnabled( const hkpCollidable& a, const hkpCollidable& b ) const = 0;

};

#endif // HK_COLLIDE2_COLLIDABLE_COLLIDABLE_FILTER_H

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
