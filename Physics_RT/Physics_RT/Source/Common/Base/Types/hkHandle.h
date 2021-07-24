/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_BASE_HANDLE_H
#define HK_BASE_HANDLE_H

#include <Common/Base/Reflection/hkClassMember.h>

/// Nullable and orderable handle.
/// Use HK_DECLARE_HANDLE( name , type , invalid value ) macro for declarations.
template <typename TYPE, hkUint32 INVALID_VALUE, typename DISCRIMINANT>
struct hkHandle
{
		HK_DECLARE_POD_TYPE();

		/// Underlying type.
		typedef TYPE	Type;

		/// Invalid value.
		enum { InvalidValue = INVALID_VALUE };
		
		/// Needed for internal serialization
		explicit HK_FORCE_INLINE			hkHandle(hkFinishLoadedObjectFlag f) {}
		
		/// Only allow for explicit or default construction.
		explicit HK_FORCE_INLINE			hkHandle(int v) : m_value((TYPE)v) {}

		HK_FORCE_INLINE			hkHandle(){}

		/// Assignment.
	#if defined(HK_PLATFORM_RVL)
		HK_FORCE_INLINE hkHandle&	operator =(const hkHandle& other) { m_value = other.m_value; return *this; }
	#else
		HK_FORCE_INLINE hkHandle&	operator =(hkHandle other) { m_value = other.m_value; return *this; }
	#endif

		/// Check for '=='.
		HK_FORCE_INLINE bool		operator ==(hkHandle other) const	{ return m_value == other.m_value; }

		/// Check for '!='.
		HK_FORCE_INLINE bool		operator !=(hkHandle other) const	{ return m_value != other.m_value; }

		/// Check for '<'.
		HK_FORCE_INLINE bool		operator <(hkHandle other) const	{ return m_value < other.m_value; }

		/// Check for '<='.
		HK_FORCE_INLINE bool		operator <=(hkHandle other) const	{ return m_value <= other.m_value; }

		/// Check for '>'.
		HK_FORCE_INLINE bool		operator >(hkHandle other) const	{ return m_value > other.m_value; }

		/// Check for '>='.
		HK_FORCE_INLINE bool		operator >=(hkHandle other) const	{ return m_value >= other.m_value; }	

		/// Increment ID.
		//HK_FORCE_INLINE void		increment()							{ ++m_value; }

		/// Decrement ID.
		//HK_FORCE_INLINE void		decrement()							{ --m_value; }

		/// Read-only access to the actual index value.
		HK_FORCE_INLINE	TYPE		value() const						{ HK_ASSERT( 0xf03465fc, m_value != (TYPE)INVALID_VALUE); return m_value; }

		HK_FORCE_INLINE	TYPE		valueUnchecked() const				{ return m_value; }

		/// Read-write access to the actual index value. Removed since we should be able to assign a value
		//HK_FORCE_INLINE	TYPE&		value()								{ return m_value; }
		
		/// Check if the ID is valid ( != INVALID_VALUE / != invalid() )
		HK_FORCE_INLINE bool		isValid() const						{ return m_value != INVALID_VALUE; }
		
		/// Get an invalid ID ( equivalent to hkHandle() ).
		static HK_FORCE_INLINE hkHandle	invalid()						{ return hkHandle(INVALID_VALUE); }

	#if defined(HK_PLATFORM_PS3_SPU) 
		/// SPU Storage type.
		typedef typename hkSpuStorage<TYPE>::StorageType	SpuStorageType;

		/// SPU Promotion type.
		struct SpuPromoteType
		{
			typedef typename hkSpuStorage<TYPE>::PromoteType	ValueType;
			ValueType		m_value;

			HK_FORCE_INLINE	SpuPromoteType(const hkHandle& handle) : m_value(handle.value()) {}
			HK_FORCE_INLINE	operator ValueType() const { return m_value; }
		};
	#endif
	protected:

		TYPE	m_value;	///< Actual handle value.
};


#define HK_DECLARE_HANDLE(_name_ , _type_ , _nullvalue_) struct _name_##Discriminant {}; typedef hkHandle<_type_, _nullvalue_, _name_##Discriminant> _name_

#endif //HK_BASE_HANDLE_H

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
