/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_AERODYNAMICS_ACTION2_H
#define HK_AERODYNAMICS_ACTION2_H

#include <Physics2012/Dynamics/Action/hkpUnaryAction.h>
#include <Physics2012/Dynamics/Action/hkpArrayAction.h>

#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Utilities/Actions/Wind/hkpWind.h>

/// This action applies wind to a single entity.
class hkpWindAction : public hkpUnaryAction
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
			/// Constructor
			/// \param body the rigid body this action applies to.
			/// \param wind the wind managed by this action.
			/// \param resistanceFactor amount of wind due to rigid body's motion.
			/// \param useObb use an oriented bounding box to estimate wind on a convex vertices shapes.
			/// A relFactor of 1.0f applies the same amount of resistance as would be caused by the equivalent wind.
		hkpWindAction( hkpRigidBody* body, const hkpWind* wind, hkReal resistanceFactor, hkReal obbFactor = 0.0f );

			/// Apply the action to the rigid body. Called every simulation step.
		virtual void applyAction( const hkStepInfo& stepInfo );

			/// hkpAction clone interface.
		virtual hkpAction* clone( const hkArray<hkpEntity*>& newEntities, const hkArray<hkpPhantom*>& newPhantoms ) const;

			/// Destructor.
		virtual ~hkpWindAction();

	private:
			/// The wind.
		const hkpWind* m_wind;
			/// Amount of wind due to the body's motion.
			/// A scaling factor of 1.0f applies the same amount of resistance as would be due to the equivalent wind.
		const hkReal m_resistanceFactor;
			/// Use an oriented bounding box in place of the full calculation for convex vertices shapes.
		const hkReal m_obbFactor;
};

#endif // HK_AERODYNAMICS_ACTION2_H

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
