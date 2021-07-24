/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_QUATERNIONf_H
#define HK_MATH_QUATERNIONf_H

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif


/// Stores a unit quaternion.
/// "Unitness" is not enforced, but certain functions (such as division
/// and inversion ) DO assume that the quaternions are unit quaternions.
///
/// \b NOTE - The constructor taking (hkVector4f, hkFloat32) does not set real,imag
///                     but assumes [angle,axis] format.
///
/// \b NOTE - getAxis() returns a valid value only if the angle of the rotation
///                     is nonzero, since the axis is undefined for a rotation of zero degrees
///                     and it is not possible to return it even if the Quaternion was created
///                     from an angle and axis. It was decided that returning an arbitrary
///                     axis would be confusing, so it is up to you to check that the
///                     stored axis is nonzero before attempting to get the axis.
///                     Otherwise, a division by zero Will occur.
///
/// Conventions adopted:
///
///    - When specified by an (angle,axis) pair, the standard mathematical convention is
///      followed, with the angle taken to be such that Quaternion(PI/2, Vector4(0,0,1))
///      will rotate the X vector (1,0,0) to the Y vector (0,0,1). If you are converting to/from a system
///      where such a quaternion would rotate X to -Y, then you will need to flip the angle or axis
///      to convert successfully.
///
///    - p/q is assumed to be p * ( q-inverse ). This
///      is an arbitrary decision since ( q-inverse ) * p is also plausible.
///
///    - The angle extracted by getAngle() is ALWAYS in the range 0 -> PI, since we
///      wish to resolve the ambiguity of storing R(a,v) as either q(a,v) or -q(a,v).
///      It would be nice to assume the real part of q was always positive,
///      but operations involving conversion from transform to quaternion or
///      quaternion multiplication may not preserve this. The best we can do
///      without more code checking) is to let R(a,v) be stored as either,
///      and overload the == operator to check both possibilities.
///      Note that the storage is (imag, real): ((xyz), w)
HK_PASS_IN_REG
class hkQuaternionf
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkQuaternionf);
		HK_DECLARE_POD_TYPE();

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
			/// Empty constructor.
		HK_FORCE_INLINE hkQuaternionf() { }

			/// Constructs a quaternion directly from its component elements.
			/// The imaginary part is (ix,iy,iz) and the real part r.
		HK_FORCE_INLINE hkQuaternionf(hkFloat32 ix, hkFloat32 iy, hkFloat32 iz, hkFloat32 r);
		HK_FORCE_INLINE hkQuaternionf(hkSimdFloat32Parameter ix, hkSimdFloat32Parameter iy, hkSimdFloat32Parameter iz, hkSimdFloat32Parameter r);

			/// Constructs a quaternion from the rotation matrix r.
		explicit HK_FORCE_INLINE hkQuaternionf(const hkRotationf& r);

			/// Constructs a quaternion from an axis and an angle. The rotation
			/// will take place about that axis by angle radians.
			/// N.B. The axis MUST be normalized.
		HK_FORCE_INLINE hkQuaternionf(hkVector4fParameter axis, hkFloat32 angle);
#endif

			/// Copy this quaternion.
		HK_FORCE_INLINE void operator= (const hkQuaternionf& q);

			/// Set this quaternion with imaginary part (ix,iy,iz) and real part r.
		HK_FORCE_INLINE void set(hkFloat32 ix, hkFloat32 iy, hkFloat32 iz, hkFloat32 r);
		HK_FORCE_INLINE void set(hkSimdFloat32Parameter ix, hkSimdFloat32Parameter iy, hkSimdFloat32Parameter iz, hkSimdFloat32Parameter r);

			/// Get a reference to an identity quaternion.
			/// Note that setIdentity will likely be faster as it does not incur a memory access.
		HK_FORCE_INLINE static const hkQuaternionf& HK_CALL getIdentity();

			/// Sets this quaternion to the unit quaternion. (this = (0, 0, 0, 1))
		HK_FORCE_INLINE void setIdentity();

			/// Sets this quaternion to be the inverse of the quaternion q. (this = q^-1)
		HK_FORCE_INLINE void setInverse( hkQuaternionfParameter q );



			/// Sets this quaternion to the product of r by q. (this = r * q)
		HK_FORCE_INLINE void setMul(hkSimdFloat32Parameter r, hkQuaternionfParameter q);
			/// Adds the product of r and q to this quaternion. (this += r * q)
		HK_FORCE_INLINE void addMul(hkSimdFloat32Parameter r, hkQuaternionfParameter q);
			/// Sets this quaternion to the product of q0 and q1. (this = q0 * q1)
		HK_FORCE_INLINE void setMul(hkQuaternionfParameter q0, hkQuaternionfParameter q1);
			/// Multiplies this quaternion by q. (this *= q)
		HK_FORCE_INLINE void mul(hkQuaternionfParameter q);

			/// Set this quaternion to be the product of q0 and the inverse of q1.
			/// (this = (q0 * q1^-1)
		HK_FORCE_INLINE void setMulInverse(hkQuaternionfParameter q0, hkQuaternionfParameter q1);

			/// Set this quaternion to be the product of inverse q0 and q1.
			/// (this = (q0^-1 * q1)
		HK_FORCE_INLINE void setInverseMul(hkQuaternionfParameter q0, hkQuaternionfParameter q1);

			/// returns an estimate for an angle to get from 'this' to 'to'.
			/// This function has a pretty good accuracy for angles less than 20 degrees
			/// and underestimates the angle for bigger values.
		HK_FORCE_INLINE void estimateAngleTo(hkQuaternionfParameter to, hkVector4f& angleOut) const;

			/// Sets/initializes this quaternion given a rotation axis and angle.
			/// N.B. The axis MUST be normalized.
		void setAxisAngle(hkVector4fParameter axis, hkFloat32 angle);
		void setAxisAngle(hkVector4fParameter axis, hkSimdFloat32Parameter angle);
		void setAxisAngle_Approximate(hkVector4fParameter axis, hkSimdFloat32Parameter angle);

			/// Sets self to a rotation around the given Euler angles, assuming the angles are in radians.
		void setFromEulerAngles(hkFloat32 roll, hkFloat32 pitch, hkFloat32 yaw);
		void setFromEulerAngles(hkSimdFloat32Parameter roll, hkSimdFloat32Parameter pitch, hkSimdFloat32Parameter yaw);
		void setFromEulerAngles_Approximate(hkSimdFloat32Parameter roll, hkSimdFloat32Parameter pitch, hkSimdFloat32Parameter yaw);

			/// Sets/initializes this quaternion from a given rotation matrix.
			/// The rotation r must be orthonormal.
		void set(const hkRotationf& r);

			/// HK_FORCE_INLINEd. Sets/initializes this quaternion from a given rotation matrix.
			/// The rotation r must be orthonormal.
		HK_FORCE_INLINE void _set(const hkRotationf& r);

			/// Removes the component of this quaternion that represents a rotation (twist) around the given axis.
			/// In more accurate terms, it converts this quaternion (q) to the smallest (smallest angle)
			/// rotation (q') that still satisfies q * axis = q' * axis.
			/// This is done by applying calculating axis' = q * axis. Then, from axis and axis' a perpendicular
			/// vector (v) is calculated, as well as the angle between axis and axis' (ang). The result of the
			/// operation is the rotation specified by the angle (ang) and the axis (v).
		void removeAxisComponent (hkVector4fParameter axis);
	
			/// Decomposes the quaternion and returns the amount of rotation around the given axis, and the rest
			/// (this) == Quaternion(axis, angle) * rest , where "rest" is the rest of rotation. This is done
			/// by calculating "rest" using removeAxisComponent() and then calculating (axis,angle) as
			/// this * inv (rest).
		
		void decomposeRestAxis (hkVector4fParameter axis, hkQuaternionf& restOut, hkSimdFloat32& angleOut) const;

			/// Calculates the spherical linear interpolation between q0 and q1
			/// parameterized by t. If t is 0 then the result will be q0.
		void setSlerp(hkQuaternionfParameter q0, hkQuaternionfParameter q1, hkSimdFloat32Parameter t);
				
			/// Calculates the barycentric interpolation between qVerts = { q0, q1, q2 }. The barycentric coordinates are vLambda = [l0, l1, l2].
		void setBarycentric(const hkQuaternionf* HK_RESTRICT qVerts, hkVector4fParameter vLambda);
		
		/* access access */

			/// Sets the real component of this quaternion.
		HK_FORCE_INLINE void setReal(hkFloat32 r);
			/// Returns the real component of this quaternion.
		HK_FORCE_INLINE hkFloat32 getReal() const;

		HK_FORCE_INLINE const hkSimdFloat32 getRealPart() const;
		HK_FORCE_INLINE void setRealPart(hkSimdFloat32Parameter r);

			/// Sets the imaginary component of this quaternion.
		HK_FORCE_INLINE void setImag(hkVector4fParameter i);
			/// Returns a read only reference to the imaginary component of this quaternion.
		HK_FORCE_INLINE const hkVector4f& getImag() const;

			/// This method extracts the angle of rotation, always returning it as a real in
			/// the range [0,PI].
			/// NOTE - The standard mathematical convention is followed, with the angle taken to be
			/// such that Quaternion((0,0,1), PI/2,) will rotate the X vector (1,0,0) to the Y vector (0,0,1).
			/// If you are converting to/from a system where such a quaternion would rotate X to -Y,
			/// then you will need to flip the angle or axis to convert successfully.
			/// \code
			/// hkQuaternionf q((1,0,0), -0.7);
			/// hkFloat32 ang = q.getAngle() ;
			/// // ang is now 0.7 radians (and a call to getAxis() will return (-1,0,0) )
			/// \endcode
		HK_FORCE_INLINE hkFloat32 getAngle() const;

			/// Return the normalized axis of rotation IF DEFINED.
			/// The axis is not defined for a zero rotation (getAngle() returns 0.0f, or getReal() returns 1 or -1).
			/// The direction of the axis is determined by the sign of the angle returned by getAngle(), so that
			/// getAxis() and getAngle() return consistent values. N.B. getAngle() always returns a *positive* value.
			///
			/// NOTE - The standard mathematical convention is followed, with the angle taken to be
			/// such that Quaternion((0,0,1), PI/2) will rotate the X vector (1,0,0) to the Y vector (0,0,1).
			/// If you are converting to/from a system where such a quaternion would rotate X to -Y,
			/// then you will need to flip the angle or axis to convert successfully.
			///
			/// NOTE - getAxis() returns a valid value ONLY if the angle of the rotation
			/// is (numerically) nonzero, since the axis is undefined for a rotation of zero degrees
			/// and it is not possible to return it even if the Quaternion was created
			/// from an angle and axis. It was decided that returning an arbitrary
			/// axis would be confusing, so it is up to the user to check that the
			/// stored axis is nonzero before attempting to get the axis.
			/// Otherwise, a division by zero will occur. The function hasValidAxis()
			/// may be called to determine if calls to getAxis() will return a valid vector.
			/// e.g., hkQuaternionf((1,0,0), 1.5 PI) will return:
			///     - 0.5 PI as angle
			///     - (-1,0,0) as axis.
		HK_FORCE_INLINE void getAxis(hkVector4f &axis) const;

			/// Determines if the quaternion has a valid axis of rotation. See getAxis()
		HK_FORCE_INLINE hkBool32 hasValidAxis() const;

			/// Read only access to the i'th component of this quaternion. (stored as (ix,iy,iz,real))
		HK_FORCE_INLINE const hkFloat32& operator()(int i) const;
		template <int I> HK_FORCE_INLINE const hkSimdFloat32 getComponent() const;

			/// Checks that all elements are valid numbers, and length is 1 (within \a epsilon)
		hkBool32 isOk(const hkFloat32 epsilon = hkFloat32(1e-3f)) const;

			/// Sets the quaternion to the given quaternion q, eventually transforming it so q and qReference are in the same hemisphere
		HK_FORCE_INLINE void setClosest(hkQuaternionfParameter q, hkQuaternionfParameter qReference);

			/// Set self to a quaternion with an axis perpendicular to \a from and no rotation angle.
		void setFlippedRotation(hkVector4fParameter from);

			/// Normalizes the quaternion. (this = q/|q|)
		HK_FORCE_INLINE void normalize();

			/// Sets/initializes this quaternion from a given rotation matrix.
		HK_FORCE_INLINE void setAndNormalize(const hkRotationf& r);

		//
		// advanced interface
		//

			/// Normalizes the quaternion. (this = q/|q|)
		template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void normalize();

			/// Sets/initializes this quaternion from a given rotation matrix.
		template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void setAndNormalize(const hkRotationf& r);

	public:

		hkVector4f m_vec;
};


#endif //HK_MATH_QUATERNIONf_H

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
