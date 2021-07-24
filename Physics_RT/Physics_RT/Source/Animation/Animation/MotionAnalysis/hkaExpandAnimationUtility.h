/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_EXPAND_ANIMATION_UTILITY_H
#define HK_EXPAND_ANIMATION_UTILITY_H

/// This utility can be used to expand the positions of the end
/// effectors of all bones into world space. It is useful for
/// analyzing a motion in detail
class hkaExpandAnimationUtility
{
public:
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_RUNTIME,hkaExpandAnimationUtility);


	hkaExpandAnimationUtility( const class hkaAnimationBinding* binding, const class hkaSkeleton* skeleton );
	hkaExpandAnimationUtility( class hkaAnimatedSkeleton* character, hkSimdRealParameter duration, int numSamples );

	hkVector4 getPosition( hkInt16 bone, int frame ) const;

	hkSimdReal getDuration() const;
	hkInt32 getNumBones() const;
	hkInt32 getNumFrames() const;

private:

	hkArray< hkVector4 > m_positions;
	hkSimdReal m_duration;
	hkInt32 m_numBones;
};


#endif // HK_EXPAND_ANIMATION_UTILITY_H

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
