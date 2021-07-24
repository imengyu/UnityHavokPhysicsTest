/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_DATA_NATIVE_OBJECT
#define HK_DATA_NATIVE_OBJECT

#include <Common/Serialize/Data/hkDataObject.h>

#include <Common/Base/Reflection/hkClassMember.h>

class hkPackfileReader;
class hkPackfileData;
class hkDataClassNative;
class hkVtableClassRegistry;
class hkClassNameRegistry;
class hkTypeInfoRegistry;

	/// This class implements the native type of hkDataWorld and
	/// can be used only for read access and in-place modifications
	/// of native objects.
	/// 
	/// You also may use this class to save object contents to a tagfile
	/// with a pointer and hkClass.
class hkDataWorldNative : public hkDataWorld
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
			/// Constructor.
		hkDataWorldNative(hkBool accessSerializeIgnored = false);
			/// Destructor.
		~hkDataWorldNative();
			/// Implements hkDataWorld::getContents().
		virtual hkDataObject getContents() const;

			// Not implemented for native world.
		virtual hkDataObjectImpl* newObject(const hkDataClass& klass, bool createdDuringPatching = false) const;
			// Not implemented for native world.
		virtual hkDataClassImpl* newClass(const hkDataClass::Cinfo& cinfo);
			// Not implemented for native world.
		virtual hkDataArrayImpl* newArray(hkDataObject& obj, hkDataObject::MemberHandle handle, const hkDataClass::MemberInfo& minfo) const;

			/// Implements hkDataWorld::getType(). Return hkDataWorld::TYPE_NATIVE.
		virtual hkEnum<hkDataWorld::DataWorldType, hkInt32> getType() const;

			/// Implements hkDataWorld::findAllClasses().
		virtual void findAllClasses(hkArray<hkDataClassImpl*>::Temp& classesOut) const;
			/// Implements hkDataWorld::findClass().
		virtual hkDataClassImpl* findClass(const char* name) const;
			/// Implements hkDataWorld::findObject().
		virtual hkDataObject findObject(const hkDataObject::Handle& handle) const;
			/// Wrap native object based on the given pointer and hkClass.
		hkDataObjectImpl* wrapObject(void* object, const hkClass& klass) const;

			/// Get the type manager
		hkTypeManager& getTypeManager() { return m_typeManager; }

			/// Set top level object with the given pointer and hkClass.
			/// The hkClass must be from the set class name registry.
			/// If 'klass' is not found then the world's top level object is set to HK_NULL.
		void setContents(void* object, const hkClass& klass);
			/// Set class name registry.
			/// Classes from this registry are used to wrap and access native objects.
		void setClassRegistry(const hkClassNameRegistry* r);
			/// Set vtable registry.
			/// This registry is used to find the most-derived class when wrapping native virtual objects.
		void setVtableRegistry(const hkVtableClassRegistry* vt);

			/// Get the type
		virtual hkDataObject::Type getTypeFromMemberType(hkClassMember::Type mtype, hkClassMember::Type stype, const hkClass* klass, int count);


			// Used internally.
		hkRefPtr<const hkClassNameRegistry> m_reg;
		hkRefPtr<const hkVtableClassRegistry> m_vtable;
		hkRefPtr<const hkTypeInfoRegistry> m_infoReg;
		mutable hkStringMap<hkDataClassNative*> m_classes;
		hkVariant m_contents;
		hkBool m_accessSerializeIgnored;

		hkTypeManager m_typeManager;

		hkArray<hkUint8> m_buffer;				///< Temporary storage for return types
};

#endif // HK_DATA_NATIVE_OBJECT

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
