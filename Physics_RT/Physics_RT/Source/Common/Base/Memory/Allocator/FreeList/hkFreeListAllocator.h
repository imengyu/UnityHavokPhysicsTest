/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_FREELIST_MEMORY
#define HK_FREELIST_MEMORY

#include <Common/Base/Memory/Allocator/Thread/hkThreadMemory.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Common/Base/Memory/Allocator/FreeList/hkFreeList.h>
#include <Common/Base/Memory/Allocator/FreeList/hkFixedSizeAllocator.h>

class hkMemorySnapshot;

	/// This class implements the hkMemoryAllocator interface, and uses freelists as the basis of
	/// small memory allocations, and a large block allocator for large memory allocations.
class hkFreeListAllocator : public hkMemoryAllocator, public hkMemoryAllocator::ExtendedInterface
{
	public:
		HK_DECLARE_PLACEMENT_ALLOCATOR();

		enum { SOFT_LIMIT_MAX = 0x7fffffff };

#if defined(HK_REAL_IS_DOUBLE)
		enum
		{
				/// The size smallest differential freelist size
			FREELIST_ALIGNMENT = 32,
				/// The maximum memory allocation size that will be handled via a freelist -> the rest go to the large
				/// block allocator.
				/// The size is designed to be big enough to hold a complete hkpRigidBody in free list
			MAX_FREELIST_SIZE = hkThreadMemory::MEMORY_MAX_SIZE_SMALL_BLOCK,
				/// Shift to go from a size to a freelist
			FREELIST_SHIFT = 5,
				/// The total amount of size->freelist lookup entries
			MAX_FREELISTS = (MAX_FREELIST_SIZE >> FREELIST_SHIFT)+1,
				/// The total amount of unique freelists that is supported
			MAX_UNIQUE_FREELISTS = MAX_FREELISTS
		};
#else
		enum
		{
				/// The size smallest differential freelist size
			FREELIST_ALIGNMENT = 16,
				/// The maximum memory allocation size that will be handled via a freelist -> the rest go to the large
				/// block allocator.
				/// The size is designed to be big enough to hold a complete hkpRigidBody in free list
			MAX_FREELIST_SIZE = hkThreadMemory::MEMORY_MAX_SIZE_SMALL_BLOCK,
				/// Shift to go from a size to a freelist
			FREELIST_SHIFT = 4,
				/// The total amount of size->freelist lookup entries
			MAX_FREELISTS = (MAX_FREELIST_SIZE >> FREELIST_SHIFT)+1,
				/// The total amount of unique freelists that is supported
			MAX_UNIQUE_FREELISTS = MAX_FREELISTS
		};
#endif

		struct FreeListCinfo
		{
			hk_size_t m_elementSize;
			hk_size_t m_alignment;
			hk_size_t m_blockSize;
		};

		struct Cinfo
		{
				/// Ctor
			Cinfo(): m_preferedBlockSize(0),m_numInfos(0) {}
				/// Add an entry.
			void add(hk_size_t elementSize, hk_size_t alignment, hk_size_t blockSize);
				/// Find an info index by elementSize. Returns -1 if not found
			int findInfoIndex(hk_size_t elementSize) const;
				/// Remove at the index
			void removeAt(int index);

				/// Will use this block size for any internal freelists
			hk_size_t m_preferedBlockSize;

			int m_numInfos;
			FreeListCinfo m_infos[MAX_FREELISTS];
		};

		
			/// Default Ctor
		hkFreeListAllocator();
			/// Chain to another allocator.
		hkFreeListAllocator(hkMemoryAllocator* allocator, hkMemoryAllocator::ExtendedInterface* allocatorExtended, const Cinfo* info = HK_NULL);
			/// Dtor
		virtual ~hkFreeListAllocator();

		/// Intialize (can only be called once, and on a hkFreeListAllocator which has used the default constructor)
		void init(hkMemoryAllocator* allocator, hkMemoryAllocator::ExtendedInterface* allocatorExtended, const Cinfo* info = HK_NULL);

			// hkMemoryAllocator
		virtual void* blockAlloc(int nbytes) HK_OVERRIDE;

		virtual void blockFree(void*, int nbytes) HK_OVERRIDE;

		virtual void* bufAlloc(int& reqNumInOut) HK_OVERRIDE;

		virtual void blockAllocBatch(void** blocksOut, int nblocks, int nbytes) HK_OVERRIDE;

		virtual void blockFreeBatch(void** blocks, int nblocks, int nbytes) HK_OVERRIDE;

		virtual int getAllocatedSize( const void* p, int nbytes) const HK_OVERRIDE;

		virtual void getMemoryStatistics( MemoryStatistics& u ) const HK_OVERRIDE;

		virtual void resetPeakMemoryStatistics();

		/// hkMemoryAllocator::ExtendedInterface
		virtual void garbageCollect();
		virtual void incrementalGarbageCollect(int numBlocks);
		virtual hkResult setMemorySoftLimit(hk_size_t maxMemory);
		virtual hk_size_t getMemorySoftLimit() const;
		virtual bool canAllocTotal( int numBytes );
		virtual hkResult walkMemory(MemoryWalkCallback callback, void* param);
		virtual hk_size_t getApproxTotalAllocated() const;
		virtual void setScrubValues(hkUint32 allocValue, hkUint32 freeValue);
		virtual int addToSnapshot(hkMemorySnapshot& snap, int /*hkMemoryWalk::ProviderId*/ parentId);
		virtual hkMemoryAllocator::ExtendedInterface* getExtendedInterface() { return this; }

			/// Do some simple sanity checking.
		virtual hkBool isOk() const;

			/// Set up default Cinfo structure
		static void HK_CALL setDefaultCinfo(Cinfo& info);
			/// Setup the Cinfo with all underlying block sizes being the blockSize passed in.
			/// The minimum blockSize is 1k. Generally it is recommended that the block size should be a power of 2, although it is not
			/// a requirement
		static void HK_CALL setFixedSizeCinfo(hk_size_t blockSize, Cinfo& info);


	protected:

		void _construct(const Cinfo* info);

			/// NOTE! The new/delete are special they are designed to use a restricted memory system, such that
			/// memory freed with _deleteFreeList will only be available if it was the last allocation. I.e., its organised
			/// like stack memory.
			///
			/// Uses the simple contained memory allocation scheme.
			/// Also ensures there is only one freelist for each element size
		hkFreeList* _newFreeList(hk_size_t elementSize,hk_size_t alignment,hk_size_t blockSize);

			/// Deletes the freelist, without using up memory
		void _deleteFreeList(hkFreeList* freeList);

		static HK_FORCE_INLINE hkBool _comparePointers( void* a, void* b ) { return (char*)a < (char*)b; }

		bool _hasMemoryAvailable(hk_size_t size);


		mutable hkCriticalSection m_criticalSection;
		hk_size_t m_totalBytesInFreeLists;
		hk_size_t m_peakInUse;

		// The underlying allocator
		hkMemoryAllocator* m_allocator;
		// The extended interface (for garbageCollect etc, on underlying allocator)
		hkMemoryAllocator::ExtendedInterface* m_allocatorExtended;

		// This holds the block descriptions (held separately from the actual freelist blocks)
		hkFixedSizeAllocator m_blockAllocator;

			/// Freelists for the small sizes
		hkFreeList* m_sizeToFreeList[MAX_FREELISTS];

		hkFreeList* m_freeLists[MAX_FREELISTS];
		int m_numFreeLists;

			// We want this allocator to be self contained. So the memory to actually hold the freelists is allocated on
			// here. We just use a simple stack style memory allocation scheme to store the freelist objects
		hkFreeList* m_topFreeList;
		hkFreeList* m_lastFreeList;
		hkFreeList m_freeListMemory[MAX_UNIQUE_FREELISTS];

		hk_size_t m_softLimit;

		int m_incrementalFreeListIndex;			

	public:
			/// When HK_DEBUG is defined, returned memory is scrubbed with this value
		static hkUint32 s_fillReturnedToUser;
};

#endif // HK_FREELIST_MEMORY

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
