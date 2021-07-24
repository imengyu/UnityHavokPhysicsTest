/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_SERIALIZE_PATCH_MANAGER_H
#define HK_SERIALIZE_PATCH_MANAGER_H

#include <Common/Base/Types/hkTypedUnion.h>
#include <Common/Base/Container/StringMap/hkStringMap.h>
#include <Common/Serialize/Data/hkDataObject.h>

class hkClassNameRegistry;

	/// Class defining and managing versions of classes using patches.
	/// You should hkVersionPatchManager::getInstance() to access instance
	/// of the manager.
class hkVersionPatchManager : public hkReferencedObject, public hkSingleton<hkVersionPatchManager>
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
			/// Supported patch component types.
		enum PatchType
		{
			PATCH_INVALID,

			PATCH_MEMBER_ADDED,
			PATCH_MEMBER_REMOVED,
			PATCH_MEMBER_RENAMED,
			PATCH_MEMBER_DEFAULT_SET,

			PATCH_FUNCTION,

			PATCH_CAST,

			PATCH_DEPENDS,

			PATCH_PARENT_SET,

			PATCH_END
		};

			/// Class defining a versioning patch for reflected class.
		struct PatchInfo
		{
				/// Class defining a component of the versioning patch, e.g., add and/or remove class member.
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,PatchInfo);
			struct Component
			{
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,Component);
				PatchType type;
				const void* patch;
			};
			const char* oldName;
			const char* newName;
			hkInt32 oldVersion;
			hkInt32 newVersion;
			const Component* component;
			hkInt32 numComponent;
		};
		
		typedef void (HK_CALL *Function)(hkDataObject& o);

		typedef hkStringMap<hkDataClassImpl*> ClassImplFromName;
		
			/// hkVersionPatchManager constructor.
		hkVersionPatchManager();

			/// hkVersionPatchManager destructor.
		~hkVersionPatchManager();

			/// Set class version dependency in patch.
		struct DependsPatch
		{
			enum { PATCH_TYPE=PATCH_DEPENDS };
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, DependsPatch);
			const char* name; ///< Class name of dependency
			hkInt32 version; ///< Class version of dependency
		};

			/// Define class member renamed in patch.
		struct MemberRenamedPatch
		{
			enum { PATCH_TYPE=PATCH_MEMBER_RENAMED};
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkVersionPatchManager::MemberRenamedPatch);
			const char* oldName; ///< Old name
			const char* newName; ///< New name
		};

			/// Define class member added in patch.
		struct MemberAddedPatch
		{
			enum { PATCH_TYPE=PATCH_MEMBER_ADDED};
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkVersionPatchManager::MemberAddedPatch);
			const char* name; ///< Name of the new member.
			hkLegacyType::Type type; ///< Type of the new member.
			const char* typeName; ///< Name of class or null for basic types.
			hkInt32 tuples; ///< The number of elements in a c-style array, usually zero for "not an c-array".
			const void* defaultPtr; ///< Pointer to default value, if given.
		};

			/// Define class member removed in patch.
		struct MemberRemovedPatch
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, MemberRemovedPatch);
			enum { PATCH_TYPE=PATCH_MEMBER_REMOVED};
			const char* name; ///< Name of the removed member
			hkLegacyType::Type type; ///< Type of the removed member
			const char* typeName;  ///< Class name of the removed member or null for basic types.
			hkInt32 tuples;  ///< Count of elements in c-style array or zero for "not a c-array".
		};

			/// Set class parent in patch.
 		struct SetParentPatch
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, SetParentPatch);
			enum { PATCH_TYPE=PATCH_PARENT_SET };
			const char* oldParent; ///< Old parent
			const char* newParent; ///< New parent
		};

			/// Set function to be called in patch.
		struct FunctionPatch
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, FunctionPatch);
			enum { PATCH_TYPE=PATCH_FUNCTION };
			const char* name; ///< Name of the function as a string for debugging.
			Function function; ///< Function pointer.
		};

			/// Set cast to class in patch.
		struct CastPatch
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, CastPatch);
			enum { PATCH_TYPE=PATCH_CAST };
			const char* name;
		};

		/// Default changed for class member in patch.
		struct DefaultChangedPatch
		{
			enum { PATCH_TYPE=PATCH_MEMBER_DEFAULT_SET };
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkVersionPatchManager::MemberAddedPatch);
			const char* name; ///< Name of the member.
			const void* defaultPtr; ///< Pointer to new default value
		};

		class ClassWrapper: public hkReferencedObject
		{
		public:
			HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
				/// Given a world and a class name tries to return the type 'wrapped'. Return HK_NULL if couldn't locate or wrap the type.
			virtual hkDataClassImpl* wrapClass(hkDataWorld* world, const char* typeName) = 0;
		};

			/// Apply registered patches to the 'world'.
			/// The function optionally takes ClassWrapper which is used to produce 
			/// current definitions of types from their names. 
			/// This function already calls hkVersionPatchManager::recomputePatchDependencies().
		hkResult applyPatches(hkDataWorld& world, ClassWrapper* wrapper = HK_NULL) const;

			/// Register individual patch with the version patch manager.
			/// The patch dependencies must be recomputed using recomputePatchDependencies()
			/// to guarantee proper sequence of patches when applied to classes in a world.
		void addPatch(const PatchInfo* p);

			/// Recompute all patch dependencies and set them in proper order,
			/// so classes can be updated accordingly.
		hkResult recomputePatchDependencies() const;


			// Used internally.
		hkResult applyPatchesDebug(hkDataWorld& world) const;

			// Used internally.
			// Return all registered patches.
			// The order of the patches may not be set according to dependencies,
			// you should call hkVersionPatchManager::recomputePatchDependencies()
			// to guarantee it.
		const hkArray<const PatchInfo*>& getPatches() const;

			// Used internally.
			// Generate uid, an unique 64-bit value, from class name and version.
		hkUint64 getUid( const char* name, hkInt32 ver ) const;

			// Used internally.
			// Get class name from uid.
		const char* getClassName( hkUint64 uid ) const;

			// Used internally.
			// Get class version from uid.
		hkInt32 getClassVersion( hkUint64 uid ) const;

			// Used internally.
			// Get update patch index from uid, if any.
			// Return -1 if no update patch found.
		HK_FORCE_INLINE hkInt32 getPatchIndex( hkUint64 uid ) const;

			// Used internally.
			// Get patch by index.
		HK_FORCE_INLINE const PatchInfo* getPatch( hkInt32 patchIndex ) const;

			// Used internally.
		HK_FORCE_INLINE int getNumPatches() const;

			// Used internally.
			// Find last registered patch index for given uid.
			// The patches should be recomputed before calling this function
			// (see hkVersionPatchManager::recomputePatchDependencies() for details).
		int findLastPatchIndexForUid(hkUint64 uid, hkBool32 allowRenames = false) const;

			// Clear patches already loaded 
		void clearPatches();

			// Clears all patches belonging to the given product. The product match is done by name prefix.
		void clearProductPatches(const char* productPrefix);

	private:

		// All classes that need to be examined by the memory tracker 
		// (like UidFromClassVersion) need to have a proper layout and to 
		// obtain that we need to reflect this class in the tracker reflection
		// using LLVM (the class must therefore be visible in the header)
		class UidFromClassVersion
		{
		public:
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SERIALIZE, UidFromClassVersion);
			~UidFromClassVersion();
			hkUint64 get( const char* name, int ver ) const;
			const char* getName( hkUint64 uid ) const;
			int getVersion( hkUint64 uid ) const;

		private:
			const char* cache(const char* name) const;
			mutable hkStringMap<int> m_indexFromName;
			mutable hkArray<const char*> m_names;
			mutable hkStringMap<char*> m_cachedNames;
		};

		UidFromClassVersion* m_uidFromClassVersion;
			// all patches
		mutable hkArray<const PatchInfo*> m_patchInfos;
		mutable hkPointerMap<hkUint64, hkInt32> m_patchIndexFromUid;

	private:

		hkResult preparePatches(hkDataWorld& worldToUpdate, ClassWrapper* wrapper, hkArray<const PatchInfo*>& patchInfosOut) const;
};

class hkDefaultClassWrapper: public hkVersionPatchManager::ClassWrapper
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
	// implement hkVersionPatchManager::ClassWrapper
	virtual hkDataClassImpl* wrapClass(hkDataWorld* world, const char* typeName);

		/// Ctor
	hkDefaultClassWrapper(const hkClassNameRegistry* nameReg = HK_NULL);

protected:
	hkRefPtr<const hkClassNameRegistry> m_nameReg;
};

#if defined(HK_COMPILER_ARMCC) || defined(HK_COMPILER_GHS) // have to specialize before use so that generalized one not auto gen-d
HK_SINGLETON_SPECIALIZATION_DECL(hkVersionPatchManager);
#endif

#include <Common/Serialize/Version/hkVersionPatchManager.inl>

#endif // HK_SERIALIZE_PATCH_MANAGER_H

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
