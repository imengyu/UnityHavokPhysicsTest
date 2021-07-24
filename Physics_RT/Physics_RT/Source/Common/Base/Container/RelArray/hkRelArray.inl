/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template <typename T>
HK_FORCE_INLINE hkRelArray<T>::hkRelArray(hkUint16 size, const void* ptr) : m_size(size)
{
	HK_ASSERT2(0x5259899b, (reinterpret_cast<hkUlong>(ptr) & hkUlong(0x0f)) == 0, "Incorrect alignment for hkRelArray member");
	m_offset = hkUint16(reinterpret_cast<const char*>(ptr) - reinterpret_cast<const char*>(this));
}

template <typename T>
HK_FORCE_INLINE const T& hkRelArray<T>::operator [](int index) const
{
	HK_ASSERT2(0x46e01b1d, (index >= 0) && (index < m_size), "Invalid index in hkRelArray");
	const T* ptr = reinterpret_cast<const T*>(reinterpret_cast<const char*>(this) + m_offset);
	return ptr[index];
}

template <typename T>
HK_FORCE_INLINE T& hkRelArray<T>::operator [](int index)
{
	HK_ASSERT2(0x4921797f, (index >= 0) && (index < m_size), "Invalid index in hkRelArray");
	T* ptr = reinterpret_cast<T*>(reinterpret_cast<char*>(this) + m_offset);
	return ptr[index];
}

template <typename T>
HK_FORCE_INLINE hkUint16 hkRelArray<T>::getSize() const
{
	return m_size;
}

template <typename T>
HK_FORCE_INLINE hkUint16 hkRelArray<T>::getOffset() const
{
	return m_offset;
}

template <typename T>
HK_FORCE_INLINE const T* hkRelArray<T>::begin() const
{
	return reinterpret_cast<const T*>(reinterpret_cast<const char*>(this) + m_offset);
}

template <typename T>
HK_FORCE_INLINE T* hkRelArray<T>::begin()
{
	return reinterpret_cast<T*>(reinterpret_cast<char*>(this) + m_offset);
}

template <typename T>
HK_FORCE_INLINE void hkRelArray<T>::_setSize(int size)
{
	HK_ASSERT( 0xf034deed, hkUint32(size) <= 0xffff );	// must fit into 16 bit
	m_size = hkUint16(size);
}

template <typename T>
HK_FORCE_INLINE void hkRelArray<T>::_setOffset(int offset)
{
	HK_ASSERT( 0xf034defd, hkUint32(offset) <= 0xffff );	// must fit into 16 bit
	m_offset = hkUint16(offset);
}

template <typename T>
HK_FORCE_INLINE void* hkRelArray<T>::operator new(hk_size_t size, hkRelArray<T>* object)
{
	HK_ASSERT2(0x1f4a821b, size == hkSizeOf(hkRelArray<T>), "Invalid size for hkRelArray placement");
	return object;
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
