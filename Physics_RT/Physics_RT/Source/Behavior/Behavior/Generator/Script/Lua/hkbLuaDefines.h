/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKB_LUA_DEFINES_H
#define HKB_LUA_DEFINES_H

#define HKB_HAVOK_SCRIPT_ENABLED 1
#define HKB_HAVOK_SCRIPT_DISABLED 2

// Only use Havok Script on platforms that support it
#if defined( HK_PLATFORM_WIN32 ) || defined( HK_PLATFORM_X64 ) || defined( HK_PLATFORM_PS3_PPU ) || defined( HK_PLATFORM_XBOX360 ) || \
	defined( HK_PLATFORM_RVL ) || defined( HK_PLATFORM_MAC386 ) || defined( HK_PLATFORM_IOS ) || defined( HK_PLATFORM_WIIU ) || defined( HK_PLATFORM_LINUX ) || \
	defined( HK_PLATFORM_PSVITA ) || defined( HK_PLATFORM_ANDROID ) || defined( HK_PLATFORM_PS4 ) || defined( HK_PLATFORM_DURANGO ) || defined ( HK_PLATFORM_TIZEN )

	// Havok Script is enabled on these platforms
	#define HKB_CONFIG_HAVOK_SCRIPT HKB_HAVOK_SCRIPT_ENABLED

#else

	// Havok Script is disabled for all others
	#define HKB_CONFIG_HAVOK_SCRIPT HKB_HAVOK_SCRIPT_DISABLED

#endif

#define HKB_HAVOK_SCRIPT_SYMBOLS_INTERNAL 1
#define HKB_HAVOK_SCRIPT_SYMBOLS_EXTERNAL 2
#define HKB_HAVOK_SCRIPT_SYMBOLS_DISABLED 3

#endif // HKB_LUA_DEFINES_H

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
