/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef hkbPhysicsConfig_H
#define hkbPhysicsConfig_H

// By default hkbCharacterControllers will use the CharacterMovementUtil.
// This util takes into account any moving surfaces the character is on. Additionally, it applies the desired
// velocity along the surface normal (see hkpCharacterMovementUtil or hknpCharacterMovementUtil).
#define HKB_USE_CHARACTER_MOVEMENT_UTIL

// By default Proxy-based hkbCharacterControllers will use the previous frame's checkSupport results in applyVelocityModifiers.
// This could cause artifacts when the character is on a fast moving platform. Uncomment
// HKB_CHARACTER_PROXY_FRAME_ACCURATE_VELOCITY to perform an extra checkSupport before applyVelocityModifiers.
// This is only used if HKB_USE_CHARACTER_MOVEMENT_UTIL is defined.
// #define HKB_CHARACTER_PROXY_FRAME_ACCURATE_VELOCITY

// By default Rigid-Body-based hkbCharacterControllers will use the previous frame's checkSupport results in applyVelocityModifiers.
// This could cause artifacts when the character is on a fast moving platform. Uncomment
// HKB_CHARACTER_RIGID_BODY_FRAME_ACCURATE_VELOCITY to perform an extra checkSupport before applyVelocityModifiers.
// This is only used if HKB_USE_CHARACTER_MOVEMENT_UTIL is defined.
// #define HKB_CHARACTER_RIGID_BODY_FRAME_ACCURATE_VELOCITY

// Uncomment to do a more extensive searching for ragdoll data during ragdoll loading.
//#define HKB_EXTENDED_RAGDOLL_DATA_SEARCH

#endif // hkbPhysicsConfig_H

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
