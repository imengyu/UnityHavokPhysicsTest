/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBP_RAGDOLL_RIGID_BODY_CONTROLLER_H
#define HKBP_RAGDOLL_RIGID_BODY_CONTROLLER_H

#include <Behavior/Utilities/Physics/Interface/hkbRagdollController.h>

class hkaRagdollRigidBodyController;
class hkbpRagdollInterface;

	/// This controller wraps an hkbpRagdollInterface and drives it by keyframing (setting velocities on) the rigid bodies.
	/// See hkaRagdollRigidBodyController and hkaKeyFrameHierarchyUtility for more information on how this is accomplished.
class hkbpRagdollRigidBodyController : public hkbRagdollController
{
	public:		
	
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BEHAVIOR );		
		
			// Ctor.
		hkbpRagdollRigidBodyController( hkbpRagdollInterface* ragdollInterface );

			// Dtor.
		virtual ~hkbpRagdollRigidBodyController();
		
			// hkbRagdollController interface.
		virtual void driveToPose(
			const struct hkbRagdollControllerData& data,
			hkReal deltaTime ) HK_OVERRIDE;

	protected:

			/// The hka controller being used to do the heavy-lifting.
		hkaRagdollRigidBodyController* m_controller;

			/// The bone weights passed into driveToPose from the previous frame.
		hkArray<hkReal> m_previousBoneWeights;
		
};

#endif // HKBP_RAGDOLL_RIGID_BODY_CONTROLLER_H

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
