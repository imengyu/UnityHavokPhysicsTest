/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
inline hkpVelocityConstraintMotor::hkpVelocityConstraintMotor()
: hkpLimitedForceConstraintMotor()
{
	m_type = TYPE_VELOCITY;
	setMaxForce(hkReal(1e6f));
	m_velocityTarget = hkReal(1);
	m_tau = hkReal(0.8f);
	m_useVelocityTargetFromConstraintTargets = false;
}

// Construct a motor with the given properties.
inline hkpVelocityConstraintMotor::hkpVelocityConstraintMotor( hkReal velocityTarget, hkReal maxForce )
: hkpLimitedForceConstraintMotor(), m_velocityTarget(velocityTarget)
{
	m_type = TYPE_VELOCITY;
	setMaxForce(maxForce);
	m_tau = hkReal(0.8f);
	m_useVelocityTargetFromConstraintTargets = false;
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
