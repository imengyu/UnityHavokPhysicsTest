/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_BVTREE_AGENT3_H
#define HK_BVTREE_AGENT3_H

#include <Physics2012/Collide/Agent3/hkpAgent3.h>
#include <Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>

class hkpShapeKeyTrackWriter;
class hkpShapeKeyTrackConsumer;

namespace hkBvTreeAgent3 
{
	//hkpAgentData*	HK_CALL create			( const hkpAgent3Input& input, hkpAgentEntry* entry, hkpAgentData* freeMemory ); reusing hkListAgent3::create

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

		// Get *unsorted* keys for shapes within the provided AABB. Returns -1 if the cache is still valid, the number of hits otherwise
	int				HK_CALL calcAabbAndQueryTree( const hkpCdBody& bodyA,	const hkpCdBody& bodyB, const hkTransform& bTa,
													const hkVector4& linearTimInfo, const hkpProcessCollisionInput& input,
													hkAabb* cachedAabb, hkpShapeKey* hitListOut, int hitListCapacity );

	HK_FORCE_INLINE const HK_SHAPE_CONTAINER* HK_CALL getShapeContainerFrom(const hkpCdBody* body, hkpShapeBuffer& buffer);

	const hkpShapeCollection* HK_CALL getShapeCollectionIfBvTreeSupportsAabbQueries(const hkpCdBody* body, hkpShapeBuffer& buffer);
}


const HK_SHAPE_CONTAINER* HK_CALL hkBvTreeAgent3::getShapeContainerFrom(const hkpCdBody* body, hkpShapeBuffer& buffer)
{
#if !defined (HK_PLATFORM_SPU)
	const hkpBvTreeShape* bvt = static_cast<const hkpBvTreeShape*>( body->getShape() );
	return bvt->getContainer();
#else
	return hkpBvTreeShape::getContainerImpl( body->getShape(), buffer );
#endif
}
#endif // HK_BVTREE_AGENT3_H

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
