/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKB_MOVE_CHARACTER_MODIFIER_H
#define HKB_MOVE_CHARACTER_MODIFIER_H

#include <Behavior/Behavior/Modifier/hkbModifier.h>

extern const class hkClass hkbMoveCharacterModifierClass;

/// A modifier that moves the character position by a constant offset per unit time.
class hkbMoveCharacterModifier : public hkbModifier
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BEHAVIOR );
		HK_DECLARE_REFLECTION();

		hkbMoveCharacterModifier();
		hkbMoveCharacterModifier( const hkbMoveCharacterModifier& );

		//////////////////////
		// hkbNode interface 
		//////////////////////

			// hkbNode interface implementation.
		virtual void activate( const hkbContext& context ) HK_OVERRIDE;

			// hkbNode interface implementation.
		virtual void update( const hkbContext& context, hkReal timestep ) HK_OVERRIDE;

			// hkbNode interface implementation.
		virtual hkbNode* cloneNode( hkbBehaviorGraph& rootBehavior ) const HK_OVERRIDE;

		//////////////////////////
		// hkbModifier interface
		//////////////////////////

			// hkbModifier interface implementation
		virtual void modify( const hkbContext& context, hkbGeneratorOutput& inOut ) HK_OVERRIDE;

			// hkbModifier interface implementation
		virtual void predictiveModify( const hkbContext& context, hkbGeneratorOutput& inOut, hkReal timeOffset ) HK_OVERRIDE;

		///////////////
		// properties
		///////////////

			/// The offset to move the character per second, in model space.
		hkVector4 m_offsetPerSecondMS; //+default(0,0,0)+hk.Description("The offset to move the character per second, in model space.")

	private:

		HKB_BEGIN_INTERNAL_STATE(0);

		hkReal m_timeSinceLastModify; //+nosave

		HKB_END_INTERNAL_STATE();

	public:

		hkbMoveCharacterModifier( hkFinishLoadedObjectFlag flag );

		friend class hkbMoveCharacterModifierUtils;

};

#endif

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
