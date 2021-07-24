/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_UTILITIES2_PHANTOM_DISPLAY_VIEWER_H
#define HK_UTILITIES2_PHANTOM_DISPLAY_VIEWER_H

#include <Physics2012/Utilities/VisualDebugger/Viewer/Dynamics/hkpWorldViewerBase.h>
#include <Physics2012/Dynamics/World/Listener/hkpWorldPostSimulationListener.h>
#include <Physics2012/Dynamics/Phantom/hkpPhantomListener.h>
#include <Physics2012/Dynamics/Phantom/hkpPhantomType.h>
#include <Common/Visualize/Shape/hkDisplayAABB.h>

class hkDebugDisplayHandler;
class hkpWorld;
class hkpWorldObject;

	/// Displays all the entities in a world.
class hkpPhantomDisplayViewer :	public hkpWorldViewerBase, 
								protected hkpPhantomListener, protected hkpWorldPostSimulationListener
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
			/// Creates a hkpPhantomDisplayViewer.
		static hkProcess* HK_CALL create(const hkArray<hkProcessContext*>& contexts);

			/// Registers the hkpPhantomDisplayViewer with the hkProcessFactory.
		static void HK_CALL registerViewer();

			/// Gets the tag associated with this viewer type
		virtual int getProcessTag() { return m_tag; }

		virtual void init();

		static inline const char* HK_CALL getName() { return "Phantoms"; }

	protected:

		hkpPhantomDisplayViewer(const hkArray<hkProcessContext*>& contexts);
		virtual ~hkpPhantomDisplayViewer();

		virtual void phantomAddedCallback( hkpPhantom* entity );
		virtual void phantomRemovedCallback( hkpPhantom* entity );
		virtual void postSimulationCallback( hkpWorld* world );

		virtual void worldAddedCallback( hkpWorld* world );
		virtual void worldRemovedCallback( hkpWorld* world );

	protected:

		void removeAllGeometries();
		void addWorld( hkpWorld* world );
		void removeWorld( hkpWorld* world );

	protected:

		static int m_tag;
		hkArray<hkpWorldObject*> m_phantomShapesCreated;
};

/// This singleton allows you to register hkPhantomTypes user types
/// as being hkShapePhantoms and thus allowing the auto display of the shapes held.
class hkpUserShapePhantomTypeIdentifier : public hkReferencedObject, public hkSingleton<hkpUserShapePhantomTypeIdentifier>
{
	//+vtable(true)
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		hkpUserShapePhantomTypeIdentifier() {}

		void registerShapePhantomType( hkpPhantomType t );

	public:

		hkArray< hkpPhantomType > m_shapePhantomTypes;
};

#ifdef HK_COMPILER_ARMCC // Error:  #2574: explicit specialization of member s_instance must precede its first use 
HK_SINGLETON_SPECIALIZATION_DECL(hkpUserShapePhantomTypeIdentifier);
#endif

#endif	// HK_UTILITIES2_SHAPE_DISPLAY_VIEWER_H

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
