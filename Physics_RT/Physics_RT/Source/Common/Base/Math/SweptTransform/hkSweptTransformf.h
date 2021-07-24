/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_SWEPTTRANSFORMf_H
#define HK_MATH_SWEPTTRANSFORMf_H


extern const class hkClass hkSweptTransformClass;

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

	/// Represents a rotation and translation over time.
	/// It basically stores the position of the mass center and the rotation at
	/// two physics frames. In addition to this it also stores the time of those
	/// frames and the center of mass in local space.
	/// With that information, it is easy to interpolate the position between the
	/// two frames.
	/// See hkSweptTransformfUtil for more functions.
class hkSweptTransformf
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkSweptTransformf);

			/// Default constructor - all elements are uninitialized. Use hkSweptTransformf::initSweptTransform() to initialize
		HK_FORCE_INLINE hkSweptTransformf() { }

	public:
			/// inline version of approxTransformAt
		HK_FORCE_INLINE void _approxTransformAt( hkTime time, hkTransformf& transformOut ) const;
		HK_FORCE_INLINE void _approxTransformAt( hkSimdFloat32Parameter time, hkTransformf& transformOut ) const;


			/// Approximate a transform for any given time T.
			/// If T is between t0 and t1 of the motion state than the algorithm is doing in interpolation
			/// otherwise the result is an extrapolation.
			/// Note: This function works has a lower accuracy than hkSweptTransformfUtil::lerp2 as used by Havok's collision detection
		void approxTransformAt( hkTime time, hkTransformf& transformOut ) const;
		void approxTransformAt( hkSimdFloat32Parameter time, hkTransformf& transformOut ) const;


			/// get an interpolation value from a given time
		HK_FORCE_INLINE hkFloat32 getInterpolationValue( hkTime t ) const;
		HK_FORCE_INLINE hkSimdFloat32 getInterpolationValue( hkSimdFloat32Parameter t ) const;

			// get an interpolation value from a given time= t+deltaTimeAddon. This has a higher precision than getInterpolationValue
		HK_FORCE_INLINE hkFloat32 getInterpolationValueHiAccuracy( hkTime t, hkFloat32 deltaTimeAddon ) const;
		HK_FORCE_INLINE hkSimdFloat32 getInterpolationValueHiAccuracy( hkSimdFloat32Parameter t, hkSimdFloat32Parameter deltaTimeAddon ) const;

			/// Get time0
		HK_FORCE_INLINE hkTime getBaseTime() const;
		HK_FORCE_INLINE hkSimdFloat32 getBaseTimeSr() const;

			/// Get 1.0f/(time1-time0) if the object is active
			/// (actually if it has been integrated since its activation, addition to hkpWorld, or
			/// motion type change)
			/// else 0.0f
		HK_FORCE_INLINE hkFloat32 getInvDeltaTime() const;
		HK_FORCE_INLINE hkSimdFloat32 getInvDeltaTimeSr() const;

			/// Initialized this class given a position and a rotation
		void initSweptTransform( hkVector4fParameter position, hkQuaternionfParameter rotation );

	public:
			/// the position of the rotational center at t0 in world space. Note: the w component is used to store time 0
		hkVector4f m_centerOfMass0;		

			/// the position of the rotational center at t1 in world space.
			/// Note:
			///  - If the object is moving active, the w component is used to store 1.0f/(time1 - time0)
			///  - If the object is fixed or deactivated, the w component is set to 0.0f
		hkVector4f m_centerOfMass1;

			/// the orientation at t0
		hkQuaternionf m_rotation0;

			/// the orientation at t1
		hkQuaternionf m_rotation1;

			/// the rotational center = e.g., the center of mass) in local space
			/// the .w component should be set to 0 if the center is 0 (allows for some platform optimizations)
			/// and set to !=0 if the center is != 0
		hkVector4f m_centerOfMassLocal;
};
#include <Common/Base/Math/SweptTransform/hkSweptTransformf.inl>

#endif //HK_MATH_SWEPTTRANSFORMf_H

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
