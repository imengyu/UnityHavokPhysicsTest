/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
template <typename T>
HK_FORCE_INLINE void hkArrayUtil::construct(T* t, int n, hkTrait::TypeIsPod)
{
}

template <typename T>
HK_FORCE_INLINE void hkArrayUtil::construct(T* t, int n, hkTrait::TypeIsClass)
{
	for(int i = 0; i < n; ++i)
	{
		::new (reinterpret_cast<hkPlacementNewArg*>(t+i)) T;
	}
}

template <typename T>
HK_FORCE_INLINE void hkArrayUtil::constructWithCopy(T* t, int n, const T& tcopy, hkTrait::TypeIsPod)
{
	for(int i = 0; i < n; ++i)
	{
		t[i] = tcopy;
	}
}

template <typename T>
HK_FORCE_INLINE void hkArrayUtil::constructWithCopy(T* t, int n, const T& tcopy, hkTrait::TypeIsClass)
{
	for(int i = 0; i < n; ++i)
	{
		void* buffer = (void*) hkAddByteOffsetConst( t, sizeof(T) * i);
		::new (reinterpret_cast<hkPlacementNewArg*>( buffer )) T(tcopy);
	}
}

template <typename T>
HK_FORCE_INLINE void hkArrayUtil::constructWithArray(T* t, int n, const T* tcopy, hkTrait::TypeIsPod)
{
	for(int i = 0; i < n; ++i)
	{
		t[i] = tcopy[i];
	}
}

template <typename T>
HK_FORCE_INLINE void hkArrayUtil::constructWithArray(T* t, int n, const T* tcopy, hkTrait::TypeIsClass)
{
	for(int i = 0; i < n; ++i)
	{
		::new (reinterpret_cast<hkPlacementNewArg*>(t+i)) T(tcopy[i]);
	}
}

template <typename T>
HK_FORCE_INLINE void hkArrayUtil::destruct(T* t, int n, hkTrait::TypeIsPod)
{
}

template <typename T>
HK_FORCE_INLINE void hkArrayUtil::destruct(T* t, int n, hkTrait::TypeIsClass )
{
	for(int i = n-1; i >= 0; --i)
	{
		static_cast<T*>(t)[i].~T();
	}
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
