/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKVEHICLE_ENGINE_hkVehicleENGINE_XML_H
#define HKVEHICLE_ENGINE_hkVehicleENGINE_XML_H


#include <Physics2012/Vehicle/DriverInput/hkpVehicleDriverInput.h>
#include <Physics2012/Vehicle/Transmission/hkpVehicleTransmission.h>

extern const class hkClass hkpVehicleEngineClass;

class hkpVehicleInstance;


/// The hkpVehicleEngine is the component responsible for calculating values
/// related to the engine of the vehicle, in particular the engine torque and RPM. A
/// typical hkpVehicleEngine implementation would collaborate with the vehicle's
/// hkpVehicleDriverInput (for the accelerator pedal input) and its
/// hkpVehicleTransmission (for RPM and torque transmission).
class hkpVehicleEngine : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_VEHICLE);
		HK_DECLARE_REFLECTION();

		/// Container for data output by the engine calculations.
		/// Note that each of these members can be accessed through
		/// the hkpVehicleInstance.
		struct EngineOutput
		{
			public:
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_VEHICLE, hkpVehicleEngine::EngineOutput );
			/// The torque currently supplied by the engine.
			hkReal m_torque;

			/// The RPM the engine is currently running at.
			hkReal m_rpm;
		};

		//
		// Methods
		//
		
			/// Sets the current values of the torque and rpm.
		virtual void calcEngineInfo(const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInput::FilteredDriverInputOutput& FilteredDriverInputOutput, const hkpVehicleTransmission::TransmissionOutput& TransmissionOutput, EngineOutput& engineOutput ) = 0;

	public:

		hkpVehicleEngine(hkFinishLoadedObjectFlag flag) : hkReferencedObject(flag) {}

	protected:

		hkpVehicleEngine() {}
};

#endif // HKVEHICLE_ENGINE_hkVehicleENGINE_XML_H

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
