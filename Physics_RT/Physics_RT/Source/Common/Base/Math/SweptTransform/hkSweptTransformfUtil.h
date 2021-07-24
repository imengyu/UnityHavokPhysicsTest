/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_SWEPT_TRANSFORMf_UTIL_H
#define HK_MATH_SWEPT_TRANSFORMf_UTIL_H


#include <Common/Base/Types/Physics/MotionState/hkMotionState.h>
#include <Common/Base/Types/Physics/hkStepInfo.h>

	/// A set of useful functions changing a hkMotionState or a SweptTransform
namespace hkSweptTransformUtil
{
			/// inline version of lerp2
		HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformf& sweptTrans, hkFloat32 t, hkQuaternionf& quatOut );
		HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformf& sweptTrans, hkSimdFloat32Parameter t, hkQuaternionf& quatOut );

			/// inline version of lerp2
		HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformf& sweptTrans, hkFloat32 t, hkTransformf& transformOut );
		HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformf& sweptTrans, hkSimdFloat32Parameter t, hkTransformf& transformOut );

			/// approximate a transform given an interpolation time
		void HK_CALL lerp2( const hkSweptTransformf& sweptTrans, hkTime time, hkTransformf& transformOut );
		void HK_CALL lerp2( const hkSweptTransformf& sweptTrans, hkSimdFloat32Parameter time, hkTransformf& transformOut );

			// internal function: approximate a transform given an interpolation time with a higher accuracy time input
		void HK_CALL lerp2Ha( const hkSweptTransformf& sweptTrans, hkTime t, hkFloat32 tAddOn, hkTransformf& transformOut );
		void HK_CALL lerp2Ha( const hkSweptTransformf& sweptTrans, hkSimdFloat32Parameter t, hkSimdFloat32Parameter tAddOn, hkTransformf& transformOut );

			/// approximate a transform given an interpolation value r between 0.0f and 1.0f.
			/// This uses an internal modified lerp (=linear interpolation of quaternion) functionality
		void HK_CALL lerp2Rel( const hkSweptTransformf& sweptTrans, hkFloat32 r, hkTransformf& transformOut );
		void HK_CALL lerp2Rel( const hkSweptTransformf& sweptTrans, hkSimdFloat32Parameter r, hkTransformf& transformOut );

			/// Calculate the transform at time0
		HK_FORCE_INLINE void HK_CALL calcTransAtT0( const hkSweptTransformf& sweptTrans, hkTransformf& transformOut );

			/// Calculate the transform at time1
		HK_FORCE_INLINE void HK_CALL calcTransAtT1( const hkSweptTransformf& sweptTrans, hkTransformf& transformOut );

#	if defined(HK_REAL_IS_FLOAT)
			/// Sets the center of mass in local space.
			/// This does not change the position of the object, however it does change m_centerOfMass0 and m_centerOfMass1
		void HK_CALL setCentreOfRotationLocal( hkVector4fParameter newCenterOfRotation, hkMotionState& sweptTrans);

			/// Step the motion forward in time.
			///
			/// Notes:
			///    - The angular velocity is clipped to 0.9*pi*invDeltatime
		HK_FORCE_INLINE void HK_CALL _stepMotionState( const hkStepInfo& stepInfo, hkVector4f& linearVelocity, hkVector4f& angularVelocity, hkMotionState& motionState );

			/// clips the input velocities
		HK_FORCE_INLINE void HK_CALL _clipVelocities( const hkMotionState& motionState, hkVector4f& linearVelocity, hkVector4f& angularVelocity );

			/// Allows you to integrate a motions state by not using velocities, but by specifying the next mass center position and rotation.
		void HK_CALL keyframeMotionState( const hkStepInfo& stepInfo, hkVector4fParameter pos1, hkQuaternionfParameter rot1, hkMotionState& motionState );

			/// Gets the mass center at a given time t.
		HK_FORCE_INLINE void HK_CALL calcCenterOfMassAt( const hkMotionState& ms, hkTime t, hkVector4f& centerOut );
		HK_FORCE_INLINE void HK_CALL calcCenterOfMassAt( const hkMotionState& ms, hkSimdFloat32Parameter t, hkVector4f& centerOut );

			/// Return the velocity which was used to integrate the motion state from state 0 to state 1
		HK_FORCE_INLINE void HK_CALL getVelocity( const hkMotionState& ms, hkVector4f& linearVelOut, hkVector4f& angularVelOut );

			// interpolates the information of t1 to be at time t.
		void HK_CALL backStepMotionState( hkTime t, hkMotionState& motionState );
		void HK_CALL backStepMotionState( hkSimdFloat32Parameter t, hkMotionState& motionState );

			// Internal function. Only used upon deactivation of entities
		void HK_CALL freezeMotionState( hkTime time, hkMotionState& motionState );
		void HK_CALL freezeMotionState( hkSimdFloat32Parameter time, hkMotionState& motionState );

			// Call this if you deactivate a body (otherwise numerical problems can result in strange extrapolation of body movement)
		HK_FORCE_INLINE void HK_CALL deactivate( hkMotionState& ms );
			
			// Internal function. Only used upon activation of entities 
		void HK_CALL setTimeInformation( hkTime startTime, hkFloat32 invDeltaTime, hkMotionState& motionState);
		void HK_CALL setTimeInformation( hkSimdFloat32Parameter startTime, hkSimdFloat32Parameter invDeltaTime, hkMotionState& motionState);

			/// Warp the geometry center of both frames to position
		void HK_CALL warpToPosition( hkVector4fParameter position, hkMotionState& ms );

			/// Warp the orientation of both frames to rotations. Note: This changes the m_centerOfMass
		void HK_CALL warpToRotation( hkQuaternionfParameter rotation, hkMotionState& ms );

			/// Warp to position and orientation
		void HK_CALL warpTo( hkVector4fParameter position, hkQuaternionfParameter rotation, hkMotionState& ms );

			/// Warp to a new transform (includes both frames)
		void HK_CALL warpTo( const hkTransformf& transform, hkMotionState& ms );

			// For a given delta time: Calc the relative linear movement (xyz) and the worst case angular movment (w)
		HK_FORCE_INLINE void HK_CALL calcTimInfo( const hkMotionState& ms0, const hkMotionState& ms1, hkFloat32 deltaTime, hkVector4f& timOut);

			// calc the relative angular movement for a reduced step
		HK_FORCE_INLINE void HK_CALL calcAngularTimInfo( const hkMotionState& ms0, const hkMotionState& ms1, hkFloat32 deltaTime, hkVector4f* deltaAngleOut0, hkVector4f* deltaAngleOut1 );
#endif // defined(HK_REAL_IS_FLOAT)

		extern const hkQuadFloat32 _stepMotionStateMaxVelf; 
}

#include <Common/Base/Math/SweptTransform/hkSweptTransformfUtil.inl>

#endif // HK_MATH_SWEPT_TRANSFORMf_UTIL_H

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
