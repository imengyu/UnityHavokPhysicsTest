/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_CHARACTER_MOVEMENT_UTIL_H
#define HK_CHARACTER_MOVEMENT_UTIL_H

/// This utility class calculates an output velocity in world space given a moving surface frame
/// and a desired velocity in this frame. This code is used in many of the states to control movement
class hkpCharacterMovementUtil
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkpCharacterMovementUtil);

		/// The struct passed as input to calculate the new character velocity.
		struct hkpMovementUtilInput
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkpCharacterMovementUtil::hkpMovementUtilInput );

			/// Signifies the space the desired velocity is defined in
			enum DesiredVelocitySpace
			{
				SURFACE_SPACE = 0,
				WORLD_SPACE,
				DEFAULT_SPACE = SURFACE_SPACE,
			};

			// Ctor.
			hkpMovementUtilInput() : m_desiredVelocitySpace(DEFAULT_SPACE) {}

			/// Forward direction in world space
			hkVector4 m_forward;

			/// Up direction in world space
			hkVector4 m_up;

			/// Normal of the surface we're standing on in world space
			hkVector4 m_surfaceNormal;

			/// Our current velocity in world space
			hkVector4 m_currentVelocity;

			/// Our desired velocity in world space OR surface frame (see m_desiredVelocityInSurfaceFrame)
			hkVector4 m_desiredVelocity;

			/// Velocity of the surface we're standing on in world space
			hkVector4 m_surfaceVelocity;

			/// Gain for the character controller.
			/// This variable controls the acceleration of the character. It should be
			/// scaled by the current timestep to ensure that the characters acceleration
			/// is not timestep dependent.
			hkReal    m_gain;

			/// Limit the maximum acceleration of the character
			hkReal m_maxVelocityDelta;

			/// The space the desired velocity is defined in
			hkEnum<DesiredVelocitySpace, hkUint8> m_desiredVelocitySpace;
		};

		/// Calculate a new output velocity based on the input
		static void HK_CALL calculateMovement( const hkpMovementUtilInput& input, hkVector4& velocityOut );

};

#endif // HK_CHARACTER_MOVEMENT_UTIL_H

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
