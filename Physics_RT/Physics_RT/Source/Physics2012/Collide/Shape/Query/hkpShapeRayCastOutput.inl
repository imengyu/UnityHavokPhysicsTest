/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

void hkpShapeRayCastOutput::_reset()
{
	m_shapeKeyIndex = 0;
	m_shapeKeys[0] = HK_INVALID_SHAPE_KEY;
}

void hkpShapeRayCastOutput::reset()
{
	hkpShapeRayCastCollectorOutput::reset();
	_reset();
}


hkpShapeRayCastOutput::hkpShapeRayCastOutput()
{
	_reset();
}

void hkpShapeRayCastOutput::changeLevel(int delta)
{
	HK_ASSERT(0x7ee30341, unsigned(m_shapeKeyIndex+delta) < MAX_HIERARCHY_DEPTH );
	m_shapeKeyIndex += delta;
}

inline void hkpShapeRayCastOutput::setKey(hkpShapeKey key)
{
	m_shapeKeys[m_shapeKeyIndex] = key;
}

inline int hkpShapeRayCastOutput::getLevel() const
{
	return m_shapeKeyIndex;
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
