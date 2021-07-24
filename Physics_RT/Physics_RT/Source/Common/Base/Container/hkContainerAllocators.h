/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_BASE_CONTAINER_ALLOCATORS_H
#define HK_BASE_CONTAINER_ALLOCATORS_H

// These helper classes exist to allow containers to use different allocators
// without necessarily storing the allocator in the container.

#if !defined(HK_PLATFORM_PS3_SPU)

		/// Forwards to the temp allocator
	struct hkContainerTempAllocator
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkContainerTempAllocator);
		struct Allocator : public hkMemoryAllocator
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Allocator);
			virtual void* blockAlloc( int numBytes ) HK_OVERRIDE;
			virtual void blockFree( void* p, int numBytes ) HK_OVERRIDE;
			virtual void* bufAlloc( int& reqNumBytesInOut ) HK_OVERRIDE;
			virtual void bufFree( void* p, int numBytes ) HK_OVERRIDE;
			virtual void* bufRealloc( void* pold, int oldNumBytes, int& reqNumBytesInOut ) HK_OVERRIDE;
			virtual void getMemoryStatistics( MemoryStatistics& u ) const HK_OVERRIDE;
			virtual int getAllocatedSize(const void* obj, int nbytes) const HK_OVERRIDE;
		};
		static Allocator s_alloc;
		hkMemoryAllocator& get(const void*) { return s_alloc; }
	};

		/// Forwards to the heap allocator
	struct hkContainerHeapAllocator
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkContainerHeapAllocator);
		struct Allocator : public hkMemoryAllocator
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Allocator);
			virtual void* blockAlloc( int numBytes ) HK_OVERRIDE;
			virtual void blockFree( void* p, int numBytes ) HK_OVERRIDE;
			virtual void* bufAlloc( int& reqNumBytesInOut ) HK_OVERRIDE;
			virtual void bufFree( void* p, int numBytes ) HK_OVERRIDE;
			virtual void* bufRealloc( void* pold, int oldNumBytes, int& reqNumBytesInOut ) HK_OVERRIDE;
			virtual void getMemoryStatistics( MemoryStatistics& u ) const HK_OVERRIDE;
			virtual int getAllocatedSize(const void* obj, int nbytes) const HK_OVERRIDE;
		};
		static Allocator s_alloc;
		hkMemoryAllocator& get(const void*) { return s_alloc; }
	};

		/// Forwards to the debug allocator
	struct hkContainerDebugAllocator
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkContainerDebugAllocator);
		struct Allocator : public hkMemoryAllocator
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Allocator);
			virtual void* blockAlloc( int numBytes ) HK_OVERRIDE;
			virtual void blockFree( void* p, int numBytes ) HK_OVERRIDE;
			virtual void* bufAlloc( int& reqNumBytesInOut ) HK_OVERRIDE;
			virtual void bufFree( void* p, int numBytes ) HK_OVERRIDE;
			virtual void* bufRealloc( void* pold, int oldNumBytes, int& reqNumBytesInOut ) HK_OVERRIDE;
			virtual void getMemoryStatistics( MemoryStatistics& u ) const HK_OVERRIDE;
			virtual int getAllocatedSize(const void* obj, int nbytes) const HK_OVERRIDE;
		};
		static Allocator s_alloc;
		hkMemoryAllocator& get(const void*) { return s_alloc; }
	};

#else

	struct hkContainerHeapAllocator
	{
		hkMemoryAllocator& get(void*) { return hkThreadMemorySpu::getInstance(); }
	};
	typedef hkContainerHeapAllocator hkContainerDebugAllocator;
	typedef hkContainerHeapAllocator hkContainerTempAllocator;
#endif

/// Allocator used when generic allocation is required without affecting the
/// other allocators.
struct hkContainerDefaultMallocAllocator
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkContainerDefaultMallocAllocator);
	hkMemoryAllocator& get(const void*);
};

#endif // HK_BASE_CONTAINER_ALLOCATORS_H

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
