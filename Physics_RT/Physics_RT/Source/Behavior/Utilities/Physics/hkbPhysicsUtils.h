/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef hkbPhysicsUtils_H
#define hkbPhysicsUtils_H

#include <Behavior/Utilities/Physics/hkbPhysicsBaseTypes.h>
#include <Behavior/Behavior/Context/hkbContext.h>
#include <Behavior/Behavior/Character/hkbCharacter.h>
#include <Behavior/Utilities/Physics/Interface/hkbPhysicsInterface.h>

class hkbContext;
class hkaPose;
class hkaSkeletonMapper;

/// A set of physics utilities used by the SDK.
class hkbPhysicsUtils
{
public:

		/// Warn if the context doesn't contain a physics interface.
	static hkbPhysicsInterface* HK_CALL warnPhysicsInterface( const hkbContext& context );
	
		/// Warn if the physics interface is null.
	static hkbPhysicsInterface* HK_CALL warnPhysicsInterface( hkbPhysicsInterface* physicsInterface );

		/// Assert if the context doesn't contain a physics interface.
	static hkbPhysicsInterface* HK_CALL requirePhysicsInterface( const hkbContext& context );

		/// Assert if the physics interface is null.
	static hkbPhysicsInterface* HK_CALL requirePhysicsInterface( hkbPhysicsInterface* physicsInterface );

		/// Change velocities of body to move to future (position, orientation) in time deltaTime.
		/// Note: You must pass in INVERSE deltaTime.
		/// Note: All the positions for HARD keyframes are automatically converted to be "centre-of-mass" positions
		/// using the information in the body supplied.
	static void HK_CALL applyHardKeyFrame(
		hkbPhysicsInterface* physicsInterface,
		const hkVector4& nextPosition,
		const hkQuaternion& nextOrientation,
		hkReal invDeltaTime,
		hkbRigidBodyHandle rigidBody );

	//////////////////////////////////////////////////////////////////////////
	// Deprecated Physics Utility Functions
	// Requires bridge be built with HKBP_DEPRECATED_PHYSICS_NODE_SUPPORT/HKBNP_DEPRECATED_PHYSICS_NODE_SUPPORT
	//////////////////////////////////////////////////////////////////////////

		/// Compute the velocity of the center-of-mass of an animation generator at a specific time.
		/// The deltaTimeForFiniteDifference parameter determines the finite-difference granularity.
	static void HK_CALL computeComVelocity(
		hkbGenerator* generator,
		hkbContext& context, 
		const hkReal time, 
		const hkReal deltaTimeForFiniteDifference,
		hkVector4& comVelocity );

		/// Compute the radial velocity of the center-of-mass of an animation generator.  Decomposes the
		/// velocity into polar form, after projecting onto an x-y plane that can be any of the 
		/// standard coordinate planes.
	static void HK_CALL computeRadialComVelocity(
		hkbGenerator* generator, 
		hkbContext& context,
		const hkReal time,
		const hkReal deltaTimeForFiniteDifference,
		const int xAxisMS,
		const int yAxisMS,
		hkReal& angle,
		hkReal& radialSpeed );
};

#include <Behavior/Utilities/Physics/hkbPhysicsUtils.inl>

#endif // hkbPhysicsUtils_H

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
