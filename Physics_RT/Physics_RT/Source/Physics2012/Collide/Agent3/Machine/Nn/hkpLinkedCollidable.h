/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_LINKED_COLLIDABLE_H
#define HK_COLLIDE2_LINKED_COLLIDABLE_H

#include <Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>
#include <Physics2012/Collide/Agent/Collidable/hkpCollidable.h>

extern const class hkClass hkpLinkedCollidableClass;

struct hkpAgentNnEntry;

/// A hkpLinkedCollidable is a hkpCollidable which is referenced by collision agents. If the agent moves
/// it can update all links pointing to it
#if !defined(HK_PLATFORM_SPU)
class hkpLinkedCollidable: public hkpCollidable
#else
class hkpLinkedCollidable: public hkCollidablePpu
#endif
{

#if !defined(HK_PLATFORM_SPU)

	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CDINFO, hkpLinkedCollidable );
		HK_DECLARE_REFLECTION();

			/// Creates a new hkpLinkedCollidable.
			/// Note: this constructor sets the owner to be HK_NULL, call setOwner to specify the owner and type
		inline hkpLinkedCollidable( const hkpShape* shape, const hkMotionState* ms, int type = 0);

		inline ~hkpLinkedCollidable();

			// Used by the serialization to discover vtables.
		inline hkpLinkedCollidable( class hkFinishLoadedObjectFlag flag ) : hkpCollidable(flag) {}

#endif

	public:

		/// A list of links to all persistent agents referencing this object
		struct CollisionEntry
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkpLinkedCollidable::CollisionEntry );

			hkpAgentNnEntry* m_agentEntry;
			hkpLinkedCollidable*	m_partner;
		};

#if ! defined (HK_PLATFORM_SPU)
			/// Returns a deterministically ordered copy of the collision entries
		void getCollisionEntriesSorted(hkArray<struct CollisionEntry>& entries) const ;

			/// returns the array of collision entries where we know that they are deterministically ordered (e.g., we know its a non fixed object)
		const hkArray<struct CollisionEntry>& getCollisionEntriesDeterministicUnchecked() const;

		hkArray<struct CollisionEntry>& getCollisionEntriesDeterministicUnchecked();

		hkArray<struct CollisionEntry>& getCollisionEntriesNonDeterministic(){ return m_collisionEntries; }

		const hkArray<struct CollisionEntry>& getCollisionEntriesNonDeterministic()  const { return m_collisionEntries; }

			/// ###ACCESS_CHECKS###( [hkpGetRigidBody(this)->getWorld(),HK_ACCESS_RW] );
		void sortEntries();
#endif


	protected:
		hkArray<struct CollisionEntry> m_collisionEntries; //+nosave

};

#if !defined(HK_PLATFORM_SPU)
#	include <Physics2012/Collide/Agent3/Machine/Nn/hkpLinkedCollidable.inl>
#endif

#endif // HK_COLLIDE2_LINKED_COLLIDABLE_H

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
