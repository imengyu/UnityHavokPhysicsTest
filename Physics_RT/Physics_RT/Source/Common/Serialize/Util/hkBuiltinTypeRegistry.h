/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_SERIALIZE_BUILTINTYPEREGISTRY_H
#define HK_SERIALIZE_BUILTINTYPEREGISTRY_H

class hkClass;
class hkTypeInfo;
class hkClassNameRegistry;
class hkVtableClassRegistry;
class hkTypeInfoRegistry;

/// Registry of all compiled in types.
/// All typeinfos and classes in the StaticLinkedTypeInfos and
/// StaticLinkedClasses lists are added to the registry when
/// this singleton is created.
class hkBuiltinTypeRegistry : public hkReferencedObject, public hkSingleton<hkBuiltinTypeRegistry>
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
			/// Access the hkTypeInfoRegistry.
		virtual hkTypeInfoRegistry* getTypeInfoRegistry() = 0;
		inline hkTypeInfoRegistry* getLoadedObjectRegistry() { return getTypeInfoRegistry(); }

			/// Access the hkClassNameRegistry.
		virtual hkClassNameRegistry* getClassNameRegistry() = 0;

			/// Access the hkVtableClassRegistry.
		virtual hkVtableClassRegistry* getVtableClassRegistry() = 0;

			/// Shortcut for adding to each of the registries.
		virtual void addType( const hkTypeInfo* info, const hkClass* klass );
	
		virtual void reinitialize() = 0;

	public:

			/// List of typeinfos which are added to the default registry - SEE DETAILS BELOW.
			/// NB Link errors (e.g. LNK2001 under .NET) for this array probably mean you
			/// have not yet registered the typeinfos via e.g., Common/Serialize/Util/hkBuiltinTypeRegistry.cxx using the HK_CLASSES_FILE macro.
			/// See the "Type Registration" section of the docs in the Serialization Chapter (or the demo/demos/*Classes.cpp files for examples, e.g., demo/demos/PhysicsClasses.cpp for Physics-Only customers).
		static const hkTypeInfo* const StaticLinkedTypeInfos[];

			/// List of classes which are added to the default registry - SEE DETAILS BELOW.
			/// NB Link errors (e.g. LNK2001 under .NET) for this array probably mean you
			/// have not yet registered the classlists via e.g., Common/Serialize/Util/hkBuiltinTypeRegistry.cxx using the HK_CLASSES_FILE macro.
			/// See the "Type Registration" section of the docs in the Serialization Chapter (or the demo/demos/*Classes.cpp files for examples, e.g., demo/demos/PhysicsClasses.cpp for Physics-Only customers).
		static const hkClass* const StaticLinkedClasses[];
};

#if defined(HK_COMPILER_ARMCC) || defined(HK_COMPILER_GHS) // have to specialize before use so that generalized one not auto gen-d
HK_SINGLETON_SPECIALIZATION_DECL(hkBuiltinTypeRegistry);
#endif

#endif // HK_SERIALIZE_BUILTINTYPEREGISTRY_H

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
