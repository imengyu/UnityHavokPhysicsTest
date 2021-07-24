/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_POSITION_CONSTRAINT_MOTOR_H
#define HKP_POSITION_CONSTRAINT_MOTOR_H

#include <Physics/Constraint/Motor/LimitedForce/hkpLimitedForceConstraintMotor.h>

extern const hkClass hkpPositionConstraintMotorClass;


/// A motor which tries to reach a desired position/angle given a maxForce and a recovery speed.
/// Notes:
///  - this motor is a good choice for driving a ragdoll to a given pose.
///  - This motor accumulates the error over time to be able to achieve high forces.
///    This can lead to a small jitter, the first time the motor is activated.
///    To reduce this jitter, you can either try to fade in the motor's maxForce or
///    set the maxForce to some reasonable value.
class hkpPositionConstraintMotor : public hkpLimitedForceConstraintMotor
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT );
		HK_DECLARE_REFLECTION();

		/// Sets some reasonable default values.
		hkpPositionConstraintMotor( hkReal currentPosition = 0.0f);

		/// Serialization constructor.
		hkpPositionConstraintMotor( hkFinishLoadedObjectFlag f ) : hkpLimitedForceConstraintMotor(f) {}

		/// Motor clone method.
		virtual hkpConstraintMotor* clone() const;

	public:

		/// The relative stiffness between 0 and 1.
		hkReal m_tau;

		/// The relative damping between 0 and 1.
		hkReal m_damping;

		/// A factor of the current error to calculate the recovery velocity.
		hkReal m_proportionalRecoveryVelocity;

		/// A constant velocity which is used to recover from errors.
		hkReal m_constantRecoveryVelocity;
};


#endif // HKP_POSITION_CONSTRAINT_MOTOR_H

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
