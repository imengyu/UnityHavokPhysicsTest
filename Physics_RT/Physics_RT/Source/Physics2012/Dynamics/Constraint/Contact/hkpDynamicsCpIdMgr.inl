/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#if defined(HK_PLATFORM_SPU)
#	include <Common/Base/Container/ArraySpu/hkArraySpu.h>
	extern hkArraySpu<hkpDynamicsCpIdMgr::hkpValueType>* g_cpIdMgrValuesArrayOnSpu;
#	define M_VALUE_GET_SIZE() g_cpIdMgrValuesArrayOnSpu->getSize()
#	define M_VALUE_GET_VALUE(IDX) ( g_cpIdMgrValuesArrayOnSpu->getValueAt(IDX) )
#	define M_VALUE_PUSH_BACK(VALUE) g_cpIdMgrValuesArrayOnSpu->pushBack(VALUE)
#else
#	define M_VALUE_GET_SIZE() m_values.getSize()
#	define M_VALUE_GET_VALUE(IDX) m_values[IDX]
#	define M_VALUE_PUSH_BACK(VALUE) m_values.pushBack(VALUE)
#endif


#if !defined(HK_PLATFORM_SPU)
inline hkpDynamicsCpIdMgr::hkpDynamicsCpIdMgr()
{
}
#endif

// Returns an index into m_values[] and sets m_values[id] = value.
inline int hkpDynamicsCpIdMgr::newId( int value )
{
	for ( int i = M_VALUE_GET_SIZE()-1; i >= 0 ; i-- )
	{
		if ( M_VALUE_GET_VALUE(i) == FREE_VALUE )
		{
			M_VALUE_GET_VALUE(i) = hkpValueType(value);
			return i;
		}
	}

	M_VALUE_PUSH_BACK( hkpValueType(value) );
	return M_VALUE_GET_SIZE()-1;
}

#if !defined(HK_PLATFORM_SPU)
	// Finds the index of an value.
inline int hkpDynamicsCpIdMgr::indexOf( int value ) const
{
	int i;
	for ( i = M_VALUE_GET_SIZE()-1; i >= 0 ; i-- )
	{
		if ( M_VALUE_GET_VALUE(i) == value )
		{
			return i;
		}
	}
	return i;
}
#endif

// Adds this->m_ids[ id ] to the freelist.
inline void hkpDynamicsCpIdMgr::freeId( int id )
{
	HK_ASSERT2(0x1fd4eea3, M_VALUE_GET_VALUE(id) != FREE_VALUE, "Too many contact points in a single collision pair. The system only handles 255 contact points or less between two objects.\
This is probably the result of creating bad collision geometries (i.e. meshes with many triangles in the same place) or having a too large collision tolerance. \
It can also result from not creating a hkpBvTreeShape about your mesh shape.");

	M_VALUE_GET_VALUE(id) = FREE_VALUE;
}
	
inline void hkpDynamicsCpIdMgr::decrementValuesGreater( int relIndex )
{
	for ( int i = M_VALUE_GET_SIZE()-1; i >= 0 ; i-- )
	{
		if ( M_VALUE_GET_VALUE(i) == FREE_VALUE )
		{
			continue;
		}
		if ( M_VALUE_GET_VALUE(i) > relIndex )
		{
			M_VALUE_GET_VALUE(i) --;
		}
	}
}

#if !defined(HK_PLATFORM_SPU)
inline void hkpDynamicsCpIdMgr::getAllUsedIds( hkArray<hkContactPointId>& ids ) const 
{
	for ( int i = 0; i < M_VALUE_GET_SIZE(); ++i )
	{
		if ( M_VALUE_GET_VALUE(i) != FREE_VALUE )
		{
			ids.pushBack(  hkContactPointId(i)  );
		}
	}
}
#endif

inline hkpDynamicsCpIdMgr::hkpValueType hkpDynamicsCpIdMgr::getValueAt(int id) const
{
	return M_VALUE_GET_VALUE(id);
}

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
