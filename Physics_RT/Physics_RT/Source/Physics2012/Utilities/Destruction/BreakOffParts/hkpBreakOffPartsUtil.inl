/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


void hkpBreakOffPartsUtil::LimitContactImpulseUtil::setMaxImpulseForShapeKey ( const hkpShapeKey key, hkUint8 max_impulse )
{
	HK_ASSERT2(0xdbc48575, key != HK_INVALID_SHAPE_KEY, "Cannot associate an impulse with an invalid shape key");
	m_shapeKeyToMaxImpulse.insert( key, max_impulse);
}

hkUint8 hkpBreakOffPartsUtil::LimitContactImpulseUtil::getMaxImpulseForKey ( const hkpShapeKey key ) const
{
	HK_ASSERT2(0xdbc48575, key != HK_INVALID_SHAPE_KEY, "Cannot associate an impulse with an invalid shape key");
	return m_shapeKeyToMaxImpulse.getWithDefault( key, 0 );
}

void hkpBreakOffPartsUtil::LimitContactImpulseUtil::removeKey ( const hkpShapeKey key )
{
	HK_ASSERT2(0xdbc48575, key != HK_INVALID_SHAPE_KEY, "Cannot associate an impulse with an invalid shape key");
	m_shapeKeyToMaxImpulse.remove(key);
}

hkpBreakOffPartsUtil::LimitContactImpulseUtilDefault::LimitContactImpulseUtilDefault( hkpBreakOffPartsUtil* breakUtil, hkpEntity* entity ) 
: LimitContactImpulseUtil( breakUtil, entity )
{
	/// Set the flag so default function is used on SPU.
	hkUlong utilPtr = hkUlong( entity->m_limitContactImpulseUtilAndFlag ) | 1;
	entity->m_limitContactImpulseUtilAndFlag = ( LimitContactImpulseUtil* ) utilPtr;
}

hkpBreakOffPartsUtil::LimitContactImpulseUtil* HK_CALL hkpBreakOffPartsUtil::getLimitContactImpulseUtilPtr( const hkpEntity* entity )
{
	const hkUlong utilAndFlag = hkUlong( entity->m_limitContactImpulseUtilAndFlag );
	hkUlong utilPtr = utilAndFlag & ( hkUlong( -1 ) ^ 1 );
#if defined(HK_PLATFORM_SPU)
	// On SPU we return null if the flag isn't set.
	utilPtr *= ( utilAndFlag & 1 );
#endif
	return (LimitContactImpulseUtil*) utilPtr;
}

#if !defined(HK_PLATFORM_SPU)

hkUFloat8 hkpBreakOffPartsUtil::LimitContactImpulseUtil::getMaxImpulseForContactPoint( hkpShapeKey key, hkpRigidBody* other ) const
{
	hkUFloat8 maxImpulse; maxImpulse.m_value = 0;
	if ( key != HK_INVALID_SHAPE_KEY )
	{
		maxImpulse.m_value = getMaxImpulseForKey(key);
	}

	if ( !maxImpulse.m_value )
	{
		if ( ( m_maxImpulse.m_value == 0 ) || ( m_maxImpulse.m_value == hkUFloat8::MAX_VALUE-1 ) )
		{
			// piece is not flagged
			return maxImpulse;
		}
		maxImpulse = m_maxImpulse;
	}

	if ( other->m_damageMultiplier != 1.0f )
	{
		maxImpulse = hkFloat32(maxImpulse) / hkFloat32(other->m_damageMultiplier);
		maxImpulse.m_value = hkMath::max2( hkUchar(1), maxImpulse.m_value );
	}

	return maxImpulse;
}

#endif

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
