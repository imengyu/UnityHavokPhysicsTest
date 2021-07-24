/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKVEHICLE_BRAKE_hkVehicleBRAKE_XML_H
#define HKVEHICLE_BRAKE_hkVehicleBRAKE_XML_H

#include <Physics2012/Vehicle/DriverInput/hkpVehicleDriverInput.h>

extern const class hkClass hkpVehicleBrakeClass;

class hkpVehicleInstance;

/// This component manages the state of torques applied by the vehicle brakes, and
/// the blocking of wheels e.g., due to handbraking or strong braking being
/// applied.
class hkpVehicleBrake : public hkReferencedObject
{
	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_VEHICLE);
		HK_DECLARE_REFLECTION();

			/// Container for data output by the brake calculations.
		struct WheelBreakingOutput
		{
			public:
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_VEHICLE, hkpVehicleBrake::WheelBreakingOutput );

				/// The breaking torque of the wheel.
			hkInplaceArray< hkReal, 32 > m_brakingTorque;

				/// Indicates whether or not a wheel is locked.
			hkInplaceArray< hkBool, 32 > m_isFixed;

				/// Time since the torque applied was maximum. In order to implement wheel
				/// blockage warning this is a float right now, a time struct would be better
				/// because over time the accuracy will get less and less.
			hkReal m_wheelsTimeSinceMaxPedalInput;
		};

		//
		// Methods
		//
		
			/// Calculates information about the effects of braking on the vehicle.
		virtual void calcBreakingInfo(const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInput::FilteredDriverInputOutput& FilteredDriverInputOutput, WheelBreakingOutput& breakingInfo) = 0;

	public:

		hkpVehicleBrake(hkFinishLoadedObjectFlag flag) : hkReferencedObject(flag) {}

	protected:

		hkpVehicleBrake() {}
};

#endif // HKVEHICLE_BRAKE_hkVehicleBRAKE_XML_H

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
