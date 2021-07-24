/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKVEHICLE_EXTERNALCONTROLLERS_ANGULARVELOCITYDAMPER_hkVehicleDefaultVelocityDamper_XML_H
#define HKVEHICLE_EXTERNALCONTROLLERS_ANGULARVELOCITYDAMPER_hkVehicleDefaultVelocityDamper_XML_H

#include <Physics2012/Vehicle/VelocityDamper/hkpVehicleVelocityDamper.h>

extern const class hkClass hkpVehicleDefaultVelocityDamperClass;

/// An angular velocity damper which reduces a vehicle's ability to spin in the air,
/// making it more stable.
class hkpVehicleDefaultVelocityDamper : public hkpVehicleVelocityDamper
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

			/// Default constructor
		hkpVehicleDefaultVelocityDamper();
		
		//
		// Methods
		//
		
			/// This controller dampens the vehicle angular velocity.
		virtual void applyVelocityDamping(const hkReal deltaTime, hkpVehicleInstance& vehicle);
		
		//
		// Members
		//
	public:
		
			/// A damping of the chassis angular velocity in normal mode
		hkReal m_normalSpinDamping;
		
			/// A damping of the chassis angular velocity in collision mode.
		hkReal m_collisionSpinDamping;
		
			/// If the chassis angular velocity is higher than this value, the engine assumes
			/// collision.
		hkReal m_collisionThreshold;

	public:

		hkpVehicleDefaultVelocityDamper(hkFinishLoadedObjectFlag f) : hkpVehicleVelocityDamper(f) { }

};

#endif // HKVEHICLE_EXTERNALCONTROLLERS_ANGULARVELOCITYDAMPER_hkVehicleDefaultVelocityDamper_XML_H

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
