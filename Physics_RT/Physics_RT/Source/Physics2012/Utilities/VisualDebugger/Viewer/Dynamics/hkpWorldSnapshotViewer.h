/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_UTILITIES2_WORLD_SNAPSHOT_VIEWER_H
#define HK_UTILITIES2_WORLD_SNAPSHOT_VIEWER_H

#include <Physics2012/Utilities/VisualDebugger/Viewer/Dynamics/hkpWorldViewerBase.h>

class hkDebugDisplayHandler;
class hkpWorld;
class hkListener;

	/// Sends the memory used by the Worlds to the VDB clients to inspect
class hkpWorldSnapshotViewer : public hkpWorldViewerBase
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_VDB);
 
		enum Type
		{
			TYPE_XML_TAGFILE = 0,
			TYPE_BINARY_TAGFILE,
			TYPE_COUNT_OF,
		};

			/// Creates a hkpWorldSnapshotViewer.
		static hkProcess* HK_CALL createXmlTagfile(const hkArray<hkProcessContext*>& contexts);
		static hkProcess* HK_CALL createBinaryTagfile(const hkArray<hkProcessContext*>& contexts);

			/// Registers the hkpWorldSnapshotViewer with the hkProcessFactory.
		static void HK_CALL registerViewer();

			/// Gets the tag associated with this viewer type
		virtual int getProcessTag() { return s_tags[m_type]; }

		virtual void init();

		virtual void step( hkReal frameTimeInMs );

		static inline const char* HK_CALL getNameXmlTagfile() { return "* Grab World Snapshot (Xml Tagfile)"; }
		static inline const char* HK_CALL getNameBinaryTagfile() { return "* Grab World Snapshot (Binary Tagfile)"; }

	protected:

		hkpWorldSnapshotViewer(const hkArray<hkProcessContext*>& contexts, Type type );
		virtual ~hkpWorldSnapshotViewer();

	protected:
			
		Type m_type;
		static int s_tags[TYPE_COUNT_OF];
};

#endif	// HK_UTILITIES2_WORLD_SNAPSHOT_VIEWER_H

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
