/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKSINGLETON_H
#define HKBASE_HKSINGLETON_H

/// Utility class to define global objects.
/// Singletons are created when hkBaseSystem::init() is called.
/// They are deleted automatically when hkBaseSystem::quit() is called.
///
/// To use this class, make a public default constructor. Parameter type in the template
/// must be derived from hkReferencedObject.
/// You will also need to put a HK_SINGLETON_IMPLEMENTATION
/// macro into its cpp.
template <typename T>
class hkSingleton
{
	public:

		static T* s_instance;

			/// Get the instance of this singleton. This creates an instance when hkBaseSystem::init is called.
		static HK_FORCE_INLINE T& HK_CALL getInstance()
		{
			return *hkSingleton<T>::s_instance;
		}

			/// Remove a reference to the existing singleton and use the supplied one instead.
		static void HK_CALL replaceInstance(T* t)
		{
			if(hkSingleton<T>::s_instance)
			{
				hkSingleton<T>::s_instance->removeReferenceLockUnchecked();
			}
			hkSingleton<T>::s_instance = t;
		}

		/// Remove a reference to the existing singleton and use the supplied one instead adding a reference to it.
		static void HK_CALL replaceInstanceAndAddReference(T* t)
		{
			t->addReferenceLockUnchecked();
			if (hkSingleton<T>::s_instance)
			{
				hkSingleton<T>::s_instance->removeReferenceLockUnchecked();
			}
			hkSingleton<T>::s_instance = t;			
		}

			/// Has this singleton been initialized?
		static hkBool HK_CALL isInitialised()
		{
			return hkSingleton<T>::s_instance != HK_NULL;
		}

	protected:

		hkSingleton() { }

		hkSingleton(const hkSingleton&); //not implemented
		hkSingleton& operator= (const hkSingleton&); //not implemented
};

extern struct hkSingletonInitNode* hkSingletonInitList;

/// An internal class for registering global instances. You will not need to
/// use it except for very low level hacking.
struct hkSingletonInitNode
{
	typedef hkReferencedObject* (HK_CALL *SingletonCreationFunction)();
	hkSingletonInitNode(const char* name, SingletonCreationFunction func, void** ptr)
		: m_name(name), m_createFunc(func), m_value(ptr)
	{
		m_next = hkSingletonInitList;
		hkSingletonInitList = this;
	}
	const char* m_name;
	/// The creation function identifies what type of singleton this is:
	/// - it is automatically generated for normal singletons
	/// - it is manually specified for custom singletons and should always be not HK_NULL
	/// - it is always HK_NULL for manual singletons.
	SingletonCreationFunction m_createFunc;
	hkSingletonInitNode* m_next;
	void** m_value;

	static void HK_CALL populate(hkSingletonInitNode* dst, const hkSingletonInitNode* src);
	static void HK_CALL depopulate(hkSingletonInitNode* dst, const hkSingletonInitNode* src);
	
	hkSingletonInitNode* findByName( const char* name );

private:
	HK_DECLARE_PLACEMENT_ALLOCATOR();
};
	
/// Add BASE_CLASS to the singleton init list.
/// The singleton is automatically created with all the other singletons and automatically destroyed.
#define HK_SINGLETON_IMPLEMENTATION(BASE_CLASS) \
	template<> BASE_CLASS* hkSingleton<BASE_CLASS>::s_instance = HK_NULL; \
	static hkReferencedObject* HK_CALL BASE_CLASS ## create() { return new BASE_CLASS(); } \
	static hkSingletonInitNode hkSingletonRegister##BASE_CLASS (#BASE_CLASS, &BASE_CLASS ## create, (void**)&BASE_CLASS::s_instance)

/// Add CUSTOM_CLASS as the implementation of BASE_CLASS to the singleton init list.
/// The singleton is automatically created with all the other singletons and automatically destroyed.
#define HK_SINGLETON_CUSTOM_IMPLEMENTATION(BASE_CLASS, CUSTOM_CLASS) \
	template<> BASE_CLASS* hkSingleton<BASE_CLASS>::s_instance = HK_NULL; \
	static hkReferencedObject* HK_CALL BASE_CLASS ## create() { return new CUSTOM_CLASS(); } \
	static hkSingletonInitNode hkSingletonRegister##BASE_CLASS (#BASE_CLASS, &BASE_CLASS ## create, (void**)&BASE_CLASS::s_instance)

/// When the singleton is to be instantiated at start up a function is called. If the function returns HK_NULL
/// it indicates the construction couldn't be performed, because something else needed to be constructed first.
/// Havok will automatically try to reconstruct once other singletons have been constructed.
/// 
/// The signature of the function should be hkReferencedObject* HK_CALL func() { ... }.
/// The singleton is automatically created with all the other singletons with the given custom call, and automatically 
/// destroyed as a normal singleton.
#define HK_SINGLETON_CUSTOM_CALL(BASE_CLASS, FUNC) \
	template<> BASE_CLASS* hkSingleton<BASE_CLASS>::s_instance = HK_NULL; \
	static hkSingletonInitNode hkSingletonRegister##BASE_CLASS (#BASE_CLASS, &FUNC, (void**)&BASE_CLASS::s_instance)

/// Manual implementation singletons have null creation pointers and must
/// explicitly be initialized in hkBaseSystem::init().
/// The singleton is NOT automatically created or automatically destroyed, the user will need to create and
/// delete it manually using hkSingleton<>::replaceInstance(). This allows for creation of the singleton before
/// any other singleton and deletion after all others.
#define HK_SINGLETON_MANUAL_IMPLEMENTATION(BASE_CLASS) \
	template<> BASE_CLASS* hkSingleton<BASE_CLASS>::s_instance = HK_NULL; \
	static hkSingletonInitNode hkSingletonRegister##BASE_CLASS (#BASE_CLASS, HK_NULL, (void**)&BASE_CLASS::s_instance)

#define HK_SINGLETON_SPECIALIZATION_DECL(BASE_CLASS) \
	template<> BASE_CLASS* hkSingleton<BASE_CLASS>::s_instance

#endif // HKBASE_HKSINGLETON_H

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
