/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

inline hkSphere::hkSphere()
{
}

inline hkSphere::hkSphere(const hkVector4& pt, hkReal radius)
{
	m_pos = pt;
	m_pos(3) = radius;
}

inline hkSphere::hkSphere(hkVector4Parameter pt, hkSimdRealParameter radius)
{
	m_pos.setXYZ_W(pt,radius);
}

inline hkReal hkSphere::getRadius() const
{
	return m_pos(3);
}

inline hkSimdReal hkSphere::getRadiusSimdReal() const
{
	return m_pos.getW();
}

inline void hkSphere::setRadius(hkReal newRadius)
{
	m_pos(3) = newRadius;
}

inline void hkSphere::setRadius(hkSimdRealParameter newRadius)
{
	m_pos.setW(newRadius);
}

inline const hkVector4& hkSphere::getPosition() const
{
	return m_pos;
}

inline const hkVector4& hkSphere::getPositionAndRadius() const
{
	return m_pos;
}

inline hkVector4& hkSphere::getPositionAndRadius()
{
	return m_pos;
}

inline void hkSphere::setPosition(const hkVector4& newPos)
{
	m_pos.setXYZ( newPos ); // do not override the z component
}

inline void hkSphere::setPositionAndRadius( const hkVector4& newPos )
{
	m_pos = newPos;
}

inline void hkSphere::setPositionAndRadius( hkVector4Parameter newPos, hkSimdRealParameter newRadius )
{
	m_pos.setXYZ_W(newPos,newRadius);
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
