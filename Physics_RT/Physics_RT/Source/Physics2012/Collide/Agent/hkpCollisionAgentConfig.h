/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_COLLISION_AGENT_CONFIG
#define HK_COLLIDE2_COLLISION_AGENT_CONFIG

/// This structure combines several configuration variables for hkpCollisionAgent.
/// Note:
/// -  currently this structure is only used by processCollision() and linearCast()
/// -  ***************** from hkpWorld
struct hkpCollisionAgentConfig
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_AGENT, hkpCollisionAgentConfig);
	
	HK_ALIGN16( hkReal m_iterativeLinearCastEarlyOutDistance );
	int m_iterativeLinearCastMaxIterations;

	inline hkpCollisionAgentConfig();
};

#include <Physics2012/Collide/Agent/hkpCollisionAgentConfig.inl>


#endif // HK_COLLIDE2_COLLISION_AGENT_CONFIG

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
