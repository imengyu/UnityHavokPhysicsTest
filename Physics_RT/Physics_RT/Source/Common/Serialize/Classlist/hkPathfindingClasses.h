/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//HK_REFLECTION_PARSER_EXCLUDE_FILE

#include <Ai/Pathfinding/Classes/hkaiPathfindingClasses.h>	
#include <Ai/Internal/Classes/hkaiInternalClasses.h> 
#include <Ai/SpatialAnalysis/Classes/hkaiSpatialAnalysisClasses.h> 

#if !defined(HK_EXCLUDE_LIBRARY_hkaiVisualize)
#include <Ai/Visualize/Classes/hkaiVisualizeClasses.h> 
#endif

#if defined(HK_FEATURE_REFLECTION_PHYSICS_2012) &&  !defined(HK_EXCLUDE_LIBRARY_hkaiPhysics2012Bridge)
#include <Ai/Physics2012Bridge/Classes/hkaiPhysics2012BridgeClasses.h>	
#endif

#if defined(HK_FEATURE_REFLECTION_PHYSICS) &&  !defined(HK_EXCLUDE_LIBRARY_hkaiPhysicsBridge)
#include <Ai/PhysicsBridge/Classes/hkaiPhysicsBridgeClasses.h>	
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
