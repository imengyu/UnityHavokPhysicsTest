/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKB_BEHAVIOR_GRAPH_STRING_DATA_H
#define HKB_BEHAVIOR_GRAPH_STRING_DATA_H


extern const class hkClass hkbBehaviorGraphStringDataClass;

/// The strings associated with a behavior.
/// 
/// These are symbol names that can be used to link the behavior
/// to characters and other behaviors using an hkbSymbolLinker.
class hkbBehaviorGraphStringData : public hkReferencedObject
{
	public:
		//+vtable(1)
		//+version(1)

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BEHAVIOR );
		HK_DECLARE_REFLECTION();

		hkbBehaviorGraphStringData() {}

			/// The names (and implicit IDs) of the events used by the behavior.
		hkArray<hkStringPtr> m_eventNames;

			/// The names (and implicit IDs) of the attributes of the behavior.
		hkArray<hkStringPtr> m_attributeNames;

			/// The names (and implicit IDs) of the variables used by the behavior.
		hkArray<hkStringPtr> m_variableNames;

			/// The names (and implicit IDs) of the character properties that this behavior requires to be linked.
		hkArray<hkStringPtr> m_characterPropertyNames;

	public:

		hkbBehaviorGraphStringData( hkFinishLoadedObjectFlag flag )
			:	hkReferencedObject(flag),
				m_eventNames(flag),
				m_attributeNames(flag),
				m_variableNames(flag),
				m_characterPropertyNames(flag) {}
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
