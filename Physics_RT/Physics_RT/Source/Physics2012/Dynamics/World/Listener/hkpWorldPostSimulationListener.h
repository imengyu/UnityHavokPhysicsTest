/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_WORLD_POST_SIMULATION_LISTENER_H
#define HK_DYNAMICS2_WORLD_POST_SIMULATION_LISTENER_H

class hkpWorld;
class hkpEntity;
class hkStepInfo;

	/// Derive from this class to receive callbacks after all entities have been simulated.
class hkpWorldPostSimulationListener
{
	//+hk.MemoryTracker(ignore=True)
	public:
		virtual ~hkpWorldPostSimulationListener() {}

			/// Called at the end of the hkpWorld::simulate call.
		virtual void postSimulationCallback( hkpWorld* world ) = 0;

			/// Called when an inactive/fixed entity is moved in the hkpWorld.
		virtual void inactiveEntityMovedCallback( hkpEntity* entity ) {}

};


#endif // HK_DYNAMICS2_WORLD_POST_SIMULATION_LISTENER_H

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
