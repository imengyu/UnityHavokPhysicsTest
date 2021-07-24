/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// WARNING: THIS FILE IS GENERATED. EDITS WILL BE LOST.
// Generated from 'Behavior/Behavior/Generator/Blender/Layer/hkbLayerGenerator.h'

#ifndef HKB_LAYER_GENERATOR_INTERNAL_STATE_H
#define HKB_LAYER_GENERATOR_INTERNAL_STATE_H

#include <Behavior/Behavior/Generator/Blender/Layer/hkbLayerGenerator.h>

class hkbLayerGeneratorInternalState : public hkReferencedObject
{
	//+vtable(1)
	//+version(0)
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BEHAVIOR );

		hkbLayerGeneratorInternalState() {}
		hkbLayerGeneratorInternalState( hkFinishLoadedObjectFlag flag )
			: hkReferencedObject(flag)
			, m_layerInternalStates(flag)
		{
		}

		int m_numActiveLayers;
		hkArray<hkbLayerGenerator::LayerInternalState> m_layerInternalStates;
		hkBool m_initSync;
};

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