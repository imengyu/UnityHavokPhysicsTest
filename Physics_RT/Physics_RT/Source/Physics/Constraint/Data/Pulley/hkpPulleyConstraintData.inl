/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

////////////////////////////////////////////////////////////////////////

/// \param pivotA			bodyA's pivot point, specified in world space.
/// \param pivotB			bodyB's pivot point, specified in world space.
inline void hkpPulleyConstraintData::setInWorldSpace(const hkTransform& bodyATransform,
													 const hkTransform& bodyBTransform,
													 const hkVector4& pivotAW,
													 const hkVector4& pivotBW,
													 const hkVector4& pulleyPivotAW,
													 const hkVector4& pulleyPivotBW,
													 hkReal leverageOnBodyB )
{
	m_atoms.m_translations.m_translationA._setTransformedInversePos(bodyATransform,pivotAW);
	m_atoms.m_translations.m_translationB._setTransformedInversePos(bodyBTransform,pivotBW);
	m_atoms.m_pulley.m_fixedPivotAinWorld = pulleyPivotAW;
	m_atoms.m_pulley.m_fixedPivotBinWorld = pulleyPivotBW;

	hkVector4 sepDist;
	sepDist.setSub( pivotAW, pulleyPivotAW );
	sepDist.length<3>().store<1>( &m_atoms.m_pulley.m_ropeLength );
	sepDist.setSub( pivotBW, pulleyPivotBW );
	m_atoms.m_pulley.m_ropeLength += sepDist.length<3>().getReal() * leverageOnBodyB;

	m_atoms.m_pulley.m_leverageOnBodyB = leverageOnBodyB;


}

//////////////////////////////////////////////////////////////////////////

/// \param pivotA			bodyA's pivot point, specified in bodyA's space.
/// \param pivotB			bodyB's pivot point, specified in bodyB's space.
inline void hkpPulleyConstraintData::setInBodySpace( const hkTransform& bodyATransform,
													 const hkTransform& bodyBTransform,
													 const hkVector4& pivotA,
													 const hkVector4& pivotB,
													 const hkVector4& pulleyPivotAW,
													 const hkVector4& pulleyPivotBW,
													 hkReal leverageOnBodyB )

{
	m_atoms.m_translations.m_translationA = pivotA;
	m_atoms.m_translations.m_translationB = pivotB;
	m_atoms.m_pulley.m_fixedPivotAinWorld = pulleyPivotAW;
	m_atoms.m_pulley.m_fixedPivotBinWorld = pulleyPivotBW;

	hkVector4 pivotAW, pivotBW;
	pivotAW._setTransformedPos(bodyATransform,pivotA);
	pivotBW._setTransformedPos(bodyBTransform,pivotB);

	hkVector4 sepDist;
	sepDist.setSub( pivotAW, pulleyPivotAW );
	sepDist.length<3>().store<1>( &m_atoms.m_pulley.m_ropeLength );
	sepDist.setSub( pivotBW, pulleyPivotBW );
	m_atoms.m_pulley.m_ropeLength += sepDist.length<3>().getReal() * leverageOnBodyB;

	m_atoms.m_pulley.m_leverageOnBodyB = leverageOnBodyB;
}


hkReal hkpPulleyConstraintData::getRopeLength(hkReal length)
{
	return m_atoms.m_pulley.m_ropeLength;
}

hkReal hkpPulleyConstraintData::getLeverageOnBodyB()
{
	return m_atoms.m_pulley.m_leverageOnBodyB;
}

void hkpPulleyConstraintData::setRopeLength(hkReal length)
{
	m_atoms.m_pulley.m_ropeLength = length;
}

void hkpPulleyConstraintData::setLeverageOnBodyB(hkReal leverageOnBodyB)
{
	m_atoms.m_pulley.m_leverageOnBodyB = leverageOnBodyB;
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
