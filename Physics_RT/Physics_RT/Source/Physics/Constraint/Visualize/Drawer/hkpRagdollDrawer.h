/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_RAGDOLLDRAWER_H
#define HKP_RAGDOLLDRAWER_H

#include <Physics/Constraint/Visualize/Drawer/hkpConstraintDrawer.h>
#include <Common/Visualize/Shape/hkDisplayCone.h>
#include <Common/Visualize/Shape/hkDisplayPlane.h>
#include <Physics/Constraint/Data/Ragdoll/hkpRagdollConstraintData.h>


/// Displays information about the ballSocket constraint.
class hkpRagdollDrawer : public hkpConstraintDrawer
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HKP_MEMORY_CLASS_VDB, hkpRagdollDrawer );

		void drawConstraint(const hkpRagdollConstraintData* constraintData,
			const hkTransform& localToWorldA, const hkTransform& localToWorldB,
			hkDebugDisplayHandler* displayHandler, int id, int tag);

	protected:

		hkDisplayCone m_twistCone;
		hkDisplayCone m_planeCone1;
		hkDisplayCone m_planeCone2;
		hkDisplayPlane m_plane;
};


#endif	// HKP_RAGDOLLDRAWER_H

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
