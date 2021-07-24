/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MXVECTORf_UTIL_H
#define HK_MXVECTORf_UTIL_H

#include <Common/Base/Math/Vector/Mx/hkMxVectorf.h>
#include <Common/Base/Math/Vector/Mx/hkMxQuaternionf.h>
#include <Common/Base/Math/Vector/hkPackedVector3.h>

typedef hkMxVectorf<4> hkMxTransformf;
#define hkMxTransformfParameter const hkMxTransformf&


/// Utility functions for working with long vectors.
///
/// Routines need to be parameterized by vector length M. The methods assume that the pointed to memory is
/// large enough to process all M subvectors. No range checking is done on the base memory pointers or the
/// addresses computed by the parameters.
///
/// The vector transform methods provide optimized implementations for the common use case of 4x4 matrices.
///
/// \sa hkMxVectorf hkMxRealf hkMxSinglef hkMxHalf8
namespace hkMxVectorUtil
{
	//
	// Storage conversion from hkHalf
	//

	/// load a stream of hkHalfs into an hkMxVectorf
	template <int M>
	HK_FORCE_INLINE void HK_CALL loadUnpack(const hkHalf* base, hkMxVectorf<M>& vOut0);

	/// Write a stream of subvectors of \a v to the a non-contiguous memory addresses \a base + (m * byteAddressIncrement), the dest address needs to be 8 byte aligned
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL scatterPack(hkMxVectorfParameter v, hkHalf* base);


// 	template <int M>
// 	HK_FORCE_INLINE void HK_CALL storePacked(const hkMxVectorf<M>& vin, const hkHalf* baseOut );

	/// Read subvectors into \a vOut0 and \a vOut1 from the first and second packed half respectively of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpack(const hkHalf* base, hkMxVectorf<M>& vOut0, hkMxVectorf<M>& vOut1);

	/// Read subvectors into \a vOut0 and \a vOut1 from the first and second packed half respectively of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL gatherUnpack(const hkHalf* base, const hkUint16* indices, hkMxVectorf<M>& vOut0, hkMxVectorf<M>& vOut1);

	/// Read subvectors into \a vOut0 and \a vOut1 from the first and second packed half respectively of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpack(const hkHalf* base, const hkInt32* indices, hkMxVectorf<M>& vOut0, hkMxVectorf<M>& vOut1);

	/// Read subvectors into \a vOut0 and \a vOut1 from the first and second packed half respectively of the hkHalf[8] at non-linear memory using addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gatherUnpackHalf8WithOffset(const void* base[M], hkMxVectorf<M>& vOut0, hkMxVectorf<M>& vOut1);

	/// Read subvectors into \a vOut from the first packed half of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpackFirst(const hkHalf* base, hkMxVectorf<M>& vOut);

	/// Read subvectors into \a vOut from the first packed half of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL gatherUnpackFirst(const hkHalf* base, const hkUint16* indices, hkMxVectorf<M>& vOut);

	/// Read subvectors into \a vOut from the first packed half of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpackFirst(const hkHalf* base, const hkInt32* indices, hkMxVectorf<M>& vOut);

	/// Read subvectors into \a vOut from the first packed half of the hkHalf[8] at non-linear memory using addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gatherUnpackFirstHalf8WithOffset(const void* base[M], hkMxVectorf<M>& vOut);

	/// Read subvectors into \a vOut from the second packed half of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpackSecond(const hkHalf* base, hkMxVectorf<M>& vOut);

	/// Read subvectors into \a vOut from the second packed half of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL gatherUnpackSecond(const hkHalf* base, const hkUint16* indices, hkMxVectorf<M>& vOut);
	/// Read subvectors into \a vOut from the second packed half of the hkHalf[8] at non-linear indexed memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL gatherUnpackSecond(const hkHalf* base, const hkInt32* indices, hkMxVectorf<M>& vOut);
	/// Read subvectors into \a vOut from the second packed half of the hkHalf[8] at non-linear memory using addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gatherUnpackSecondHalf8WithOffset(const void* base[M], hkMxVectorf<M>& vOut);


	/// Write subvectors of \a v0 and \a v1 to the first and second packed half respectively of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL scatterPack(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkHalf* base);

	/// Write subvectors of \a v0 and \a v1 to the first and second packed half respectively of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPack(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkHalf* base, const hkUint16* indices);

	/// Write subvectors of \a v0 and \a v1 to the first and second packed half respectively of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPack(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkHalf* base, const hkInt32* indices);

	/// Write subvectors of \a v0 and \a v1 to the first and second packed half respectively of the hkHalf[8] at non-linear memory addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL scatterPackHalf8WithOffset(hkMxVectorfParameter v0, hkMxVectorfParameter v1, void* base[M]);

	/// Write subvectors of \a v to the first packed half of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL scatterPackFirst(hkMxVectorfParameter v, hkHalf* base);

	/// Write subvectors of \a v to the first packed half of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPackFirst(hkMxVectorfParameter v, hkHalf* base, const hkUint16* indices);

	/// Write subvectors of \a v to the first packed half of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPackFirst(hkMxVectorfParameter v, hkHalf* base, const hkInt32* indices);

	/// Write subvectors of \a v to the first packed half of the hkHalf[8] at non-linear memory addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL scatterPackFirstHalf8WithOffset(hkMxVectorfParameter v, void* base[M]);

	/// Write subvectors of \a v to the second packed half of the hkHalf[8] at non-contiguous memory addresses \a base + (m * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement>
	HK_FORCE_INLINE void HK_CALL scatterPackSecond(hkMxVectorfParameter v, hkHalf* base);
	/// Write subvectors of \a v to the second packed half of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPackSecond(hkMxVectorfParameter v, hkHalf* base, const hkUint16* indices);
	/// Write subvectors of \a v to the second packed half of the hkHalf[8] at non-linear indexed to memory addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <int M, hkUint32 byteAddressIncrement> 
	HK_FORCE_INLINE void HK_CALL scatterPackSecond(hkMxVectorfParameter v, hkHalf* base, const hkInt32* indices);
	/// Write subvectors of \a v to the second packed half of the hkHalf[8] at non-linear memory addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL scatterPackSecondHalf8WithOffset(hkMxVectorfParameter v, void* base[M]);


	//
	// Storage conversion from hkPackedVector
	//

	/// Read subvectors into \a vOut from the packed 3-component vectors at non-linear memory using addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gatherUnpackPackedVectorWithOffset(const void* base[M], hkMxVectorf<M>& vOut);

	/// Get 3w components of 3 consecutive hkVector4f s
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gather3WComponents(const void* base[M], hkMxVectorf<M>& vOut);

	

	/// Read subvectors into \a vOut from the packed 4-component unit vectors at non-linear memory using addresses \a base[m] + byteAddressOffset
	template <int M, hkUint32 byteAddressOffset>
	HK_FORCE_INLINE void HK_CALL gatherUnpackPackedUnitVectorWithOffset(const void* base[M], hkMxVectorf<M>& vOut);




	//
	// Vector transformations
	//


	/// Transform the 4 position subvectors in \a vIn using matrix \a mat and store in \a vOut.
	/// \warning [M:1-4 only] 
	template <int M>
	HK_FORCE_INLINE void HK_CALL transformPosition(hkMxTransformfParameter mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut);
	/// Transform the 4 position subvectors in \a vIn using the transpose matrix of \a mat and store in \a vOut.
	/// \warning [M:1-4 only] 
	template <int M>
	HK_FORCE_INLINE void HK_CALL transformTransposePosition(hkMxTransformfParameter mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut);

	/// Rotate the direction subvectors in \a vIn using matrix \a mat and store in \a vOut.
	/// \warning [M:1-4 only] 
	template <int M>
	HK_FORCE_INLINE void HK_CALL rotateDirection( hkMxTransformfParameter mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut);
	/// Rotate the direction subvectors in \a vIn using the inverse matrix of \a mat and store in \a vOut.
	/// \warning [M:1-4 only] 
	template <int M>
	HK_FORCE_INLINE void HK_CALL rotateInverseDirection( hkMxTransformfParameter mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut);

	/// Optimized routine to transform each position subvector in \a vIn with one matrix and store in \a vOut. \a vIn[0] is transformed by \a mat0, \a vIn[1] is transformed by \a mat1, \a vIn[2] is transformed by \a mat2 and \a vIn[3] is transformed by \a mat3.
	/// \warning [M:4 only] 
	HK_FORCE_INLINE void HK_CALL transform4Positions(hkMxTransformfParameter mat0, hkMxTransformfParameter mat1, hkMxTransformfParameter mat2, hkMxTransformfParameter mat3, const hkMxVectorf<4>& vIn, hkMxVectorf<4>& vOut);
	/// Optimized routine to rotate each direction subvector in \a vIn with one matrix and store in \a vOut. \a vIn[0] is rotated by \a mat0, \a vIn[1] is rotated by \a mat1, \a vIn[2] is rotated by \a mat2 and \a vIn[3] is rotated by \a mat3.
	/// \warning [M:4 only] 
	HK_FORCE_INLINE void HK_CALL rotate4Directions(hkMxTransformfParameter mat0, hkMxTransformfParameter mat1, hkMxTransformfParameter mat2, hkMxTransformfParameter mat3, const hkMxVectorf<4>& vIn, hkMxVectorf<4>& vOut);

	/// Rotate each subvector in \a vIn using the respective subquaterion in \a mat and store in \a vOut.
	template <int M>	HK_FORCE_INLINE void HK_CALL rotateDirection( hkMxQuaternionfParameter mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut);

	/// Rotate each subvector in \a vIn using one transform from the array \a mat and store in \a vOut.
	template <int M>	HK_FORCE_INLINE void HK_CALL rotateDirection( const hkTransformf* mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut);

	/// Transform each subvector in \a vIn using one transform from the array \a mat and store in \a vOut.
	template <int M>	HK_FORCE_INLINE void HK_CALL transformPosition( const hkTransformf* mat, hkMxVectorfParameter vIn, hkMxVectorf<M>& vOut);
};

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
	#if (HK_SSE_VERSION >= 0x50)
	#include <Common/Base/Math/Vector/Mx/hkMxVectorUtil_AVX.inl>
	#else
	#include <Common/Base/Math/Vector/Mx/hkMxVectorfUtil.inl>
	#endif
#else
	#include <Common/Base/Math/Vector/Mx/hkMxVectorfUtil.inl>
#endif

#endif // HK_MXVECTORf_UTIL_H

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
