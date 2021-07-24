/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBP_CHARACTER_CONTROLLER_H
#define HKBP_CHARACTER_CONTROLLER_H

#include <Behavior/Utilities/Physics/Interface/hkbCharacterController.h>
#include <Physics2012/Utilities/CharacterControl/hkpCharacterControl.h>
#include <Behavior/Utilities/Physics/hkbPhysicsConfig.h>

class hkpCollidable;

	/// Havok Physics2012 abstract class to allow for getting the hkpCollidable from the character controller.
class hkbpCharacterController : public hkbCharacterController
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BEHAVIOR );

			// Ctor.
		hkbpCharacterController();

			// hkbCharacterController interface
		virtual void applyVelocityModifiers(
			const hkbContext& context,
			const hkbGeneratorOutput& currentOutput,
			hkVector4Parameter desiredVelocity,
			hkBinaryReal gravityBlendFactor,
			hkReal timestep,
			hkVector4& newVelocityOut ) HK_OVERRIDE;

			/// Get the hkpCollidable used by this character controller.
		virtual const hkpCollidable* getCollidable() const = 0;

	protected:

			/// Cached ground info from supported call
		hkpSurfaceInfo m_groundInfo;

};

#endif // HKBP_CHARACTER_CONTROLLER_H

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
