/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKVEHICLE_TRANSMISSION_DEFAULT_hkVehicleDefaultTransmission_XML_H
#define HKVEHICLE_TRANSMISSION_DEFAULT_hkVehicleDefaultTransmission_XML_H

#include <Physics2012/Vehicle/Transmission/hkpVehicleTransmission.h>

extern const class hkClass hkpVehicleDefaultTransmissionClass;

/// The hkpVehicleDefaultTransmission class implements an automatic transmission, with n
/// gears and a reverse gear, different torque ratios for each wheel (so FWD - RWD -
/// AWD can be specified) and clutch delay.
class hkpVehicleDefaultTransmission : public hkpVehicleTransmission
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();
	
			/// Default constructor
		hkpVehicleDefaultTransmission();
		
		//
		// Methods
		//
		
			/// Calculates information about the effects of transmission on the vehicle.
		virtual void calcTransmission(const hkReal deltaTime, const hkpVehicleInstance* vehicle, TransmissionOutput& TransmissionOutputOut);
		

			/// A utility function to calculate the primaryTransmissionRatio for a vehicle. The answer
			/// returned is intended only as a guideline. It will probably need to be tweaked a little
			/// to give the exact desired performance. See the "Tuning tips" of the Havok User Guide
			/// for more details.
			/// The formula is copied here:
			///  - TopSpeedCar[m/s] = vehicleTopSpeedMPH * 1.609 / 3.6
			///  - MaxWheelAngularVel = TopSpeedCar[m/s] / wheelRadius
			///  - MaxWheelRPM = MaxWheelAngularVel * 60 / 2 * PI
			///  - PrimirayTransmissionRatio = maxEngineRPM / MaxWheelRPM
		static hkReal HK_CALL calculatePrimaryTransmissionRatio( const hkReal vehicleTopSpeedMPH,
																	const hkReal wheelRadius,
																	const hkReal maxEngineRpm,
																	const hkReal topGearRatio );

			/// A utility function to calculate the primaryTransmissionRatio for a vehicle. This overloads
			/// converts the vehicle top speed to MPH and then calls the calculatePrimaryTransmissionRatio. 
			/// The answer returned is intended only as a guideline. Tweak calculatePrimaryTransmissionRatio
			/// (not this function) to give the exact desired performance. 
			/// See the "Tuning tips" of the Havok User Guide for more details.
			/// The formula is copied here:
			///  - vehicleTopSpeedMPH = vehicleTopSpeedKPH * 0.621f
			///  - [km/hr]*[1000m/km]*[100cm/m]*[1in/2.54cm]*[1ft/12in]*[1mi/5280ft] = 0.621f [mi/hr]
			/// 
			/// The rest proceeds as in calculatePrimaryTransmissionRatio.
		static hkReal HK_CALL calculatePrimaryTransmissionRatioKPH( const hkReal vehicleTopSpeedKPH, 
																	const hkReal wheelRadius, 
																	const hkReal maxEngineRpm,
																	const hkReal topGearRatio );	
		
		//
		// The following functions are all used by calcTransmission.
		//
	public:
			/// Calculates the transmitted torque.
		virtual hkReal calcMainTransmittedTorque(const hkpVehicleInstance* vehicle, TransmissionOutput& transmissionOut) const;
		
			/// Calculates the transmission RPM.
		virtual hkReal calcTransmissionRPM(const hkpVehicleInstance* vehicle, TransmissionOutput& transmissionOut) const;
		
			/// Calculates if the vehicle is currently reversing.
		virtual hkBool calcIsReversing(const hkpVehicleInstance* vehicle, TransmissionOutput& transmissionOut) const;
		
			/// Calculates the current gear.
		virtual void updateCurrentGear( const hkReal deltaTime, const hkpVehicleInstance* vehicle, TransmissionOutput& transmissionOut );
		
			/// Returns the gear ratio of the current gear.
		virtual hkReal getCurrentRatio(const hkpVehicleInstance* vehicle, TransmissionOutput& transmissionOut) const;
		
		//
		// Members
		//
	public:
		
			/// The RPM of the engine the transmission shifts down.
		hkReal m_downshiftRPM;
		
			/// The RPM of the engine the transmission shifts up. Note: m_upshiftRpm >
			/// m_downshiftRpm.
		hkReal m_upshiftRPM;
		
			/// An extra factor to the gear ratio.
		hkReal m_primaryTransmissionRatio;
		
			/// The time needed [seconds] to shift a gear.
		hkReal m_clutchDelayTime;
		
			/// The back gear ratio.
		hkReal m_reverseGearRatio;
		
			/// The ratio of the forward gears.
		hkArray<hkReal> m_gearsRatio;
		
			/// The transmission ratio for every wheel
		hkArray<hkReal> m_wheelsTorqueRatio;

	protected:
	#if defined HK_DEBUG
			// Check that the sum of all the wheel torque ratios equals 1.0f. Fire a warning if it does not.
		void checkTotalWheelTorqueRatio( const hkpVehicleInstance* vehicle ) const;
	#endif // #if defined HK_DEBUG

	public:
		hkpVehicleDefaultTransmission(hkFinishLoadedObjectFlag f) :
			hkpVehicleTransmission(f), m_gearsRatio(f), m_wheelsTorqueRatio(f) { }
};

#endif // HKVEHICLE_TRANSMISSION_DEFAULT_hkVehicleDefaultTransmission_XML_H

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
