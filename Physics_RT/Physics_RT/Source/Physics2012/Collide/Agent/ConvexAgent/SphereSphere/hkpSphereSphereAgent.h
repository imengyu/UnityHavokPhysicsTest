/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_SPHERE_SPHERE_AGENT_H
#define HK_COLLIDE2_SPHERE_SPHERE_AGENT_H

#include <Physics2012/Collide/Agent/Util/LinearCast/hkpIterativeLinearCastAgent.h>
#include <Physics2012/Collide/Dispatch/hkpCollisionDispatcher.h>

class hkpCollisionDispatcher;

	/// This agent handles collisions between two hkpSphereShape s
class hkpSphereSphereAgent : public hkpIterativeLinearCastAgent
{
    public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
#if !defined(HK_PLATFORM_SPU)
		static void HK_CALL initAgentFunc(hkpCollisionDispatcher::AgentFuncs& f);
#else
		static void HK_CALL initAgentFunc(hkpSpuCollisionQueryDispatcher::AgentFuncs& f);
#endif

			/// Registers this agent with the collision dispatcher.
        static void HK_CALL registerAgent(hkpCollisionDispatcher* dispatcher);

			/// Registers this agent with the collision dispatcher. Does not register bridge agent.
        static void HK_CALL registerAgent2(hkpCollisionDispatcher* dispatcher);

			// hkpCollisionAgent interface implementation.
        virtual void processCollision(const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpProcessCollisionInput& input, hkpProcessCollisionOutput& result);

			// hkpCollisionAgent interface implementation.
		virtual void getClosestPoints( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdPointCollector& pointDetails); 

			// hkpCollisionAgent interface implementation.
		static void HK_CALL staticGetClosestPoints( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, class hkpCdPointCollector& collector  );

			// hkpCollisionAgent interface implementation.
		virtual void getPenetrations( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdBodyPairCollector& collector );

			// hkpCollisionAgent interface implementation.
		static void  HK_CALL staticGetPenetrations( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdBodyPairCollector& collector );

			// hkpCollisionAgent interface implementation.
		virtual void cleanup(hkCollisionConstraintOwner& info);

	private:
		
		/// Constructor, called by the agent creation function.
		inline hkpSphereSphereAgent(hkpContactMgr* mgr);

		static HK_FORCE_INLINE hkBool getClosestPoint( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkContactPoint& contact );

	protected:
        /// Agent creation function used by the hkpCollisionDispatcher.
		static hkpCollisionAgent* HK_CALL createSphereSphereAgent(	const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr);

	protected:
		hkContactPointId m_contactPointId;
};

#endif // HK_COLLIDE2_SPHERE_SPHERE_AGENT_H

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
