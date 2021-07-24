/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template<class TYPE>
HK_FORCE_INLINE hkRefPtr<TYPE>::hkRefPtr() : m_pntr(HK_NULL)
{
}

template<class TYPE>
HK_FORCE_INLINE hkRefPtr<TYPE>::hkRefPtr(hkFinishLoadedObjectFlag ) {}

template<class TYPE>
HK_FORCE_INLINE hkRefPtr<TYPE>::hkRefPtr(const hkRefPtr& rp)
{
	if ( rp.m_pntr )
	{
#ifndef HK_PLATFORM_SPU
		rp.m_pntr->addReference();
#endif
	}
	m_pntr = rp.m_pntr;
}

template<class TYPE>
HK_FORCE_INLINE hkRefPtr<TYPE>::hkRefPtr(hkRefLoan<TYPE> rp)
{
#ifndef HK_PLATFORM_SPU
	if( TYPE* t = rp )
	{
		t->addReference();
	}
#endif
	m_pntr = rp;
}

template<class TYPE>
HK_FORCE_INLINE hkRefPtr<TYPE>::hkRefPtr(hkRefNew<TYPE> rp)
{
	m_pntr = rp.stealOwnership();
}

template<class TYPE>
HK_FORCE_INLINE hkRefPtr<TYPE>::hkRefPtr(TYPE* e)
{
	if ( e )
	{
#ifndef HK_PLATFORM_SPU
		e->addReference();
#endif
	}
	m_pntr = e;
}

template<class TYPE>
HK_FORCE_INLINE hkRefPtr<TYPE>::~hkRefPtr()
{
	if ( m_pntr )
	{
#ifndef HK_PLATFORM_SPU
		m_pntr->removeReference();
#endif
	}
	m_pntr = HK_NULL;
}

template<class TYPE>
HK_FORCE_INLINE void hkRefPtr<TYPE>::operator=(const hkRefPtr& rp)
{
	if ( rp.m_pntr )
	{
#ifndef HK_PLATFORM_SPU
		rp.m_pntr->addReference(); // add reference first to allow self-assignment
#endif
	}
	if ( m_pntr )
	{
#ifndef HK_PLATFORM_SPU
		m_pntr->removeReference();
#endif
	}
	m_pntr = rp.m_pntr;
}

template<class TYPE>
HK_FORCE_INLINE void hkRefPtr<TYPE>::operator=(hkRefLoan<TYPE> e)
{
	operator=( static_cast<TYPE*>(e) );
}

template<class TYPE>
HK_FORCE_INLINE void hkRefPtr<TYPE>::operator=(hkRefNew<TYPE> e)
{
	if( m_pntr )
	{
#ifndef HK_PLATFORM_SPU
		m_pntr->removeReference();
#endif
	}
	m_pntr = e.stealOwnership();
}

template<class TYPE>
HK_FORCE_INLINE void hkRefPtr<TYPE>::operator=(TYPE* e)
{
	if ( e )
	{
#ifndef HK_PLATFORM_SPU
		e->addReference(); // add reference first to allow self-assignment
#endif
	}
	if ( m_pntr )
	{
#ifndef HK_PLATFORM_SPU
		m_pntr->removeReference();
#endif
	}
	m_pntr = e;
}

template<class TYPE>
HK_FORCE_INLINE TYPE* hkRefPtr<TYPE>::val() const
{
	return m_pntr;
}

template<class TYPE>
HK_FORCE_INLINE TYPE* hkRefPtr<TYPE>::operator->() const
{
	return m_pntr;
}

template<class TYPE>
HK_FORCE_INLINE void hkRefPtr<TYPE>::setAndDontIncrementRefCount( TYPE* e )
{
	if ( m_pntr && m_pntr != e )
	{
#ifndef HK_PLATFORM_SPU
		m_pntr->removeReference();
#endif
	}
	m_pntr = e;
}

template<class TYPE>
HK_FORCE_INLINE hkRefPtr<TYPE>::operator TYPE*() const
{
	return val();
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
