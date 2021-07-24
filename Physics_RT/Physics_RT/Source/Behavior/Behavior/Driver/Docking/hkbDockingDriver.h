/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKB_DOCKING_DRIVER_H
#define HKB_DOCKING_DRIVER_H

#include <Behavior/Behavior/Driver/Docking/Target/hkbDockingTarget.h>

class hkbContext;
class hkbGeneratorOutput;

	/// Provides corrections to the characters world from model in order to constrain the character
class hkbDockingDriver : public hkReferencedObject
{
	public:
		
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BEHAVIOR );

		hkbDockingDriver()
		:	m_dockingTarget(HK_NULL),
			m_worldFromNewReference(),
			m_worldFromOldReference()
		{
			m_worldFromNewReference.setIdentity();
			m_worldFromOldReference.setIdentity();
		}

			/// Called by the scene modifier utils to update the generator output for the current docking target
			/// and reference frame.
		void dock( const hkbContext& context, hkbGeneratorOutput& generatorOutput );

			/// If you character no longer has a reference frame, call this function.
		void clearWorldFromReference() { setWorldFromReference( hkQsTransform::getIdentity() ); }

			/// If you are changing to a new distinct reference frame, call this function.
		void setWorldFromReference( const hkQsTransform& worldFromReference );

			/// If you are updating a reference frame to new coordinates, call this function.
		void updateWorldFromReference( const hkQsTransform& worldFromReference );

			/// Gets the current reference frame
		const hkQsTransform& getWorldFromReference() const { return m_worldFromNewReference; }

			/// The object that defines how a character is to dock
		hkRefPtr<hkbDockingTarget> m_dockingTarget;

		const hkQsTransform& getLastTarget() const { return m_lastTarget; }
		const hkQsTransform& getFirstTarget() const { return m_firstTarget; }
		const hkQsTransform& getLastDesiredTarget() const { return m_lastDesiredTarget; }
		hkReal getLastBlendParam() const { return m_lastBlend; }

	protected:

		void getError(const hkQsTransform& transformA, const hkQsTransform& transformB, hkReal blendParam, hkReal lastBlendParam, hkQsTransform& error);

		hkQsTransform	m_worldFromNewReference;
		hkQsTransform	m_worldFromOldReference;

		hkQsTransform	m_lastTarget;
		hkQsTransform	m_firstTarget;
		hkQsTransform	m_lastDesiredTarget;
		hkReal			m_lastBlend;
};

#endif

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
