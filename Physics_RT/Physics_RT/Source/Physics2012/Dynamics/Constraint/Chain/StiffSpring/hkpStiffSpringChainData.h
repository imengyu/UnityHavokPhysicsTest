/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_STIFF_SPRING_CHAIN_H
#define HK_DYNAMICS2_STIFF_SPRING_CHAIN_H

#include <Physics/ConstraintSolver/Solve/hkpSolverResults.h>
#include <Physics/Constraint/Atom/Bridge/hkpBridgeConstraintAtom.h>
#include <Physics2012/Dynamics/Constraint/Chain/hkpConstraintChainData.h>
#include <Physics2012/Dynamics/Action/hkpArrayAction.h>

extern const class hkClass hkpStiffSpringChainDataConstraintInfoClass;
extern const class hkClass hkpStiffSpringChainDataClass;


	/// A chain of stiff springs
class hkpStiffSpringChainData : public hkpConstraintChainData
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT ); // and action too
		
		hkpStiffSpringChainData();

		~hkpStiffSpringChainData();

			/// Not implemented. Returns always true.
		hkBool isValid() const { return true; }

			/// Get type from this constraint
		virtual int getType() const;

			/// Returns the number of stored constraint infos.
		virtual int getNumConstraintInfos() { return m_infos.getSize(); }
		
			/// Adds a constraint info to the chain.
			/// Pivot points are specified in the local space of the bodies.
			/// Spring length must be supplied.
		void addConstraintInfoInBodySpace(const hkVector4& pivotInA, const hkVector4& pivotInB, hkReal springLength);

	public:

		struct Runtime
		{
				/// Runtime only stores solver results. The number of solver results is (hkpStiffSpringConstraintData::SOLVER_RESULT_MAX * getNumConstraintInfos()
				/// == 1 * getNumConstraintInfos()).
				/// Note: when the instance uses less constraints than there are constraintInfos, then the hkpSolverResults at the end of the array are uninitialized.
			inline const hkpSolverResults* getSolverResults() { return reinterpret_cast<hkpSolverResults*>(this); }
		};

		inline const Runtime* getRuntime( hkpConstraintRuntime* runtime )
		{ 
			return reinterpret_cast<Runtime*>(runtime); 
		}
				

	public:

		//
		// Internal functions
		//

			/// Interface implementation.
		virtual void buildJacobian( const hkpConstraintQueryIn &in, hkpConstraintQueryOut &out );

			/// Interface implementation.
		virtual void getConstraintInfo( hkpConstraintData::ConstraintInfo& info ) const;

			/// Interface implementation.
		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;

	public:

			/// Serialization ctor.
		hkpStiffSpringChainData(hkFinishLoadedObjectFlag f);

	public:


		struct hkpBridgeAtoms m_atoms;

			/// This structure holds information needed for an individual constraint in the chain.
		struct ConstraintInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpStiffSpringChainData::ConstraintInfo );
			HK_DECLARE_REFLECTION();

				/// Constraint's pivot point in bodyA's space.
			hkVector4 m_pivotInA;

				/// Constraint's pivot point in bodyB's space.
			hkVector4 m_pivotInB;

				/// Requested distance between the pivot points of the two bodies. It is advised to specify a non-zero value, otherwise the constraint is instable.
			hkReal m_springLength;
		};

			/// Constraint infos for the chain's constraints.
		hkArray<struct ConstraintInfo> m_infos;

			/// Solver tau, this overrides the global value from hkpSolverInfo when processing the chained constraints.
		hkReal m_tau;

			/// Solver damping, this overrides the global value from hkpSolverInfo when processing the chained constraints.
		hkReal m_damping;

			/// Constraint force mixing parameter. Value added to the diagonal of the constraint matrix.
			/// Should be zero or tiny, e.g., a fraction of HK_REAL_EPSILON. When this value is zero, then some chain configurations
			/// may result in a division by zero when solving.
		hkReal m_cfm;
};


#endif // HK_DYNAMICS2_STIFF_SPRING_CHAIN_H

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
