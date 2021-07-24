/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HK_CRITICAL_SECTION_H
#define HKBASE_HK_CRITICAL_SECTION_H

#include <Common/Base/Config/hkConfigThread.h>
#include <Common/Base/Monitor/hkMonitorStream.h>


#if defined(HK_PLATFORM_WIN32)
#	include <Common/Base/Fwd/hkwindows.h>
#elif defined(HK_PLATFORM_XBOX360)
#	include <xtl.h>
#elif defined(HK_PLATFORM_PS3_PPU) || defined(HK_PLATFORM_PS3_SPU) 
#	include <cell/sync.h>
#	if defined(HK_PLATFORM_PS3_PPU) 
#		include <sys/synchronization.h>	
#	endif
#elif defined(HK_PLATFORM_MACPPC) || defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_IOS) || defined(HK_PLATFORM_LINUX) || \
      defined(HK_PLATFORM_LRBXENSIM) || defined(HK_PLATFORM_ANDROID) || defined(HK_PLATFORM_TIZEN) || defined(HK_PLATFORM_PS4) 
#	include <pthread.h>
#elif defined(HK_PLATFORM_WIIU) 
#	include <cafe/os.h>
#elif defined(HK_PLATFORM_LRBSIM) 
#	include <common/winpthread.h>
#elif defined(HK_PLATFORM_PSVITA) 
#	include <kernel.h>
#endif

#include <Common/Base/Thread/Thread/hkThreadLocalData.h>

	// Set this define if you want a timer begin and timer end call 
	// if a thread has to wait for a critical section
	// You also have to call hkCriticalSection::setTimersEnabled()
//#define HK_TIME_CRITICAL_SECTION_LOCKS

#if !defined (HK_TIME_CRITICAL_SECTION_LOCKS) && defined(HK_PLATFORM_SIM)
#	define HK_TIME_CRITICAL_SECTION_LOCKS
#endif

#define HK_PS3_CRITICAL_SECTION_SYSTEM_WAIT 1

	/// Critical section wrapper. This can be used to guard access
	/// to shared data structures between threads.
	/// Note that critical sections are fast but have serious drawbacks.
	/// Check windows help for details.
	/// Note that including this file means including a system file, such as windows.h,
	/// which makes compile time significantly slower.
class hkCriticalSection
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE_CLASS, hkCriticalSection);

#	if !defined(HK_PLATFORM_PS3_SPU)
			/// Init a critical section with spin count.
			/// Read MSDN help of InitializeCriticalSectionAndSpinCount for details.
			///
			/// In short: positive spinCount value results in threads doing busy waiting and is good
			/// when you know that the critical section will only be locked for a short period of time.
			/// zero value causes the thread to immediately go back to the system when waiting.
		hkCriticalSection( int spinCount = 0);

			/// Quit a critical section
		inline ~hkCriticalSection();

			/// Lock a critical section
		void enter();

			/// Unlock a critical section
		void leave();


			/// Tell the critical section to time blocking locks. HK_TIME_CRITICAL_SECTION_LOCKS must be
			/// defined at compile time for this flag to have any effect
		static inline void HK_CALL setTimersEnabled();

			/// Stop timing blocking locks
		static inline void HK_CALL setTimersDisabled();
#	else
		inline hkCriticalSection(int spinCount=0) {}
#	endif

		/// adds a value to a variable in a thread safe way and returns the old value
		static HK_FORCE_INLINE hkUint32 HK_CALL atomicExchangeAdd(hkUint32* var, int value);

		/// waits until the value of *var is not value and returns the value of *var
		static hkUint32 waitForValueEqual( hkUint32* var, hkUint32 value );
		static hkUint32 waitForValueNotEqual( hkUint32* var, hkUint32 value );
		static hkUint16 waitForValueNotEqual( hkUint16* var, hkUint16 value );

#if defined( HK_PLATFORM_SPU )
		/// Lock a critical section if you only have the PPU address of the class. This does not allow recursive locking.
		static HK_FORCE_INLINE void HK_CALL enter( HK_CPU_PTR(hkCriticalSection*) sectionOnPpu );

		/// Unlock a critical section if you only have the PPU address of the class. This does not allow recursive locking.
		static HK_FORCE_INLINE void HK_CALL leave( HK_CPU_PTR(hkCriticalSection*) sectionOnPpu );
#endif

	public:

#if HK_CONFIG_THREAD == HK_CONFIG_MULTI_THREADED
#	if defined(HK_PLATFORM_PS3_PPU) || defined(HK_PLATFORM_PS3_SPU) 
		// Busy wait mutex used on both PPU and SPU,  a uint32, 
		// not used as this data on SPU, but used through the ptr to the actual one in main mem.
		CellSyncMutex m_mutex; // 32bits
		hkInt32 m_recursiveLockCount;
		hkUint64 m_currentThread; // if this == current, then we have the lock already and just inc recursion count
		
#		if defined(HK_PS3_CRITICAL_SECTION_SYSTEM_WAIT)
#			if defined(HK_PLATFORM_PS3_PPU)// PPU  
				// have a kinder system level lock first, so that PPU threads
				// can sleep on locks with each other. ie, if this is locked, then a 
				// ppu thread has the lock, and we can sleep on it
				sys_lwmutex_t m_ppuMutex;
#			else  // SPU
				hkUint32 m_lwMutexPadding32[6];
#			endif
#		endif


#	elif defined(HK_PLATFORM_MACPPC) || defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_IOS) || defined(HK_PLATFORM_LINUX) || defined(HK_PLATFORM_ANDROID) || defined(HK_PLATFORM_TIZEN) || defined(HK_PLATFORM_PS4)

		/// OS mutex
		pthread_mutex_t m_mutex;

		/// Number of times that will try to lock the mutex before blocking
		int m_spinCount;

#	elif defined(HK_PLATFORM_WIIU) 
		
		OSSpinLock m_mutex;

#	elif defined(HK_PLATFORM_PSVITA)
		hkInt32 m_recursiveLockCount;
		volatile SceUID m_currentThread; 
//#	elif defined(HK_PLATFORM_ANDROID)
//		hkInt32 m_recursiveLockCount;
//		volatile hkUint32 m_currentThread; 
#	else // other threaded platforms:
		CRITICAL_SECTION  m_section;
#	endif
#	ifdef HK_PLATFORM_HAS_SPU
			// points to this. This is useful for SPU simulation where this pointer
			// points to the main memory critical section
		HK_CPU_PTR(hkCriticalSection*) m_this;
#	endif
#endif
};

// move to static member when compiler support
#if HK_CONFIG_THREAD == HK_CONFIG_MULTI_THREADED && defined(HK_TIME_CRITICAL_SECTION_LOCKS)
	extern HK_THREAD_LOCAL( int ) hkCriticalSection__m_timeLocks;
#endif

// include the inl before the hkCriticalSectionLock def so 
// that gcc can inline the enter and leave properly
#if HK_CONFIG_THREAD != HK_CONFIG_MULTI_THREADED 
#		include <Common/Base/Thread/CriticalSection/Empty/hkEmptyCriticalSection.inl>
#else // HK_CONFIG_THREAD == HK_CONFIG_MULTI_THREADED 
#	include <Common/Base/Thread/Thread/hkThread.h>
#	define HK_INVALID_THREAD_ID (hkUint64(-1))

#	if defined(HK_PLATFORM_PS3_PPU) 
#		include <Common/Base/Thread/CriticalSection/Ps3/hkPs3CriticalSection.inl>
#	elif defined(HK_PLATFORM_PS3_SPU) 
#		include <Common/Base/Thread/CriticalSection/Ps3/hkPs3SpuCriticalSection.inl>
#   elif defined(HK_PLATFORM_MACPPC) || defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_IOS)
#		include <Common/Base/Thread/CriticalSection/Mac/hkMacCriticalSection.inl>
#	elif defined(HK_PLATFORM_LINUX) || defined(HK_PLATFORM_ANDROID) || defined(HK_PLATFORM_TIZEN) || defined(HK_PLATFORM_PS4)
#		include <Common/Base/Thread/Thread/Posix/hkPosixCheck.h>
#		include <Common/Base/Thread/CriticalSection/Posix/hkPosixCriticalSection.inl>
#	elif defined(HK_PLATFORM_WIIU)
#		include <Common/Base/Thread/CriticalSection/WiiU/hkWiiuCriticalSection.inl>
#	elif defined(HK_PLATFORM_PSVITA)
#		include <Common/Base/Thread/CriticalSection/PsVita/hkPsVitaCriticalSection.inl>
//#	elif defined(HK_PLATFORM_ANDROID)
//#		include <Common/Base/Thread/CriticalSection/Arm/hkArmCriticalSection.inl>
#	elif !defined(HK_PLATFORM_PS3_SPU)
#		include <Common/Base/Thread/CriticalSection/Win32/hkWin32CriticalSection.inl>
#	endif
#endif

#if !defined(HK_PLATFORM_PS3_SPU)

	/// Helper class which locks a critical section as long is this object exists.
class hkCriticalSectionLock
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE_CLASS, hkCriticalSectionLock);

			/// Create a lock by entering a critical section.
		inline hkCriticalSectionLock( hkCriticalSection* section )
		{
			m_section = section;
			section->enter();
		}

			/// Destructor leaves the critical section
		inline ~hkCriticalSectionLock()
		{
			m_section->leave();
		}

	protected:
		hkCriticalSection* m_section;
};
#endif

#if !defined(HK_PLATFORM_SPU)
typedef hkCriticalSection hkDmaManager;
#endif

#endif // HKBASE_HK_CRITICAL_SECTION_H

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
