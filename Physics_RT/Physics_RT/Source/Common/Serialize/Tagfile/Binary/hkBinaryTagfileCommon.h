/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_BINARY_TAGFILE_COMMON_H
#define HK_BINARY_TAGFILE_COMMON_H

	/// Common data used in the binary tagfile reader and writer.
	/// See the comments in hkBinaryTagfileWriter for version descriptions.
namespace hkBinaryTagfile
{
		/// Magic marker constants used in the file.
	enum TagType
	{
		TAG_EOF = -1,
			/// Invalid tag.
		TAG_NONE = 0,

			/// File header info. Followed by an integer version number.
			/// The rest of the header data is determined by the version number.
		TAG_FILE_INFO = 1,
		
			/// The following item is an hkGenericClass
		TAG_METADATA = 2,

			/// The following item is an hkGenericObject which will not be
			/// referenced again.
		TAG_OBJECT = 3,
			/// The following item is an object which may be referenced again
			/// from TAG_OBJECT_BACKREF. The id is implicitly the count of preceding
			/// remembered objects.
		TAG_OBJECT_REMEMBER = 4,
			/// Refer to a previously encountered object.
			/// Followed by the integer object index.
		TAG_OBJECT_BACKREF = 5,
			/// The null object pointer, only used in version 0 and 1
		TAG_OBJECT_NULL = 6,

			/// End of file marker
		TAG_FILE_END = 7,
	};

	enum
	{
		BINARY_MAGIC_0 = 0xCAB00D1E,
		BINARY_MAGIC_1 = 0xD011FACE,
	};

	struct Header
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(Header, HK_MEMORY_CLASS_BASE);

		hkUint32 m_magic1;
		hkUint32 m_magic2;
		int m_fileInfo;
		int m_version;
		hkStringPtr m_sdk;
	};

		/// Reverse the endianness of a hkUint32.
	inline hkUint32 HK_CALL convertEndianU32( hkUint32 n )
	{
		union fmtU32
		{
			hkUint8 b[4];
			hkUint32 v;
		};
		union fmtU32 fDataIn, fDataOut;

		fDataIn.v = n;
		fDataOut.b[0] = fDataIn.b[3];
		fDataOut.b[1] = fDataIn.b[2];
		fDataOut.b[2] = fDataIn.b[1];
		fDataOut.b[3] = fDataIn.b[0];
		return fDataOut.v;
	}

		/// Do the numbers match the binary magic numbers in either endianness?
	inline hkBool HK_CALL isBinaryMagic( hkUint32 number0, hkUint32 number1 )
	{
		return ( ((number0 == hkBinaryTagfile::BINARY_MAGIC_0) && (number1 == hkBinaryTagfile::BINARY_MAGIC_1))
			|| ((convertEndianU32(number0) == hkUint32(hkBinaryTagfile::BINARY_MAGIC_0)) && (convertEndianU32(number1) == hkUint32(hkBinaryTagfile::BINARY_MAGIC_1))) );
	}
}

#endif // HK_BINARY_TAGFILE_COMMON_H

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
