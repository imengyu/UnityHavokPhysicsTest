/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_COLLECTION_BVTREE_AGENT3_H
#define HK_COLLIDE2_COLLECTION_BVTREE_AGENT3_H

#include <Physics2012/Collide/Agent3/hkpAgent3.h>
#include <Physics2012/Collide/Dispatch/hkpCollisionDispatcher.h>

class hkpCollisionDispatcher;
class hkpShapeKeyTrackWriter;
class hkpShapeKeyTrackConsumer;

#if !defined(HK_PLATFORM_SPU)
#	define HK_MAX_NUM_HITS_PER_AABB_QUERY_USED HK_MAX_NUM_HITS_PER_AABB_QUERY
#else
#	define HK_MAX_NUM_HITS_PER_AABB_QUERY_USED hkpListShape::MAX_CHILDREN_FOR_SPU_MIDPHASE
#endif

/// a streamed agent implementing list collisions.
/// This agent is continuous
namespace hkpCollectionCollectionAgent3
{

	//hkpAgentData*	HK_CALL create			( const hkpAgent3Input& input, hkpAgentEntry* entry, hkpAgentData* freeMemory );

		/// Returns the number of shape keys found or a negative integer on error.
	int				HK_CALL process_gatherShapeKeys ( const hkpAgent3ProcessInput& input, const HK_SHAPE_CONTAINER* shapeContainerA, const HK_SHAPE_CONTAINER* shapeContainerB, hkpShapeKeyPair* shapeKeyPairs );

	hkpAgentData*	HK_CALL process			( const hkpAgent3ProcessInput& input, hkpAgentEntry* entry, hkpAgentData* agentData, hkVector4* separatingNormal, hkpProcessCollisionOutput& output );

	//void			HK_CALL destroy			( hkpAgentEntry* entry, hkpAgentData* agentData, hkpContactMgr* mgr, hkCollisionConstraintOwner& constraintOwner, hkpCollisionDispatcher* dispatcher );

	void			HK_CALL registerAgent3	( hkpCollisionDispatcher* dispatcher );

	void			HK_CALL HK_INIT_FUNCTION( initAgentFunc )( hkpCollisionDispatcher::Agent3Funcs& f );
	

	//
	// Other functions needed for shape-collection agents
	//

	void			HK_CALL updateFilter( hkpAgentEntry* entry, hkpAgentData* agentData, const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr, hkCollisionConstraintOwner& constraintOwner );

	void			HK_CALL invalidateTim( hkpAgentEntry* entry, hkpAgentData* agentData, const hkpCollisionInput& input );

	void			HK_CALL warpTime( hkpAgentEntry* entry, hkpAgentData* agentData, hkTime oldTime, hkTime newTime, const hkpCollisionInput& input );

	extern bool g_agentRegistered;
}

#endif // HK_COLLIDE2_COLLECTION_BVTREE_AGENT3_H

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
