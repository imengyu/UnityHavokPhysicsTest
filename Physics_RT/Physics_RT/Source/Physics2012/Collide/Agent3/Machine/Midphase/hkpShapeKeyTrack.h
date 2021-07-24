/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SHAPE_KEY_TRACK_H
#define HK_SHAPE_KEY_TRACK_H

#include <Common/Base/Container/BlockList/hkBlockList.h>
#include <Physics2012/Collide/Shape/hkpShape.h>

#define HK_SIZE_OF_SHAPE_KEY_BLOCKS 512

class hkpShapeKeyTrack : public hkBlockList<hkpShapeKey, HK_SIZE_OF_SHAPE_KEY_BLOCKS>
{
	public:
		hkpShapeKeyTrack();
};

class hkpShapeKeyTrackWriter : public hkpShapeKeyTrack::BatchWriter
{
	public:
#if defined(HK_PLATFORM_SPU)
		HK_FORCE_INLINE hkpShapeKeyTrackWriter( int dmaGroup ) : hkpShapeKeyTrack::BatchWriter( dmaGroup ) {}
#endif

		void writeBatch( const hkpShapeKey* data, int numElements );
};

class hkpShapeKeyTrackConsumer : public hkpShapeKeyTrack::BatchConsumer
{
	public:
#if defined(HK_PLATFORM_SPU)
		HK_FORCE_INLINE hkpShapeKeyTrackConsumer( int dmaGroup ) : hkpShapeKeyTrack::BatchConsumer( dmaGroup ) {}
#endif

		hkpShapeKey* getShapeKeysInBuffer( int numShapeKeys );

		void freeShapeKeyBuffer( int numShapeKeys, hkpShapeKey* buffer );
};

#include <Physics2012/Collide/Agent3/Machine/Midphase/hkpShapeKeyTrack.inl>

#endif // HK_SHAPE_KEY_TRACK_H

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
