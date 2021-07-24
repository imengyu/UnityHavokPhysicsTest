/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_MOPP_BV_TREE_STREAM_AGENT_H
#define HK_COLLIDE2_MOPP_BV_TREE_STREAM_AGENT_H

#include <Physics2012/Collide/Agent/CompoundAgent/BvTreeStream/hkpBvTreeStreamAgent.h>

class hkpCollisionDispatcher;


	/// This agent deals with collisions between hkMoppShapes and other shapes.
	/// This agent only differs in two points from its parent hkpBvTreeAgent:
	///  - it implements a specialized staticLinearCast, which is doing an optimized
	///    static linear cast in MOPPs.
	///  - When two MOPPs collide, it checks for each MOPPs size and collides all the
	///    triangles of the smaller MOPP against the bigger MOPP.
class hkpMoppBvTreeStreamAgent 
{
	public:
			/// Registers this agent with the collision dispatcher.
		static void HK_CALL registerAgent(hkpCollisionDispatcher* dispatcher);
};

#endif // HK_COLLIDE2_MOPP_BV_TREE_STREAM_AGENT_H

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
