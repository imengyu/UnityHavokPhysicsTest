/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_AGENT3_BRIDGE_H
#define HK_COLLIDE2_AGENT3_BRIDGE_H

#include <Physics2012/Collide/Agent3/hkpAgent3.h>

class hkpCollisionDispatcher;
class hkpCollisionAgent;

namespace hkAgent3Bridge
{
		/// This agent3 links in the existing agents
	hkpAgentData* create  ( const hkpAgent3Input& input, hkpAgentEntry* entry, hkpAgentData* agentData );

	hkpAgentData* process ( const hkpAgent3ProcessInput& input, hkpAgentEntry* entry, hkpAgentData* agentData, hkVector4* separatingNormalOut, hkpProcessCollisionOutput& result);

	//void            sepNormalFunc( const hkpAgent3Input& input, hkpAgentData* agentData, hkVector4& separatingNormalOut );

	//hkpAgentData* cleanupFunc ( hkpAgentEntry* entry, hkpAgentData* agentData, hkpContactMgr* mgr );

	void HK_CALL    destroy ( hkpAgentEntry* entry, hkpAgentData* agentData, hkpContactMgr* mgr, hkCollisionConstraintOwner& constraintOwner, hkpCollisionDispatcher* dispatcher );

	void HK_CALL    updateFilter(hkpAgentEntry* entry, hkpAgentData* agentData, const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr, hkCollisionConstraintOwner& constraintOwner);

	void HK_CALL    invalidateTim(hkpAgentEntry* entry, hkpAgentData* agentData, const hkpCollisionInput& input);

	void HK_CALL    warpTime(hkpAgentEntry* entry, hkpAgentData* agentData, hkTime oldtime, hkTime newTime, const hkpCollisionInput& input);

	int	 HK_CALL	registerAgent3( hkpCollisionDispatcher* dispatcher );


	void HK_CALL removePoint( hkpAgentEntry* entry, hkpAgentData* agentData, hkContactPointId idToRemove );

	void HK_CALL commitPotential( hkpAgentEntry* entry, hkpAgentData* agentData, hkContactPointId newId );

	void HK_CALL createZombie( hkpAgentEntry* entry, hkpAgentData* agentData, hkContactPointId idTobecomeZombie );

	//
	// Helper functions
	//

	HK_FORCE_INLINE hkpCollisionAgent*& HK_CALL getChildAgent(hkpAgentData* agentData)
	{
		return *reinterpret_cast<hkpCollisionAgent**>(agentData);
	}

	HK_FORCE_INLINE hkpAgentData* HK_CALL getAgentDataEnd(hkpAgentData* agentData)
	{
		HK_ASSERT(0x44ff9925,  HK_NEXT_MULTIPLE_OF( HK_REAL_ALIGNMENT, sizeof(getChildAgent(agentData)) ) <= hkAgent3::MAX_NET_SIZE);
		return hkAddByteOffset( agentData, HK_NEXT_MULTIPLE_OF( HK_REAL_ALIGNMENT, sizeof(getChildAgent(agentData)) ) );
	}



}
#endif // HK_COLLIDE2_AGENT3_BRIDGE_H

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
