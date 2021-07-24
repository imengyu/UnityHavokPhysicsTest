/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SCENEDATA_HKX_ANIMATED_FLOAT_H
#define HK_SCENEDATA_HKX_ANIMATED_FLOAT_H

#include <Common/SceneData/Attributes/hkxAttribute.h>

extern const hkClass hkxAnimatedFloatClass;

	/// An hkxAnimatedFloat stores the values associated with an hkxAttribute of type float.
class hkxAnimatedFloat : public hkReferencedObject
{
	//+vtable(true)
	//+version(1)
	public: 
	
	HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA );
	HK_DECLARE_REFLECTION();

	hkxAnimatedFloat() {}
	hkxAnimatedFloat(hkFinishLoadedObjectFlag f) : hkReferencedObject(f), m_floats(f) {}

	virtual const hkClass* getClassType() const HK_OVERRIDE { return &hkxAnimatedFloatClass;	}

		/// The array of sampled floats. Array can be of length 1 for not animated,
		/// or one per frame so assumes that the value is then fully sampled.
	hkArray<hkFloat32> m_floats;
	
		/// Usage hint so that automatic transform filters can attempt
		/// to change the value in a sensible way.
	hkEnum< hkxAttribute::Hint,hkUint8> m_hint;
};

#endif // HK_SCENEDATA_HKX_ANIMATED_FLOAT_H

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
