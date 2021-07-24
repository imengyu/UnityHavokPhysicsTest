/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_COLLECTION_AGENT3_H
#define HK_COLLIDE2_COLLECTION_AGENT3_H

#include <Physics2012/Collide/Agent3/hkpAgent3.h>
#include <Physics2012/Collide/Dispatch/hkpCollisionDispatcher.h>

class hkpShapeKeyTrackConsumer;
class hkpShapeKeyTrackWriter;

class hkpCollisionDispatcher;

#if !defined(HK_PLATFORM_SPU)
#	define HK_MAX_NUM_HITS_PER_AABB_QUERY_USED HK_MAX_NUM_HITS_PER_AABB_QUERY
#else
#	define HK_MAX_NUM_HITS_PER_AABB_QUERY_USED hkpListShape::MAX_CHILDREN_FOR_SPU_MIDPHASE
#endif

/// a streamed agent implementing collisions of simple shapes against collection shapes.
/// This agent is continuous.
/// This agent is based on hkpListAgent3 and hkpCollectionCollectionAgent3.
namespace hkpCollectionAgent3
{
	hkpAgentData*	HK_CALL process			( const hkpAgent3ProcessInput& input, hkpAgentEntry* entry, hkpAgentData* agentData, hkVector4* separatingNormal, hkpProcessCollisionOutput& output );

	void			HK_CALL registerAgent3	( hkpCollisionDispatcher* dispatcher );

	void			HK_CALL HK_INIT_FUNCTION( initAgentFunc )( hkpCollisionDispatcher::Agent3Funcs& f );
}

#endif // HK_COLLIDE2_COLLECTION_AGENT3_H

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
