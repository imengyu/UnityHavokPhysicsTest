/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_DEFAULT_CLASS_NAME_REGISTRY_H
#define HK_DEFAULT_CLASS_NAME_REGISTRY_H

#include <Common/Base/Object/hkSingleton.h>
#include <Common/Base/Reflection/Registry/hkDynamicClassNameRegistry.h>
#include <Common/Base/Config/hkConfigVersion.h>

	/// Class name registry singleton. This singleton provides access to all registered runtime classes.
	/// The registry name is HAVOK_SDK_VERSION_STRING.
class hkDefaultClassNameRegistry : public hkDynamicClassNameRegistry, public hkSingleton<hkDefaultClassNameRegistry>
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		hkDefaultClassNameRegistry() : hkDynamicClassNameRegistry(HAVOK_SDK_VERSION_STRING) {}
};

#if defined(HK_COMPILER_ARMCC) || defined(HK_COMPILER_GHS) //have to specialize before use so that generalized one not auto gen-d
HK_SINGLETON_SPECIALIZATION_DECL(hkDefaultClassNameRegistry);
#endif

#endif // HK_DEFAULT_CLASS_NAME_REGISTRY_H

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
