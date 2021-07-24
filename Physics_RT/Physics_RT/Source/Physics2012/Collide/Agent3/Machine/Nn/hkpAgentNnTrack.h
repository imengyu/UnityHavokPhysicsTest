/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_COLLISION_AGENT_TRACK_H
#define HK_COLLIDE2_COLLISION_AGENT_TRACK_H

#include <Physics2012/Collide/Agent3/hkpAgent3.h>
typedef void hkpAgentData;
struct hkpAgentNnEntry;
struct hkpAgentNnSector; 
class hkpCollidable;

#if defined(HK_REAL_IS_DOUBLE)

#if ( HK_POINTER_SIZE == 4 ) 
#	define HK_AGENT3_MIDPHASE_AGENT_SIZE 80
#	define HK_AGENT3_NARROWPHASE_AGENT_SIZE 160
#	define HK_AGENT3_MAX_AGENT_SIZE 160
#	define HK_AGENT3_SECTOR_SIZE 640
#else
#	define HK_AGENT3_MIDPHASE_AGENT_SIZE 96
#	define HK_AGENT3_NARROWPHASE_AGENT_SIZE 192
#	define HK_AGENT3_MAX_AGENT_SIZE 192
#	define HK_AGENT3_SECTOR_SIZE 960
#endif

#else

#if ( HK_POINTER_SIZE == 4 ) 
#	define HK_AGENT3_MIDPHASE_AGENT_SIZE 64
#	define HK_AGENT3_NARROWPHASE_AGENT_SIZE 128
#	define HK_AGENT3_MAX_AGENT_SIZE 128
#	define HK_AGENT3_SECTOR_SIZE 512
#else
#	define HK_AGENT3_MIDPHASE_AGENT_SIZE 80
#	define HK_AGENT3_NARROWPHASE_AGENT_SIZE 160
#	define HK_AGENT3_MAX_AGENT_SIZE 160
#	define HK_AGENT3_SECTOR_SIZE 960
#endif

#endif

#define HK_AGENT3_FEWEST_AGENTS_PER_1N_SECTOR ( (HK_AGENT3_SECTOR_SIZE - HK_REAL_ALIGNMENT ) / HK_AGENT3_MAX_AGENT_SIZE )
#define HK_AGENT3_MIDPHASE_AGENTS_PER_NN_SECTOR ( HK_AGENT3_SECTOR_SIZE / HK_AGENT3_MIDPHASE_AGENT_SIZE )
#define HK_AGENT3_NARROWPHASE_AGENTS_PER_NN_SECTOR ( HK_AGENT3_SECTOR_SIZE / HK_AGENT3_NARROWPHASE_AGENT_SIZE )

enum hkpAgentNnTrackType
{
	HK_AGENT3_INVALID_TRACK = 0,
	HK_AGENT3_MIDPHASE_TRACK = 1,	///< For collisions which require midphase processing.
	HK_AGENT3_NARROWPHASE_TRACK = 2	///< For convex-convex collisions only.
};

	// Make sure if you use this entry that you pad to get a 16 byte alignment
	// Notes: 
	//
	//   HK_POINTER_SIZE == 4
	//   --------------------
	//   - sizeof(hkpAgentEntry) = 8
	//   - sizeof(hkpAgentNnEntry) = 8 + 20
	//
	//   HK_POINTER_SIZE == 8
	//   --------------------
	//   - sizeof(hkpAgentEntry) = 16
	//   - sizeof(hkpAgentNnEntry) = 16 + 32
struct hkpAgentNnEntry: public hkpAgentEntry
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkpAgentNnEntry );

	hkObjectIndex		m_agentIndexOnCollidable[2]; // this value must not be written back from spu!
	hkpContactMgr*		m_contactMgr;

	hkUchar				m_collisionQualityIndex;
	hkUchar				m_forceCollideOntoPpu;	// only used if the platform has an spu
	hkEnum<hkpAgentNnTrackType, hkUint8> m_nnTrackType; // Is this a convex-convex collision.
	hkUchar				m_padding;
	// Additional 4 bytes padding on 64-bit platforms
	hkpLinkedCollidable*	m_collidable[2];

	inline hkpCollidable*  getCollidableA(){ return reinterpret_cast<hkpCollidable*>(m_collidable[0]); }
	inline hkpCollidable*  getCollidableB(){ return reinterpret_cast<hkpCollidable*>(m_collidable[1]); }
};


struct hkpAgentNnSector
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_AGENT, hkpAgentNnSector);
	
	hkUint8 m_data[ HK_AGENT3_SECTOR_SIZE ];

	hkpAgentNnEntry* getBegin()
	{
		return reinterpret_cast<hkpAgentNnEntry*>( &m_data[0] );
	}

	hkpAgentNnEntry* getEnd()
	{
		return reinterpret_cast<hkpAgentNnEntry*>( &m_data[HK_AGENT3_SECTOR_SIZE] );
	}
};

struct hkpAgentNnTrack
{
	hkpAgentNnTrack( hkpAgentNnTrackType nnTrackType )
	{
#if defined(HK_PLATFORM_HAS_SPU)
		m_sectors.reserve(4);	// align array on 16 byte boundary
		m_spuNumSectors = 0;
		m_spuBytesUsedInLastSector = HK_AGENT3_SECTOR_SIZE;

		m_ppuBytesUsedInLastSector = HK_AGENT3_SECTOR_SIZE;
#else
		m_bytesUsedInLastSector = HK_AGENT3_SECTOR_SIZE;
#endif
		m_nnTrackType = nnTrackType;
	}

	int getSectorSize( int sectorIndex ) const
	{
#if !defined(HK_PLATFORM_HAS_SPU)
		if ( sectorIndex+1 == m_sectors.getSize())
		{
			return m_bytesUsedInLastSector;
		}
#else
		if ( sectorIndex+1 == m_spuNumSectors)
		{
			return m_spuBytesUsedInLastSector;
		}

		if ( sectorIndex+1 == m_sectors.getSize())
		{
			return m_ppuBytesUsedInLastSector;
		}
#endif
		return HK_AGENT3_SECTOR_SIZE;
	}

		/// Get the size of the space allocated to each agent in tracks of the given type.
	HK_FORCE_INLINE static unsigned int getAgentSize( hkpAgentNnTrackType nnTrackType )
	{
		// Works because HK_AGENT3_MIDPHASE_AGENT_SIZE * 2 == HK_AGENT3_NARROWPHASE_AGENT_SIZE
		
		return nnTrackType * HK_AGENT3_MIDPHASE_AGENT_SIZE;
	}

		/// Get the size of the space allocated to each agent the track.
	HK_FORCE_INLINE unsigned int getAgentSize() const
	{
		return getAgentSize( m_nnTrackType );
	}

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkpAgentNnTrack );

#ifdef HK_PLATFORM_HAS_SPU
	hkUint16	m_spuNumSectors;
	hkUint16    m_spuBytesUsedInLastSector;
	hkUint16    m_ppuBytesUsedInLastSector;
	HK_FORCE_INLINE int getNumPpuSectors() const { return m_sectors.getSize() - m_spuNumSectors; }
#else
	hkUint16	m_bytesUsedInLastSector;
#endif

		/// Does the track contain midphase or narrowphase agent entries?
	hkEnum<hkpAgentNnTrackType, hkUint8> m_nnTrackType;
	hkUint8     m_padding;

#if defined(HK_PLATFORM_HAS_SPU)
		// spu sectors come first, than some bytes of padding, than ppu sectors
	hkArray<hkpAgentNnSector*> m_sectors; // constructor sets size to 4 so that array will be 16byte-aligned
#else
	hkInplaceArray<hkpAgentNnSector*,1> m_sectors; 
#endif
};





#endif // HK_COLLIDE2_COLLISION_AGENT_TRACK_H

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
