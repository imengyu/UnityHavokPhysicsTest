/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKBASEOBJECT_H
#define HKBASE_HKBASEOBJECT_H

extern const hkClass hkBaseObjectClass;

/// Base class for all Havok classes that have virtual functions.
/// In gcc2 for instance, if the virtual base class has data in it the vtable
/// is placed after the data, whereas most other compilers always have the vtable
/// at the start. Thus we have an empty virtual base class to force the vtable
/// to always be at the start of the derived objects.
/// All Havok managed objects inherit from a sub class of this, hkReferencedObject
/// that stores the memory size and the reference count info (if used).
class hkBaseObject
{
		//+hk.ReflectedFile("BaseObject")
		//+hk.MemoryTracker(ignore=True)
	public:
		HK_DECLARE_REFLECTION();
		HK_DECLARE_PLACEMENT_ALLOCATOR();
		
			/// Virtual destructor for derived objects
		HK_FORCE_INLINE HK_NOSPU_VIRTUAL ~hkBaseObject() {}

	public:
		
		HK_FORCE_INLINE hkBaseObject( class hkFinishLoadedObjectFlag flag ) {}

	public:

			// Dummy virtual function, to ensure we have a proper vtable layout on both PPU and SPU
		virtual void __first_virtual_table_function__() {}

	protected:

		// Protected constructor to make sure this class is only instantiated through the serialization constructor or derived classes
		HK_FORCE_INLINE hkBaseObject() {}
};

hkBool::CompileTimeFalseType hkIsVirtual(void*);
hkBool::CompileTimeTrueType hkIsVirtual(hkBaseObject*);

#endif // HKBASE_HKBASEOBJECT_H

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
