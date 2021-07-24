/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_SHAPE_CONTAINER_H
#define HKP_SHAPE_CONTAINER_H

#include <Physics2012/Collide/Shape/hkpShapeBuffer.h>
#include <Physics2012/Collide/Shape/hkpShape.h>

extern const class hkClass hkpShapeContainerClass;
extern const class hkClass hkpSingleShapeContainerClass;

class hkpShape;


	/// Interface to shapes which have one or more children, accessible through a shapekey.
	/// See hkpShape::getContainer().
class hkpShapeContainer
{		
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE,hkpShapeContainer);
		HK_DECLARE_REFLECTION();

			/// The policy used how the constructor will change the reference count of the new child. This does not affect the destructor.
		enum ReferencePolicy
		{
			//+reflected(False)
				/// Ignore the reference count of the child.
			REFERENCE_POLICY_IGNORE,

				/// Increment the reference count of the child.
			REFERENCE_POLICY_INCREMENT	
		};

			///
		virtual ~hkpShapeContainer() {}

#if !defined(HK_PLATFORM_SPU)

			/// The number of child shapes. The default implementation just iterates over all keys and is really slow.
		virtual int getNumChildShapes() const;

			/// Get the first child shape key
			/// see getChildShape() for extra details
		virtual hkpShapeKey getFirstKey() const = 0;

			/// Get the next child shape key.
			/// If the "oldKey" parameter is the last key in the shape collection, this function
			/// returns HK_INVALID_SHAPE_KEY.
			/// See getChildShape() for extra details.
		virtual hkpShapeKey getNextKey( hkpShapeKey oldKey ) const = 0;

			/// Return the collision filter info for a given child shape.
		virtual hkUint32 getCollisionFilterInfo( hkpShapeKey key ) const;

			/// Gets a child shape using a shape key.
			/// This function must return a child shape pointer. This is only called internally by
			/// the collision detection system after having called getFirstKey() or getNextKey().
			/// If you have shape keys that are invalid, you must implement getNextKey() in such
			/// a way that it skips over these shapes.
			/// Important Note: It is assumed by the system that a shape key, if valid (i.e., returned by
			/// getNextkey()) will always remain valid.
			///
			/// Notes:
			///     - You can return a pointer to a shape.
			///     - Or you can construct a shape in place in the buffer and return a pointer to that buffer.
			///       E.g., hkpMeshShape uses this buffer for temporarily created triangles.
			///       hkpListShape does not use the buffer as it already has shape instances.
			///       \b Attention: When the buffer gets erased, no destructor will be called.
			///     - The buffer must be 16 byte aligned.
		virtual const hkpShape* getChildShape( hkpShapeKey key, hkpShapeBuffer& buffer ) const = 0;

			/// Return whether welding should be enabled for this shape container (default true).
		virtual bool isWeldingEnabled() const { return true; }
#endif
};


	/// Utility class for a shape which has a single child.
class hkpSingleShapeContainer : public hkpShapeContainer
{
	public:
		HK_DECLARE_REFLECTION();

		/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpSingleShapeContainer() {}

			/// Create a single shape collection.
		hkpSingleShapeContainer( const hkpShape* s, ReferencePolicy ref = REFERENCE_POLICY_INCREMENT ) : m_childShape(s)
		{
#if !defined(HK_PLATFORM_SPU)
			if ( ref == REFERENCE_POLICY_INCREMENT)
			{
				m_childShape->addReference();
			}
#endif
		}

#if !defined(HK_PLATFORM_SPU)
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE,hkpSingleShapeContainer);

		hkpSingleShapeContainer( hkFinishLoadedObjectFlag ) {}

		~hkpSingleShapeContainer()
		{
			if( m_childShape )
			{
				m_childShape->removeReference();
			}
		}

			// Implemented method of hkpShapeContainer
		virtual int getNumChildShapes() const { return 1; }

			// Implemented method of hkpShapeContainer
		virtual hkpShapeKey getFirstKey() const { return 0; }

			// Implemented method of hkpShapeContainer
		virtual hkpShapeKey getNextKey( hkpShapeKey oldKey ) const { return HK_INVALID_SHAPE_KEY; }

			// Implemented method of hkpShapeContainer
		virtual const hkpShape* getChildShape( hkpShapeKey key, hkpShapeBuffer& buffer ) const;

#else
		void* operator new(hk_size_t, void* p) { return p; }
		void  operator delete(void* p) { }
#endif
			/// Get the child shape.
		inline const hkpShape* getChild() const { return m_childShape; }
			
			/// 
		inline const hkpShape* operator->() const { return m_childShape; }

	protected:

		const hkpShape* m_childShape;
};

hkBool::CompileTimeTrueType hkIsVirtual( hkpSingleShapeContainer* );

// used by hkpConvexVerticesShape and hkpCompressedMeshShape
typedef void (HK_CALL *hkpGetFaceNormalsFunc)(const void*, hkArray<hkVector4>&);

#endif // HKP_SHAPE_CONTAINER_H

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
