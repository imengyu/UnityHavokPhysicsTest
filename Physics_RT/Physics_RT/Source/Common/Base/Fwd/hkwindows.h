/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_BASE_WINDOWS_H
#define HK_BASE_WINDOWS_H

#if defined(HK_PLATFORM_WINRT)

// As using metro api lebvel etc:
#define NOMINMAX
#include <windows.h>

#elif !defined(_WINDOWS_) // may already be included, or should nto be allowed
// remember if we defined symbols so we can reset them afterward

#ifndef _WIN32_WINNT
#	if defined(HK_PLATFORM_WINRT) || defined(HK_PLATFORM_DURANGO)
#		define _WIN32_WINNT 0x0602 // Win8 or higher
#	else
#		define _WIN32_WINNT 0x0500   // Windows2000 or higher
#	endif
#   define HK_DEFINED_WIN32_WINNT
#endif

#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	define HK_DEFINED_WIN32_LEAN_AND_MEAN
#endif

#define NOGDICAPMASKS
#define NOVIRTUALKEYCODES
#define NOWINMESSAGES
#define NOWINSTYLES
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOKEYSTATES
#define NOSYSCOMMANDS
#define NORASTEROPS
//#define NOSHOWWINDOW
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOGDI
#define NOKERNEL
//#define NOUSER wsprintf
#define NONLS
#define NOMB
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOMSG
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOWINOFFSETS
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX

#ifndef __GCCXML__

#include <windows.h>

#endif

#ifdef HK_DEFINED_WIN32_WINNT
#	undef _WIN32_WINNT
#	undef HK_DEFINED_WIN32_WINNT
#endif
#ifdef HK_DEFINED_WIN32_LEAN_AND_MEAN
#	undef WIN32_LEAN_AND_MEAN
#	undef HK_DEFINED_WIN32_LEAN_AND_MEAN
#endif

#endif // ifndef _WINDOWS_ or winrt based

#endif // HK_BASE_WINDOWS_H

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
