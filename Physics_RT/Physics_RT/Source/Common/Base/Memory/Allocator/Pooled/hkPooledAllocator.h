/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_hkPooledAllocator_H
#define HKBASE_hkPooledAllocator_H

#include <Common/Base/System/Io/OStream/hkOStream.h>

	/// 
class hkPooledAllocator : public hkMemoryAllocator
{
	//+hk.MemoryTracker(ignore=True)
	public:

			///
		hkPooledAllocator();

			/// Initialize pooled memory allocator. If an initial block is specified, it is used to satisfy allocations. If not, or once filled,
			/// subsequent allocations will be made from the block allocator. The initial block must remain valid for the lifetime of the allocator.
		void init(hkMemoryAllocator* internal, hkMemoryAllocator* large, hkMemoryAllocator* blocks, int blockSize, void *initialBlock = HK_NULL, int initialBlockSize = 0);

			///
		void quit();

		virtual void* blockAlloc( int numBytes ) HK_OVERRIDE;
		virtual void blockFree( void* p, int numBytes ) HK_OVERRIDE;
		
		hkBool32 isOk() const;

		virtual void getMemoryStatistics( MemoryStatistics& u ) const HK_OVERRIDE;
		virtual int getAllocatedSize(const void* obj, int nbytes) const HK_OVERRIDE;

			/// Purges allocated pools if there's no active allocations
		bool purge();

	protected:

		enum {
			MIN_ALIGNMENT = 4,
			MAX_ALIGNMENT = 16
		};
		void* m_curPtr;
		int m_curBytesLeft;

		int m_statsAllocated;
		int m_statsUsed;
		int m_statsPeak;

		hkMemoryAllocator* m_internal;
		hkMemoryAllocator* m_large;
		hkMemoryAllocator* m_block;
		int m_blockSize;
		hkMapBase<void*, int> m_largeAllocs;
		hkArrayBase<void*> m_blockAllocs;
};

#endif // HKBASE_hkPooledAllocator_H

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
