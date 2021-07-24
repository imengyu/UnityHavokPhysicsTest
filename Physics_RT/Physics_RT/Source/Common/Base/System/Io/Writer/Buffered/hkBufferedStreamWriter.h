/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_BUFFERED_STREAMWRITER_H
#define HKBASE_BUFFERED_STREAMWRITER_H

#include <Common/Base/System/Io/Writer/hkStreamWriter.h>

extern const hkClass hkBufferedStreamWriterClass;

#ifdef HK_PLATFORM_PSVITA
#define HK_BUFFERED_STREAM_DEFAULT_WRITE_BUFSIZE (64*1024)
#else
#define HK_BUFFERED_STREAM_DEFAULT_WRITE_BUFSIZE 4096
#endif

	/// Wraps and buffers an existing unbuffered stream.
class hkBufferedStreamWriter : public hkStreamWriter
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
			/// Create a buffered stream from stream 's' with size 'bufSize'.
			/// Adds a reference to 's'.
		hkBufferedStreamWriter(hkStreamWriter* s, int bufSize=HK_BUFFERED_STREAM_DEFAULT_WRITE_BUFSIZE);

			/// Create a buffered stream from a piece of memory 'm' with size 'memSize'.
			/// The memory is used in place and must be valid for the lifetime of this object.
			/// If the memory is to be used to hold a C string, it is zeroed and the final byte
			/// will not be written to which ensures the string is always terminated.
		hkBufferedStreamWriter(void* mem, int memSize, hkBool memoryIsString);

			/// Removes a reference to its sub stream.
		~hkBufferedStreamWriter();

		virtual int write(const void* buf, int nbytes);

		virtual void flush();

		virtual hkBool isOk() const;


		virtual hkBool seekTellSupported() const;

		virtual hkResult seek(int offset, SeekWhence whence);

		virtual int tell() const;

#ifndef HK_PLATFORM_SPU
		virtual const hkClass* getClassType() const { return &hkBufferedStreamWriterClass; }
#endif

	protected:

		hkStreamWriter* m_stream; // child stream or HK_NULL for inplace
		char* m_buf; // start of buffer area
		int m_bufSize; // used buffer area
		int m_bufCapacity; // total available buffer area
		hkBool m_ownBuffer; // did we allocate the buffer

	protected:

		int flushBuffer();
};

#endif // HKBASE_BUFFERED_STREAMWRITER_H

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
