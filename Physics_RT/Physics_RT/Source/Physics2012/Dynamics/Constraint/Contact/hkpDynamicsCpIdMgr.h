/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_DYNAMICS_CP_ID_MGR_H
#define HKP_DYNAMICS_CP_ID_MGR_H


/// Class to manage the link between external contact points and hkDynamicsContactPoints.
class hkpDynamicsCpIdMgr
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpDynamicsCpIdMgr );

		enum { HK_MAX_IDS_PER_OBJECT = 8 };
		enum { FREE_VALUE = 0xff };
		typedef hkUchar hkpValueType;

	public:

		inline  hkpDynamicsCpIdMgr();
		inline ~hkpDynamicsCpIdMgr() {}

			/// Returns an index (==contactPointId) into m_values[] and sets m_values[id] = value
		inline int newId( int value );

			/// Finds the index (==contactPointId) of an value
		inline int indexOf( int value ) const;

			/// Flags the id to be free.
		inline void freeId( int id );

			/// Decrement all values which are greater then relIndex.
		inline void decrementValuesGreater( int relIndex );

		inline void getAllUsedIds( hkArray<hkContactPointId>& ids ) const;

		inline hkpValueType getValueAt(int id) const;

	public:

		hkInplaceArray<hkpValueType,HK_MAX_IDS_PER_OBJECT>	m_values;

};

#include <Physics2012/Dynamics/Constraint/Contact/hkpDynamicsCpIdMgr.inl>


#endif // HKP_DYNAMICS_CP_ID_MGR_H

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
