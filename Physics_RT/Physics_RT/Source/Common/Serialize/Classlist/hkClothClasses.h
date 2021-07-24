/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//HK_REFLECTION_PARSER_EXCLUDE_FILE

#include <Cloth/Cloth/Classes/hclClothClasses.h>	

// define HK_FEATURE_REFLECTION_CLOTH_SETUP if you are going to use Cloth Setup serialized objects rather than runtime objects
#if defined(HK_FEATURE_REFLECTION_CLOTH_SETUP)
	#if !defined(HK_EXCLUDE_LIBRARY_hclSetup)
		#include <Cloth/Setup/Classes/hclSetupClasses.h>	
	#endif
#endif

#ifdef HK_FEATURE_REFLECTION_ANIMATION
#	ifdef HK_FEATURE_REFLECTION_CLOTH_SETUP_ANIMATION 
#		if !defined(HK_EXCLUDE_LIBRARY_hclAnimationBridge)
#			include <Cloth/AnimationBridge/Classes/hclAnimationBridgeClasses.h>	
#		endif
#	endif
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
