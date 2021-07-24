/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Phantom/hkpShapePhantom.h>

inline void hkpCpuCharacterProxyUtil::linearCastWorldCast( const hkpShapePhantom* phantom
															   , const hkpLinearCastInput& input
															   , hkpCollidable* collidable
															   , hkpAllCdPointCollector& castCollector
															   , hkpAllCdPointCollector* startCollector
															   )
{
	phantom->getWorld()->linearCast( collidable, input, castCollector, startCollector );
}

inline void hkpCpuCharacterProxyUtil::linearCastSetPositionAndCast( hkpShapePhantom* phantom
																   , const hkpLinearCastInput& input
																   , hkpAllCdPointCollector& castCollector
																   , hkpAllCdPointCollector* startCollector
																   , const hkVector4& position
																   )
{
	phantom->setPositionAndLinearCast( position, input, castCollector, startCollector );
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
