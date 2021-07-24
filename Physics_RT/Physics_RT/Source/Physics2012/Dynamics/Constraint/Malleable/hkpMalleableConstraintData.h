/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_MALLEABLE_CONSTRAINT_H
#define HKP_MALLEABLE_CONSTRAINT_H

#include <Physics/Constraint/Data/hkpConstraintData.h>
#include <Physics/Constraint/Atom/Bridge/hkpBridgeConstraintAtom.h>

extern const hkClass hkpMalleableConstraintDataClass;


/// This is a wrapper class around constraints intended to allow the user to make a constraint softer.
/// Important: This malleable constraint does not affect the angular limit and angular motor components of a constraint.
class hkpMalleableConstraintData : public hkpConstraintData
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

			/// The constraint to be 'softened' should be passed in - its ref count will be incremented.
			///
			/// The malleable constraint essentially wraps another constraint. A reference
			/// is added to the constraint passed in (and removed upon destruction).
			/// NOTE: Instead of adding the original constraint to the world, you should
			/// add this malleable constraint. Do not add both constraints.
		hkpMalleableConstraintData(hkpConstraintData* constraintData);	

			/// The reference to the original constraint is removed.
		~hkpMalleableConstraintData();
	
			/// Set the strength of the contained constraint.
			/// The value should be in the range 0 (disabled) to 1 (full strength).
		void setStrength(const hkReal s);
		
			/// Get the strength value for this constraint
		hkReal getStrength() const;
		
			/// Checks consistency of constraint members
		virtual hkBool isValid() const;
		
			// hkpConstraintData interface implementation
		virtual int getType() const;
		
			// hkpConstraintData interface implementation
		virtual void getConstraintInfo( hkpConstraintData::ConstraintInfo& infoOut ) const;
	
			/// Gets the wrapped constraint
		hkpConstraintData* getWrappedConstraintData();

			/// Gets the wrapped constraint
		const hkpConstraintData* getWrappedConstraintData() const;

	protected:

			/// The wrapped constraint (referenced, so protected)
		hkpConstraintData* m_constraintData;

	public:

		struct hkpBridgeAtoms m_atoms;

		hkReal m_strength;

			// Internal functions
		virtual void buildJacobian( const hkpConstraintQueryIn &in, hkpConstraintQueryOut &out );

			// hkpConstraintData interface implementation
		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;

	public:

		hkpMalleableConstraintData(hkFinishLoadedObjectFlag f);
};


#endif // HKP_MALLEABLE_CONSTRAINT_H

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
