/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONTACT_POINT_PROPERTIES_H
#define HKP_CONTACT_POINT_PROPERTIES_H

#include <Physics/ConstraintSolver/Solve/hkpSolverResults.h>
#include <Common/Base/Types/Physics/ContactPoint/hkContactPointMaterial.h>

#define HK_NUM_EXTENDED_USER_DATAS_IN_TOI_EVENT 7

struct hkpSimpleContactConstraintAtom; 


///
class hkpContactPointProperties : public hkpSolverResults, public hkContactPointMaterial
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkpContactPointProperties );

			/// returns true if this contact point was really used by the solver
			/// and an impulse was applied
		inline bool wasUsed()
		{
			return !isPotential() && ( m_impulseApplied > hkReal(0) );
		}

	public:

			// internal data, not for client use
		hkReal m_internalDataA;

		typedef hkUint32 UserData;

		// The use of ExtendedUserData for anything other than shape keys is deprecated.
		static inline int getNumExtendedUserDatas(const hkpSimpleContactConstraintAtom* atom, int bodyIdx);
		inline UserData* getStartOfExtendedUserData( const hkpSimpleContactConstraintAtom* atom );
		inline UserData& getExtendedUserData(const hkpSimpleContactConstraintAtom* atom, int bodyIdx, int i);
};


///
HK_CLASSALIGN(class,HK_REAL_ALIGNMENT) hkContactPointPropertiesWithExtendedUserData16 : public hkpContactPointProperties
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkContactPointPropertiesWithExtendedUserData16 );

		void set(const hkContactPointPropertiesWithExtendedUserData16& other)
		{
#			if defined(HK_PLATFORM_PS3_SPU) || defined(HK_PLATFORM_PS3_PPU)
			vec_int4* d = (vec_int4*)this;
			d[0] = ((const vec_int4*)&other)[0];
			d[1] = ((const vec_int4*)&other)[1];
			d[2] = ((const vec_int4*)&other)[2];
#			else
#				if defined (HK_PLATFORM_HAS_SPU)
				HK_ASSERT2(0xad810217, ((hkUlong(this) & 0xf) == 0x0) && ((hkUlong(&other) & 0xf) == 0x0), "hkContactPointProperties not aligned when copying from Spu." );
#				endif
			*this = other;
#			endif 
		}

		UserData m_extendedUserDatas[HK_NUM_EXTENDED_USER_DATAS_IN_TOI_EVENT];
};


///
class hkpContactPointPropertiesStream
{
	public:

		HK_FORCE_INLINE hkpContactPointProperties* asProperties() { return reinterpret_cast<hkpContactPointProperties*>(this); }
		HK_FORCE_INLINE const hkpContactPointProperties* asProperties() const { return reinterpret_cast<const hkpContactPointProperties*>(this); }

	#if defined HK_DEBUG
		HK_FORCE_INLINE void operator[](int i) { HK_ASSERT2(0xad7655aa, false, "Array-element access operator not allowed. Offset the pointer by proper striding and then conver to (non-Ex) hkpContactPointProperties."); }
	#endif	
};


// Only include that after the hkpContactPointProperties are defined
#include <Physics2012/Dynamics/Constraint/Atom/hkpSimpleContactConstraintAtom.h>


inline int hkpContactPointProperties::getNumExtendedUserDatas(const hkpSimpleContactConstraintAtom* atom, int bodyIdx)
{
	HK_ASSERT2(0xad7854aa, (&atom->m_numUserDatasForBodyA)+1 == (&atom->m_numUserDatasForBodyB), "Member variables incorrectly ordered.");
	return (&atom->m_numUserDatasForBodyA)[bodyIdx];
}

inline hkpContactPointProperties::UserData* hkpContactPointProperties::getStartOfExtendedUserData( const hkpSimpleContactConstraintAtom* atom )
{
	// Assert this is the right atom.. This doesn't work for TOIs...
	// This assert is disabled for TOIs
	HK_ASSERT2(0xad765512, m_internalDataA == 321.0f || ((hkUlong) atom < (hkUlong) this && (hkUlong) this < (hkUlong) hkAddByteOffset( (void*) atom, atom->m_sizeOfAllAtoms ) ), "The properties doesn't belong to that atom." );
	return (hkpContactPointProperties::UserData*) ( this + 1 );
}

inline hkpContactPointProperties::UserData& hkpContactPointProperties::getExtendedUserData(const hkpSimpleContactConstraintAtom* atom, int bodyIdx, int i) 
{
	// Assert this is the right atom.. This doesn't work for TOIs...
	// This assert is disabled for TOIs
	HK_ASSERT2(0xad765512, m_internalDataA == 321.0f || ((hkUlong)atom < (hkUlong)this && (hkUlong)this < (hkUlong)hkAddByteOffset((void*)atom, atom->m_sizeOfAllAtoms)), "The properties doesn't belong to that atom.");
	HK_ASSERT2(0xad8755aa, i < getNumExtendedUserDatas(atom, bodyIdx) && 0 <= bodyIdx && bodyIdx <= 1, "Index out of range.");
	return *(hkpContactPointProperties::UserData*)hkAddByteOffset((this+1), sizeof(hkpContactPointProperties::UserData) * (bodyIdx * getNumExtendedUserDatas(atom, 0) + i));
}


#endif // HKP_CONTACT_POINT_PROPERTIES_H

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
