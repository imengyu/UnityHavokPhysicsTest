/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_UTILITIES2_CONTACT_POINT_VIEWER_H
#define HK_UTILITIES2_CONTACT_POINT_VIEWER_H

#include <Physics2012/Utilities/VisualDebugger/Viewer/Dynamics/hkpWorldViewerBase.h>
#include <Physics2012/Dynamics/World/Listener/hkpWorldPostSimulationListener.h>

class hkDebugDisplayHandler;
class hkpWorld;
class hkListener;

	/// An abstract base class for the contact viewers
	/// (hkActiveContactPointviewer and hkpInactiveContactPointViewer).
class hkpContactPointViewer : public hkpWorldViewerBase, public hkpWorldPostSimulationListener
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_VDB);

		virtual void init();

		void postSimulationCallback(hkpWorld* world);
		
			/// Draw only contact points whose impulse exceeds this limit. Default: 0 (=all)
		hkReal m_limit;

	protected:

			/// Draw all of the contact points in the given simulation island.
		void drawAllContactPointsInIsland(const class hkpSimulationIsland* island);

			/// Get the array of simulation islands that this viewer will draw.
		virtual const hkArray<class hkpSimulationIsland*>& getIslands(class hkpWorld* world) const = 0;
	
		hkpContactPointViewer(const hkArray<hkProcessContext*>& contexts, const hkColor::Argb color);
		virtual ~hkpContactPointViewer();

		virtual void worldAddedCallback( hkpWorld* world );
		virtual void worldRemovedCallback( hkpWorld* world );

		const hkColor::Argb m_color;
};

#endif	// HK_UTILITIES2_CONTACT_POINT_VIEWER_H

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
