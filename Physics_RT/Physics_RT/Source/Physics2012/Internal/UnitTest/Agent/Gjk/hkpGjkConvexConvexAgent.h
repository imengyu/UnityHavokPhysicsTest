/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_CONVEX_CONVEX_AGENT_H
#define HK_COLLIDE2_CONVEX_CONVEX_AGENT_H

#include <Physics2012/Collide/Agent/Util/LinearCast/hkpIterativeLinearCastAgent.h>
#include <Physics2012/Internal/Collide/Gjk/hkpGjkCache.h>
#include <Physics2012/Collide/Agent/ConvexAgent/Gjk/hkpClosestPointManifold.h>

class hkpCollisionDispatcher;


	/// A hkpGjkConvexConvexAgent handles collision detection between pairs of hkConvexShapes.
	/// Read the hkpGskConvexConvexAgent documentation for further details
class hkpGjkConvexConvexAgent : public hkpIterativeLinearCastAgent
{
	public:
			/// Registers the agent with the collision dispatcher.
		static void HK_CALL registerAgent(hkpCollisionDispatcher* dispatcher);

			/// hkpCollisionAgent interface implementation.
		virtual void processCollision(const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpProcessCollisionInput& input, hkpProcessCollisionOutput& result);
	
			// hkpCollisionAgent interface implementation.
		virtual void getClosestPoints( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdPointCollector& pointDetails); 
		
			// hkpCollisionAgent interface implementation.
		static void HK_CALL staticGetClosestPoints( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdPointCollector& pointDetails); 
		
			// hkpCollisionAgent interface implementation.
		virtual void getPenetrations( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdBodyPairCollector& collector );

			// hkpCollisionAgent interface implementation.
		static void HK_CALL staticGetPenetrations( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdBodyPairCollector& collector );

			// hkpCollisionAgent interface implementation.
		virtual void cleanup( hkCollisionConstraintOwner& constraintOwner );

	public:
			/// Constructor, called by the createConvexConvexAgent() function.
		hkpGjkConvexConvexAgent(hkpContactMgr* mgr) : hkpIterativeLinearCastAgent(mgr) { m_oldNormal.setZero(); m_oldNormal(3) = hkReal(-1); }

			/// Destructor, called by cleanup().
		~hkpGjkConvexConvexAgent(){}

			/// Agent creation function used by the hkpCollisionDispatcher.
		static hkpCollisionAgent* HK_CALL createConvexConvexAgent(	const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* contactMgr);


	protected:

		friend class hkpConvexConvexWelderAgent;

		hkBool getClosestPoint( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpExtendedGskOut& output);

		static HK_FORCE_INLINE hkBool staticGetClosestPoint(  const hkpCdBody& bodyA,	const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpGjkCache& cache, struct hkpExtendedGskOut& output);


	protected:
		hkVector4	m_oldNormal;

		hkpGjkCache m_cache;
		hkpClosestPointManifold m_bridgeManifold;

};

#endif // HK_COLLIDE2_CONVEX_CONVEX_AGENT_H

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
