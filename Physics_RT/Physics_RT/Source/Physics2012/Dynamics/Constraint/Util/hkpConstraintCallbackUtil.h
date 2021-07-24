/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONSTRAINT_CALLBACK_UTIL_H
#define HKP_CONSTRAINT_CALLBACK_UTIL_H

class hkpConstraint;
struct hkpContactPointAddedEvent;
struct hkpContactPointConfirmedEvent;
struct hkpContactPointRemovedEvent;
struct hkpContactProcessEvent;

#include <Physics2012/Dynamics/Constraint/hkpConstraintListener.h>


class hkpConstraintCallbackUtil
{
	public:
			/// go through both, the Constraint and the collision listeners
		static void HK_CALL fireConstraintAdded(   hkpConstraintInstance* constraint );
		static void HK_CALL fireConstraintRemoved( hkpConstraintInstance* constraint );
		static void HK_CALL fireConstraintDeleted( hkpConstraintInstance* constraint );
		static void HK_CALL fireConstraintBroken  (  const hkpConstraintBrokenEvent& event ) ;
		static void HK_CALL fireConstraintRepaired(  const hkpConstraintRepairedEvent& event ) ;
};

#endif // HKP_CONSTRAINT_CALLBACK_UTIL_H

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
