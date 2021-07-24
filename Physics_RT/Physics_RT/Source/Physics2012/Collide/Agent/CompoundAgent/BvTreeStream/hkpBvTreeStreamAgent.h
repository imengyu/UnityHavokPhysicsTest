/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_BV_TREE_SHAPE_STREAM_AGENT_H
#define HK_COLLIDE2_BV_TREE_SHAPE_STREAM_AGENT_H

#include <Physics2012/Collide/Agent/CompoundAgent/BvTree/hkpBvTreeAgent.h>
#include <Physics2012/Collide/Agent3/Machine/1n/hkpAgent1nTrack.h>

	/// This agent deals with collisions between hkBvTreeShapes and other shapes. It traverses the bounding volume tree and dispatches
	/// collision agents for those child shapes that are found to be collision candidates with the other shape.
	/// The difference to hkpBvTreeAgent is that this agent uses a memory stream to store the agents.
	/// As a result, memory consumption and fragmentation is reduced significantly.
	/// However only hkPredGskAgent3 and hkCapsuleTriangleAgent3 are supporting this technology.
	/// This Agent as well handles welding of inner landscape edges.
class hkpBvTreeStreamAgent : public hkpCollisionAgent
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
			/// Registers this agent with the collision dispatcher.
		static void HK_CALL registerAgent(hkpCollisionDispatcher* dispatcher);

		static void HK_CALL registerConvexListAgent(hkpCollisionDispatcher* dispatcher);

		static void HK_CALL registerMultiRayAgent(hkpCollisionDispatcher* dispatcher);

			// hkpCollisionAgent interface implementation.
		virtual void processCollision(const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpProcessCollisionInput& input, hkpProcessCollisionOutput& result);

			// hkpCollisionAgent interface implementation.
		virtual void cleanup(hkCollisionConstraintOwner& info);


			// hkpCollisionAgent interface implementation.
		virtual void getPenetrations( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdBodyPairCollector& collector );


			// hkpCollisionAgent interface implementation.
		virtual void getClosestPoints( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdPointCollector& collector ) ;


			// hkpCollisionAgent interface implementation.
		virtual void linearCast( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpLinearCastCollisionInput& input, hkpCdPointCollector& collector, hkpCdPointCollector* startCollector );

			// hkpCollisionAgent interface implementation.
		virtual void updateShapeCollectionFilter( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkCollisionConstraintOwner& constraintOwner );

			// hkpCollisionAgent interface implementation.
		virtual void invalidateTim( const hkpCollisionInput& input);

			// hkpCollisionAgent interface implementation.
		virtual void warpTime(hkTime oldTime, hkTime newTime, const hkpCollisionInput& input);

	protected:
		hkResult prepareCollisionPartnersProcess( hkpAgent3ProcessInput& input, hkArray<hkpShapeKey>& hitList );

		/// Constructor, called by the agent creation function.
		hkpBvTreeStreamAgent( const hkpCdBody& bodyA, 	const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr );

		///Destructor, called by cleanup().
		~hkpBvTreeStreamAgent(){}

	public:
			/// Agent creation function used by the hkpCollisionDispatcher.
		static hkpCollisionAgent* HK_CALL createShapeBvAgent( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr );

		/// Agent creation function used by the hkpCollisionDispatcher.
		static hkpCollisionAgent* HK_CALL createBvTreeShapeAgent( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr );

			// Extra convex list dispatch functions
		static hkpCollisionAgent* HK_CALL dispatchBvTreeConvexList( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr );
		static hkpCollisionAgent* HK_CALL dispatchConvexListBvTree( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr );


	protected:
		hkpCollisionDispatcher* m_dispatcher;
		hkAabb	m_cachedAabb;
		hkpAgent1nTrack m_agentTrack;
};

#endif // HK_COLLIDE2_BV_TREE_SHAPE_STREAM_AGENT_H

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
