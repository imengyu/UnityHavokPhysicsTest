/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_BASE_CRCSTREAMWRITER_H
#define HK_BASE_CRCSTREAMWRITER_H

#include <Common/Base/System/Io/Writer/hkStreamWriter.h>

/// A generic CRC (Cylic Redundancy Check) class.
template<typename T, T poly>
class hkCrcStreamWriter : public hkStreamWriter
{
	public:
		inline hkCrcStreamWriter( T startCrc = 0 );
		virtual hkBool isOk() const { return true; }
		virtual int write( const void*, int n );

			/// Get the crc from the writer.
		T getCrc() const;

		static inline T calcPermute( T p );

	protected:
		T m_crc;
};

/// CRC32
class hkCrc32StreamWriter : public hkCrcStreamWriter<hkUint32, 0xedb88320> 
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		hkCrc32StreamWriter( hkUint32 startCrc = 0 ) : hkCrcStreamWriter<hkUint32, 0xedb88320>( startCrc ) {}
};

/// CRC64
class hkCrc64StreamWriter : public hkCrcStreamWriter<hkUint64, 0xc96c5795d7870f42ull> 
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
	hkCrc64StreamWriter( hkUint64 startCrc = 0 ) : hkCrcStreamWriter<hkUint64, 0xc96c5795d7870f42ull>( startCrc ) {}

	static const hkUint64 g_crc64lookupTable[256];
};

// Specialize the template for crc64 to use the look-up table.
template<>
inline hkUint64 hkCrcStreamWriter<hkUint64, 0xc96c5795d7870f42ull>::calcPermute(hkUint64 p)
{
	return hkCrc64StreamWriter::g_crc64lookupTable[p];
}

#include <Common/Base/System/Io/Writer/Crc/hkCrcStreamWriter.inl>

#endif // HK_BASE_CRCSTREAMWRITER_H

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
