/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKARRAY_UTIL_H
#define HKBASE_HKARRAY_UTIL_H

	/// Common functionality for all hkArray types.
	/// Resizing functions are out of line functions to avoid code bloat.
class hkArrayUtil
{
public:

	template<typename T> static HK_FORCE_INLINE void construct(T* t, int n, hkTrait::TypeIsPod);
	template<typename T> static HK_FORCE_INLINE void construct(T* t, int n, hkTrait::TypeIsClass);

	template<typename T> static HK_FORCE_INLINE void constructWithCopy(T* t, int n, const T& tcopy, hkTrait::TypeIsPod);
	template<typename T> static HK_FORCE_INLINE void constructWithCopy(T* t, int n, const T& tcopy, hkTrait::TypeIsClass);

	template<typename T> static HK_FORCE_INLINE void destruct(T* t, int n, hkTrait::TypeIsPod);
	template<typename T> static HK_FORCE_INLINE void destruct(T* t, int n, hkTrait::TypeIsClass);

	template<typename T> static HK_FORCE_INLINE void constructWithArray(T* t, int n, const T* tcopy, hkTrait::TypeIsPod);
	template<typename T> static HK_FORCE_INLINE void constructWithArray(T* t, int n, const T* tcopy, hkTrait::TypeIsClass);

	static hkResult HK_CALL _reserve( hkMemoryAllocator& a, void*, int reqElem, int sizeElem);
	static void HK_CALL _reserveMore( hkMemoryAllocator& a, void* array, int sizeElem);
	static void HK_CALL _reduce( hkMemoryAllocator& a, void* array, int sizeElem, char* inplaceMem, int requestedCapacity);
};


#include <Common/Base/Container/Array/hkArrayUtil.inl>

#endif // HKBASE_HKARRAY_UTIL_H

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
