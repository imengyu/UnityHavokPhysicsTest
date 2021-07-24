/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
// Build configuration settings
// These are compile time settings for the libraries.
// Changing these values with compiled libs will not work,

// If this setting is changed you must rebuild all Havok libs

// EQSELECT: HK_CONFIG_MONITORS, Runtime profile information (monitors)
// Whether runtime profiling information is collected or not.

#ifndef HK_BASE_CONFIGMONITORS_H
#define HK_BASE_CONFIGMONITORS_H

#define HK_CONFIG_MONITORS_DISABLED 0 // Disabled
#define HK_CONFIG_MONITORS_ENABLED 1 // Enabled

#ifndef HK_CONFIG_MONITORS

// VALUE:
#if defined(HK_PLATFORM_SPU)
#include <Common/Base/Config/hkConfigSpuMonitors.h>
#else
#	define HK_CONFIG_MONITORS HK_CONFIG_MONITORS_ENABLED
#endif

#endif // #ifndef HK_CONFIG_MONITORS

#endif // HK_BASE_CONFIGMONITORS_H

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
