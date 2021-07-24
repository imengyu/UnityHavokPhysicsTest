/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_BASE_POSIXSTREAMREADER_H
#define HK_BASE_POSIXSTREAMREADER_H

#include <Common/Base/System/Io/Reader/hkStreamReader.h>

class hkPosixStreamReader : public hkSeekableStreamReader
{
	public:

		static hkPosixStreamReader* open(const char* name);

		hkPosixStreamReader( int handle );
		virtual ~hkPosixStreamReader();
		void close();

		virtual int read( void* buf, int nbytes);
		virtual int peek( void* buf, int nbytes);
		virtual hkBool isOk() const;

		virtual hkResult seek( int offset, SeekWhence whence);
		virtual int tell() const;

	protected:

		int m_handle;
		bool m_isOk;
};

#endif //HK_BASE_POSIXSTREAMREADER_H

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
