/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKANIMATION_RIG_HKBONE_HKCLASS_H
#define HKANIMATION_RIG_HKBONE_HKCLASS_H

	/// hkaBone meta information
extern const class hkClass hkaBoneClass;

	/// The bone structure as seen by the toolchain.
class hkaBone
{
	public:
		
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RIG, hkaBone );
		HK_DECLARE_REFLECTION();

		HK_FORCE_INLINE hkaBone() : m_lockTranslation(false) {}
		HK_FORCE_INLINE hkaBone(const hkaBone& other)
		{
			*this = other;
		}
		HK_FORCE_INLINE hkaBone& operator=(const hkaBone& other)
		{
			if( this == &other )
			{
				return *this;
			}
			m_name = other.m_name;
			m_lockTranslation = other.m_lockTranslation;
			return *this;
		}
		HK_FORCE_INLINE hkaBone(hkFinishLoadedObjectFlag f) : m_name(f) {}
		
		//
		// Members
		//
	public:
		
			/// The name of the bone from the toolchain
		hkStringPtr m_name;
		
			/// Whether or not this bone can move relative to its parent
		hkBool m_lockTranslation;
};

#endif // HKANIMATION_RIG_HKBONE_HKCLASS_H

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
