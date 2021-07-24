/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_WORLD_CONSTRAINT_UTIL_H
#define HK_DYNAMICS2_WORLD_CONSTRAINT_UTIL_H

#include <Physics2012/Dynamics/Constraint/Atom/hkpSimpleContactConstraintAtom.h>

class hkpConstraintInstance;
class hkpEntity;
class hkpWorld;
struct hkpModifierConstraintAtom;

/// Class hkpWorldConstraintUtil
class hkpWorldConstraintUtil
{
	public:
			/// ###ACCESS_CHECKS###( [world,HK_ACCESS_RO] [constraint->m_entities[0]->getSimulationIsland(),HK_ACCESS_RW] [constraint->m_entities[1]->getSimulationIsland(),HK_ACCESS_RW] );
		static void                      HK_CALL addConstraint( hkpWorld* world, hkpConstraintInstance* constraint );

			/// removes the constraint and deletes all attached modifiers.
			/// ###ACCESS_CHECKS###( [world,HK_ACCESS_RO] [constraint->m_entities[0]->getSimulationIsland(),HK_ACCESS_RW] [constraint->m_entities[1]->getSimulationIsland(),HK_ACCESS_RW] [island->m_world,HK_ACCESS_RO] [island,HK_ACCESS_RW] );
		static void                      HK_CALL removeConstraint( hkpConstraintInstance* constraint );
			/// ###ACCESS_CHECKS###( [world,HK_ACCESS_IGNORE] [entityA->getSimulationIsland(),HK_ACCESS_RO] [entityB->getSimulationIsland(),HK_ACCESS_RO] );
		static hkpConstraintInstance*     HK_CALL getConstraint( const hkpEntity* entityA, const hkpEntity* entityB);

		static void                      HK_CALL addModifier             ( hkpConstraintInstance* instance, hkpConstraintOwner& constraintOwner, hkpModifierConstraintAtom* s );
		static void                      HK_CALL removeAndDeleteModifier          ( hkpConstraintInstance* instance, hkpConstraintOwner& constraintOwner, hkpConstraintAtom::AtomType type );
			/// ###ACCESS_CHECKS###( [world,HK_ACCESS_RO] [instance->getSimulationIsland(),HK_ACCESS_RO] );
		static hkpModifierConstraintAtom* HK_CALL findModifier            ( hkpConstraintInstance* instance, hkpConstraintAtom::AtomType type );
			/// ###ACCESS_CHECKS###( [world,HK_ACCESS_RO] [instance->getSimulationIsland(),HK_ACCESS_RO] );
		static hkpModifierConstraintAtom* HK_CALL findLastModifier        ( hkpConstraintInstance* instance );
		static void                      HK_CALL updateFatherOfMovedAtom ( hkpConstraintInstance* instance, const hkpConstraintAtom* oldAtom, const hkpConstraintAtom* updatedAtom, int updatedSizeOfAtom );
		HK_FORCE_INLINE static hkpConstraintAtom* HK_CALL getTerminalAtom (const hkConstraintInternal* cInternal);
};

#include <Physics2012/Dynamics/World/Util/hkpWorldConstraintUtil.inl>

#endif // HK_DYNAMICS2_WORLD_CONSTRAINT_UTIL_H

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
