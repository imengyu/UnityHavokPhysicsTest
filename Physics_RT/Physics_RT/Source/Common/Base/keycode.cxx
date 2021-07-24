/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/KeyCode.h>

#if defined(HK_PLATFORM_GC) && !defined(HK_PLATFORM_WIIU)
#	define KEYCODE_ATTRIBUTES __attribute__((section(".sdata")))
#else
#	define KEYCODE_ATTRIBUTES
#endif

//
// PHYSICS_2012
//
#if !defined( HAVOK_PHYSICS_2012_KEYCODE )
#define HAVOK_PHYSICS_2012_KEYCODE ""
#endif
extern const char         HK_PHYSICS_2012_KEYCODE[] KEYCODE_ATTRIBUTES = HAVOK_PHYSICS_2012_KEYCODE;

//
// PHYSICS
//
#if !defined( HAVOK_PHYSICS_KEYCODE )
#define HAVOK_PHYSICS_KEYCODE ""
#endif
extern const char         HK_PHYSICS_KEYCODE[] KEYCODE_ATTRIBUTES = HAVOK_PHYSICS_KEYCODE;

//
// ANIMATION
//
#if !defined( HAVOK_ANIMATION_KEYCODE )
#define HAVOK_ANIMATION_KEYCODE ""
#endif
extern const char         HK_ANIMATION_KEYCODE[] KEYCODE_ATTRIBUTES = HAVOK_ANIMATION_KEYCODE;

//
// BEHAVIOR
//
#if !defined( HAVOK_BEHAVIOR_KEYCODE )
#define HAVOK_BEHAVIOR_KEYCODE ""
#endif
extern const char         HK_BEHAVIOR_KEYCODE[] KEYCODE_ATTRIBUTES = HAVOK_BEHAVIOR_KEYCODE;

//
// CLOTH
//
#if !defined( HAVOK_CLOTH_KEYCODE )
#define HAVOK_CLOTH_KEYCODE ""
#endif
extern const char         HK_CLOTH_KEYCODE[] KEYCODE_ATTRIBUTES = HAVOK_CLOTH_KEYCODE;

//
// DESTRUCTION_2012
//
#if !defined( HAVOK_DESTRUCTION_2012_KEYCODE )
#define HAVOK_DESTRUCTION_2012_KEYCODE ""
#endif
extern const char         HK_DESTRUCTION_2012_KEYCODE[] KEYCODE_ATTRIBUTES = HAVOK_DESTRUCTION_2012_KEYCODE;

//
// DESTRUCTION
//
#if !defined( HAVOK_DESTRUCTION_KEYCODE )
#define HAVOK_DESTRUCTION_KEYCODE ""
#endif
extern const char         HK_DESTRUCTION_KEYCODE[] KEYCODE_ATTRIBUTES = HAVOK_DESTRUCTION_KEYCODE;

//
// AI
//
#if !defined( HAVOK_AI_KEYCODE )
#define HAVOK_AI_KEYCODE ""
#endif
extern const char         HK_AI_KEYCODE[] KEYCODE_ATTRIBUTES = HAVOK_AI_KEYCODE;

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
