/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


namespace hkaBatchBlenderUtilities
{
	//
	// The following base functions blend and interpolate vectors,
	// quaternions and transforms.  These base functions provide the
	// building blocks for more complex actions.  Each function
	// provides the appropriate analogue of the interpolation
	// function: dst = ( 1 - alpha ) * src0 + ( alpha ) * src1.
	//

	// Linearly interpolates four hkVector4 pairs with four unique blend amounts alpha
	HK_FORCE_INLINE void HK_CALL lerp4(
		hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
		const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
		const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3,
		const hkVector4& alpha
		);

	
	// Spherically linearly interpolates four quaternion pairs (as hkVector4's) with four unique blend amounts alpha
	HK_FORCE_INLINE void HK_CALL slerp4(
		hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
		const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
		const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3,
		const hkVector4& alpha
		);
	
	// Linearly interpolates four quaternion pairs (as hkVector4's) with four unique blend amounts alpha (must be renormalized later)
	HK_FORCE_INLINE void HK_CALL qlerp4(
		hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
		const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
		const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3,
		const hkVector4& alpha
		);

	// Inverts four hkQuaternions
	HK_FORCE_INLINE void HK_CALL inv4(
		hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
		const hkQuaternion& src0, const hkQuaternion& src1, const hkQuaternion& src2, const hkQuaternion& src3
		);
	
	// Inverts four hkQsTransforms
	HK_FORCE_INLINE void HK_CALL inv4(
		hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
		const hkQsTransform& src0, const hkQsTransform& src1, const hkQsTransform& src2, const hkQsTransform& src3
		);
	
	// Adds four hkVector4 pairs
	HK_FORCE_INLINE void HK_CALL add4(
		hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
		const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
		const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
		);
	
	// Multiplies four hkVector4 pairs
	HK_FORCE_INLINE void HK_CALL mul4(
		hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
		const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
		const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
		);
	
	// Multiplies four hkQuaternion pairs
	HK_FORCE_INLINE void HK_CALL mul4(
		hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
		const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
		const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3
		);
	
	// Multiplies four hkQsTransform pairs
	HK_FORCE_INLINE void HK_CALL mul4(
		hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
		const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
		const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3
		);
	
	// Adds four hkVector4 pairs
	HK_FORCE_INLINE void HK_CALL sub4(
		hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
		const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
		const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
		);
	
	// Multiplies four hkQuaternion pairs by inverting the right transform
	HK_FORCE_INLINE void HK_CALL mulInv4(
		hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
		const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
		const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3
		);
	
	// Multiplies four hkQsTransform pairs by inverting the right transform
	HK_FORCE_INLINE void HK_CALL mulInv4(
		hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
		const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
		const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3
		);
	
	// Rotates four hkVector4 instances by corresponding hkQuaternion instances
	HK_FORCE_INLINE void HK_CALL rotate4(
		hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
		const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
		const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
		);
	
	// Rotates four hkVector4 instances by corresponding hkQuaternion instances
	HK_FORCE_INLINE void HK_CALL rotateInv4(
		hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
		const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
		const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
		);
	
	// Transforms four hkVector4 instances by corresponding hkQsTransform instances
	HK_FORCE_INLINE void HK_CALL transform4(
		hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
		const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
		const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
		);
	
	// Transforms four hkVector4 instances by corresponding hkQsTransform instances
	HK_FORCE_INLINE void HK_CALL transformInv4(
		hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
		const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
		const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
		);


	//
	// The following base utility functions are useful for
	// implementing the base functions above.
	//

	// Copies four vectors
	HK_FORCE_INLINE void HK_CALL copy4(
		hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
		const hkVector4& src0, const hkVector4& src1, const hkVector4& src2, const hkVector4& src3
		);

	// Copies four quaternions
	HK_FORCE_INLINE void HK_CALL copy4(
		hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
		const hkQuaternion& src0, const hkQuaternion& src1, const hkQuaternion& src2, const hkQuaternion& src3
		);

	// Copies four transforms
	HK_FORCE_INLINE void HK_CALL copy4(
		hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
		const hkQsTransform& src0, const hkQsTransform& src1, const hkQsTransform& src2, const hkQsTransform& src3
		);

	// Transposes four vectors in place
	HK_FORCE_INLINE void HK_CALL transpose4(
		hkVector4& v0InOut, hkVector4& v1InOut, hkVector4& v2InOut, hkVector4& v3InOut
		);

	// Computes new blend amount alphaOut from four given alphas and four weights
	HK_FORCE_INLINE void HK_CALL computeBlendFactorAndWeights4(
		hkVector4& alphaOut, hkVector4& weightsOut,
		const hkVector4& alpha,
		const hkVector4& weightL, const hkVector4& weightR );

	// Computes new blend amount alphaOut from four given alphas and four weights
	HK_FORCE_INLINE void HK_CALL computeBlendFactorAndWeightsAdditive4(
		hkVector4& alphaOut, hkVector4& weightsOut,
		const hkVector4& alpha,
		const hkVector4& weightL, const hkVector4& weightR );

	// Normalizes four hkQuaternion instances
	HK_FORCE_INLINE void HK_CALL normalize4(
		hkQuaternion& qInOut0, hkQuaternion& qInOut1, hkQuaternion& qInOut2, hkQuaternion& qInOut3
		);
	
	// Series approximations for trig functions.  Computed four at a time.
	HK_FORCE_INLINE void HK_CALL sin_series_2_terms( hkVector4& out, const hkVector4& theta );
	HK_FORCE_INLINE void HK_CALL acos_series_4_terms( hkVector4& out, const hkVector4& theta );

	// Data used by the previous functions, extracted as extern constant because of wii/wiiu compilers not
	// able to handle static const function variables properly.
	extern const hkQuadReal s_sin_series_2_terms_c2;
	extern const hkQuadReal s_sin_series_2_terms_c4;

	extern const hkQuadReal s_acos_series_4_terms_c0;
	extern const hkQuadReal s_acos_series_4_terms_c1;
	extern const hkQuadReal s_acos_series_4_terms_c2;
	extern const hkQuadReal s_acos_series_4_terms_c3;

	// blend without weights
	template< typename TYPE >
	void HK_CALL blendBase( TYPE* HK_RESTRICT dstOut, const TYPE* HK_RESTRICT srcL, const TYPE* HK_RESTRICT srcR, const hkSimdReal& alpha, int n, hkaBlender::BLEND_MODE blendMode, hkaBlender::ROTATION_MODE rotationMode );

	// blend with weights
	template< typename TYPE >
	void HK_CALL blendBase( TYPE* HK_RESTRICT dstOut, hkReal* HK_RESTRICT weightsOut, const TYPE* HK_RESTRICT srcL, const hkReal* HK_RESTRICT weightL, const TYPE* HK_RESTRICT srcR, const hkReal* HK_RESTRICT weightR, const hkSimdReal& alpha, int n, hkaBlender::BLEND_MODE blendMode, hkaBlender::ROTATION_MODE rotationMode );

	template< typename TYPE, typename BLEND_FUNCTOR, typename WEIGHT_FUNCTOR, typename ROTATION_FUNCTOR  >
	void HK_FORCE_INLINE blendCore( TYPE* HK_RESTRICT dst, hkReal* weightsOut, const TYPE* HK_RESTRICT srcL, const hkReal* weightsL, const TYPE* HK_RESTRICT srcR, const hkReal* weightsR, const hkSimdReal& alpha, int n, WEIGHT_FUNCTOR weightFunctor, BLEND_FUNCTOR blendFunctor, ROTATION_FUNCTOR rotationFunctor );

	// Base function for implementing rotations
	template< typename HANDLE_W_FUNCTOR >
	void HK_FORCE_INLINE rotateBase4(
		HANDLE_W_FUNCTOR handleW,
		hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
		const hkQuaternion& q0, const hkQuaternion& q1, const hkQuaternion& q2, const hkQuaternion& q3,
		const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, const hkVector4& v3
		);	

	// Helper Functors...
	// See http://en.wikipedia.org/wiki/Function_object for an
	// explanation of why functors can be inlined, but function
	// pointers cannot
	struct BlendNormalFunctor
	{
		HK_FORCE_INLINE void operator() ( hkReal& dst0, hkReal& dst1, hkReal& dst2, hkReal& dst3,
										  const hkReal& srcL0, const hkReal& srcL1, const hkReal& srcL2, const hkReal& srcL3,
										  const hkReal& srcR0, const hkReal& srcR1, const hkReal& srcR2, const hkReal& srcR3 );
		
		HK_FORCE_INLINE void operator() ( hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
										  const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
										  const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3 );
		
		HK_FORCE_INLINE void operator() ( hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
										  const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
										  const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3 );
		
		HK_FORCE_INLINE void operator() ( hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
										  const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
										  const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3 );
	};

	struct BlendAdditiveFunctor
	{
		HK_FORCE_INLINE void operator() ( hkReal& dst0, hkReal& dst1, hkReal& dst2, hkReal& dst3,
										  const hkReal& srcL0, const hkReal& srcL1, const hkReal& srcL2, const hkReal& srcL3,
										  const hkReal& srcR0, const hkReal& srcR1, const hkReal& srcR2, const hkReal& srcR3 );
		
		HK_FORCE_INLINE void operator() ( hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
										  const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
										  const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3 );
		
		HK_FORCE_INLINE void operator() ( hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
										  const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
										  const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3 );
		
		HK_FORCE_INLINE void operator() ( hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
										  const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
										  const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3 );
	};

	struct BlendSubtractiveFunctor
	{
		HK_FORCE_INLINE void operator() ( hkReal& dst0, hkReal& dst1, hkReal& dst2, hkReal& dst3,
										  const hkReal& srcL0, const hkReal& srcL1, const hkReal& srcL2, const hkReal& srcL3,
										  const hkReal& srcR0, const hkReal& srcR1, const hkReal& srcR2, const hkReal& srcR3 );
		
		HK_FORCE_INLINE void operator() ( hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
										  const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
										  const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3 );
		
		HK_FORCE_INLINE void operator() ( hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
										  const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
										  const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3 );
		
		HK_FORCE_INLINE void operator() ( hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
										  const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
										  const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3 );
	};

	struct LerpFunctor
	{
		HK_FORCE_INLINE void operator() (
			hkReal& dst0, hkReal& dst1, hkReal& dst2, hkReal& dst3,
										  const hkReal& srcL0, const hkReal& srcL1, const hkReal& srcL2, const hkReal& srcL3,
										  const hkReal& srcR0, const hkReal& srcR1, const hkReal& srcR2, const hkReal& srcR3,
										  const hkVector4& alpha );
		
		HK_FORCE_INLINE void operator() (
			hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
			const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
			const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3,
			const hkVector4& alpha );
		
		HK_FORCE_INLINE void operator() (
			hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
			const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
			const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3,
			const hkVector4& alpha );
		
		HK_FORCE_INLINE void operator() (
			hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
			const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
			const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3,
			const hkVector4& alpha );
	};

	struct SlerpFunctor
	{
		HK_FORCE_INLINE void operator() (
			hkReal& dst0, hkReal& dst1, hkReal& dst2, hkReal& dst3,
										  const hkReal& srcL0, const hkReal& srcL1, const hkReal& srcL2, const hkReal& srcL3,
										  const hkReal& srcR0, const hkReal& srcR1, const hkReal& srcR2, const hkReal& srcR3,
										  const hkVector4& alpha );

		HK_FORCE_INLINE void operator() (
			hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
			const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
			const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3,
			const hkVector4& alpha );
		
		HK_FORCE_INLINE void operator() (
			hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
			const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
			const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3,
			const hkVector4& alpha );
		
		HK_FORCE_INLINE void operator() (
			hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
			const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
			const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3,
			const hkVector4& alpha );
	};

	struct WeightUnweightedFunctor
	{
		HK_FORCE_INLINE void operator() (
			hkVector4& alphaOut, hkVector4& weightsOut,
			const hkVector4& alpha,
			const hkVector4& weightL, const hkVector4& weightR );
	};

	struct WeightNormalFunctor
	{
		HK_FORCE_INLINE void operator() (
			hkVector4& alphaOut, hkVector4& weightsOut,
			const hkVector4& alpha,
			const hkVector4& weightL, const hkVector4& weightR );
	};

	struct WeightAdditiveFunctor
	{
		HK_FORCE_INLINE void operator() (
			hkVector4& alphaOut, hkVector4& weightsOut,
			const hkVector4& alpha,
			const hkVector4& weightL, const hkVector4& weightR );
	};

	struct PosateFunctor
	{
		void operator()( hkVector4& vInOut );
	};

	struct NegateFunctor
	{
		void operator()( hkVector4& vInOut );
	};
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::lerp4(
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
	const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3,
	const hkVector4& alpha
	)
{
	// Allocate temporary storage for transpose style operations

	// Left values
	hkVector4 xl;
	hkVector4 yl;
	hkVector4 zl;
	hkVector4 wl;

	// Right values
	hkVector4 xr;
	hkVector4 yr;
	hkVector4 zr;
	hkVector4 wr;

	// Blended values
	hkVector4 xt;
	hkVector4 yt;
	hkVector4 zt;
	hkVector4 wt;

	// Transpose the input vectors
	copy4( xl, yl, zl, wl, srcL0, srcL1, srcL2, srcL3 );
	transpose4( xl, yl, zl, wl );

	copy4( xr, yr, zr, wr, srcR0, srcR1, srcR2, srcR3 );
	transpose4( xr, yr, zr, wr );
	
	// Compute beta = ( 1 - alpha )
	hkVector4 beta;
	beta.setSub( hkVector4::getConstant<HK_QUADREAL_1>(), alpha );
	
	// Blend the left input by beta
	xt.setMul( beta, xl );
	yt.setMul( beta, yl );
	zt.setMul( beta, zl );
	wt.setMul( beta, wl );

	// Blend the right input by alpha
	xt.addMul( alpha, xr );
	yt.addMul( alpha, yr );
	zt.addMul( alpha, zr );
	wt.addMul( alpha, wr );

	// Transpose back for output
	transpose4( xt, yt, zt, wt );
	copy4( dst0, dst1, dst2, dst3, xt, yt, zt, wt );
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::slerp4(
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
	const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3,
	const hkVector4& alpha
	)
{
	// HK_ASSERT2( 0x1ebafe53, checkRange01( alpha ), "Must have 0 <= alpha <= 1" );
	
	hkVector4 nearly1111; nearly1111.setSub(hkVector4::getConstant<HK_QUADREAL_1>(), hkVector4::getConstant<HK_QUADREAL_EPS>());

	// Allocate temporary storage for transpose style operations

	// Left values
	hkVector4 xl;
	hkVector4 yl;
	hkVector4 zl;
	hkVector4 wl;

	// Right values
	hkVector4 xr;
	hkVector4 yr;
	hkVector4 zr;
	hkVector4 wr;

	// Blended values
	hkVector4 xt;
	hkVector4 yt;
	hkVector4 zt;
	hkVector4 wt;

	// Blend weights
	hkVector4 qAlpha;
	hkVector4 qBeta;

	// Transpose the input vectors
	copy4( xl, yl, zl, wl, srcL0.m_vec, srcL1.m_vec, srcL2.m_vec, srcL3.m_vec );
	transpose4( xl, yl, zl, wl );

	copy4( xr, yr, zr, wr, srcR0.m_vec, srcR1.m_vec, srcR2.m_vec, srcR3.m_vec );
	transpose4( xr, yr, zr, wr );

	// Compute the dot product
	hkVector4 dot;
	{
		dot.setMul( xl, xr );
		dot.addMul( yl, yr );
		dot.addMul( zl, zr );
		dot.addMul( wl, wr );
	}

	// Put the quaternions in the same hemisphere
	{
		hkVector4Comparison negative = dot.lessZero();

		// Note, multiplying all rhs vectors here timed faster than negating qAlpha below
		xr.setFlipSign(xr,negative);
		yr.setFlipSign(yr,negative);
		zr.setFlipSign(zr,negative);
		wr.setFlipSign(wr,negative);

		dot.setFlipSign(dot,negative);
	}
	
	// Compute the slerp blend weights
	{
		// Slerp( ql, qr, a) = wl*ql + wr*qr
		// wl = sin((1-a)*t)/sin(t)
		// wr = sin(a*t)/sin(t)
		// t = acos( dot( q1, q2 ) )

		// theta = acos( dot )
		hkVector4 theta;
		acos_series_4_terms( theta, dot );

		// beta = 1 - alpha
		hkVector4 beta;
		beta.setSub( hkVector4::getConstant<HK_QUADREAL_1>(), alpha );

		// alpha * theta
		hkVector4 alphaTheta;
		alphaTheta.setMul( alpha, theta );

		// beta * theta
		hkVector4 betaTheta;
		betaTheta.setMul( beta, theta );

		// sin( theta )
		hkVector4 sinTheta;
		sin_series_2_terms( sinTheta, theta );

		// sin( alpha * theta )
		hkVector4 sinAlphaTheta;
		sin_series_2_terms( sinAlphaTheta, alphaTheta );

		// sin( beta * theta )
		hkVector4 sinBetaTheta;
		sin_series_2_terms( sinBetaTheta, betaTheta );

		// Find the blending amounts
		qAlpha.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( sinAlphaTheta, sinTheta );
		qBeta.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( sinBetaTheta, sinTheta );

		// Check if cos( theta ) approx equal 1.0.  theta == 0 or theta == 180
		hkVector4Comparison smallAngle;
		smallAngle = dot.greater( nearly1111 );

		// If theta is near 0 or 180 degrees, many of the above calculations will divide by zero
		// Simply choose the left side over the right.
		// This gives the correct answer for 0, and defines the otherwise undefined 180 result
		qAlpha.setSelect(smallAngle, hkVector4::getConstant<HK_QUADREAL_1>(), qAlpha );
		qBeta.zeroIfTrue(smallAngle);
	}

	// Blend the left input by beta
	xt.setMul( qBeta, xl );
	yt.setMul( qBeta, yl );
	zt.setMul( qBeta, zl );
	wt.setMul( qBeta, wl );

	// Blend the right input by alpha
	xt.addMul( qAlpha, xr );
	yt.addMul( qAlpha, yr );
	zt.addMul( qAlpha, zr );
	wt.addMul( qAlpha, wr );

	// Transpose back for output
	transpose4( xt, yt, zt, wt );
	copy4( dst0.m_vec, dst1.m_vec, dst2.m_vec, dst3.m_vec, xt, yt, zt, wt );

//	HK_ASSERT2( 0x0555ce48, dst0.m_vec.isOk4(), "Bad output" );
//	HK_ASSERT2( 0x0555ce48, dst1.m_vec.isOk4(), "Bad output" );
//	HK_ASSERT2( 0x0555ce48, dst2.m_vec.isOk4(), "Bad output" );
//	HK_ASSERT2( 0x0555ce48, dst3.m_vec.isOk4(), "Bad output" );
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::qlerp4(
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
	const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3,
	const hkVector4& alpha
	)
{
	// HK_ASSERT2( 0x1ebafe53, checkRange01( alpha ), "Must have 0 <= alpha <= 1" );
	
	// Allocate temporary storage for transpose style operations

	// Left values
	hkVector4 xl;
	hkVector4 yl;
	hkVector4 zl;
	hkVector4 wl;

	// Right values
	hkVector4 xr;
	hkVector4 yr;
	hkVector4 zr;
	hkVector4 wr;

	// Blended values
	hkVector4 xt;
	hkVector4 yt;
	hkVector4 zt;
	hkVector4 wt;

	// Blend weights
	hkVector4 qAlpha;
	hkVector4 qBeta;

	// Transpose the input vectors
	copy4( xl, yl, zl, wl, srcL0.m_vec, srcL1.m_vec, srcL2.m_vec, srcL3.m_vec );
	transpose4( xl, yl, zl, wl );

	copy4( xr, yr, zr, wr, srcR0.m_vec, srcR1.m_vec, srcR2.m_vec, srcR3.m_vec );
	transpose4( xr, yr, zr, wr );

	// Compute the dot product
	hkVector4 dot;
	{
		dot.setMul( xl, xr );
		dot.addMul( yl, yr );
		dot.addMul( zl, zr );
		dot.addMul( wl, wr );
	}

	// Put the quaternions in the same hemisphere
	hkVector4Comparison negative = dot.lessZero();

	qAlpha = alpha;
	qBeta.setSub( hkVector4::getConstant<HK_QUADREAL_1>(), alpha );
	qBeta.setFlipSign(qBeta, negative);

	// Blend the left input by beta
	xt.setMul( qBeta, xl );
	yt.setMul( qBeta, yl );
	zt.setMul( qBeta, zl );
	wt.setMul( qBeta, wl );

	// Blend the right input by alpha
	xt.addMul( qAlpha, xr );
	yt.addMul( qAlpha, yr );
	zt.addMul( qAlpha, zr );
	wt.addMul( qAlpha, wr );

	// Transpose back for output
	transpose4( xt, yt, zt, wt );
	copy4( dst0.m_vec, dst1.m_vec, dst2.m_vec, dst3.m_vec, xt, yt, zt, wt );

//	HK_ASSERT2( 0x0555ce48, dst0.m_vec.isOk4(), "Bad output" );
//	HK_ASSERT2( 0x0555ce48, dst1.m_vec.isOk4(), "Bad output" );
//	HK_ASSERT2( 0x0555ce48, dst2.m_vec.isOk4(), "Bad output" );
//	HK_ASSERT2( 0x0555ce48, dst3.m_vec.isOk4(), "Bad output" );
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::copy4(
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkVector4& src0, const hkVector4& src1, const hkVector4& src2, const hkVector4& src3 )
{
	dst0 = src0;
	dst1 = src1;
	dst2 = src2;
	dst3 = src3;
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::copy4(
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& src0, const hkQuaternion& src1, const hkQuaternion& src2, const hkQuaternion& src3 )
{
	dst0 = src0;
	dst1 = src1;
	dst2 = src2;
	dst3 = src3;
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::copy4(
	hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
	const hkQsTransform& src0, const hkQsTransform& src1, const hkQsTransform& src2, const hkQsTransform& src3 )
{
	dst0 = src0;
	dst1 = src1;
	dst2 = src2;
	dst3 = src3;
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::transpose4(
	hkVector4& v0InOut, hkVector4& v1InOut, hkVector4& v2InOut, hkVector4& v3InOut )
{
	HK_TRANSPOSE4( v0InOut, v1InOut, v2InOut, v3InOut );
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::computeBlendFactorAndWeights4(
	hkVector4& alphaOut, hkVector4& weightOut,
	const hkVector4& alpha,
	const hkVector4& weightL, const hkVector4& weightR )
{
//	HK_ASSERT2( 0x03979cfa, checkRange01( alpha ), "Alpha must be between zero and one." );
//	HK_ASSERT2( 0x1f683fb0, checkRange01( weightL ), "Weights must be between zero and one." );
//	HK_ASSERT2( 0x1bb02353, checkRange01( weightR ), "Weights must be between zero and one." );


	// Compute a new alpha factor based on the given weights
	hkVector4 beta;

	// If weightL > weightR then want beta < alpha.  Let beta = alpha * weightR / weightL
	hkVector4 betaL;
	betaL.setMul( alpha, weightR );
	betaL.div( weightL );

	// If weightR > weightL then want (1-beta) < (1-alpha).  Let (1-beta) = (1-alpha) * weightL / weightR
	hkVector4 betaR;
	betaR.setSub( hkVector4::getConstant<HK_QUADREAL_1>(), alpha );
	betaR.mul( weightL );
	betaR.div( weightR );
	betaR.setSub( hkVector4::getConstant<HK_QUADREAL_1>(), betaR );

	// Select from betaL, betaR
	const hkVector4Comparison l_gt_R =  weightL.greater( weightR );
	beta.setSelect(l_gt_R, betaL, betaR);

	// Temp for output weights
	hkVector4 w;

	// w = blend( weightL, weightR, beta )
	w.setSub( hkVector4::getConstant<HK_QUADREAL_1>(), beta );
	w.mul( weightL );
	w.addMul( beta, weightR );

	// Lastly, handle zero weights

	//               |  weightL > 0                      |  weightL == 0       
	// ------------------------------------------------------------------------
	// weightR > 0   |  beta = (see logic above)         |  w = weightR        
	//               |  w = blend(weightL,weightR,beta)  |  beta = 1           
	// ------------------------------------------------------------------------
	// weightR == 0  |  w = weightL                      |  w = 0              
    //               |  beta = 0                         |  beta = alpha  

	const hkVector4Comparison weightL_lte0 = weightL.lessEqualZero();
	const hkVector4Comparison weightR_lte0 = weightR.lessEqualZero();
	hkVector4Comparison weightsEqualZero;
	weightsEqualZero.setAnd( weightL_lte0, weightR_lte0 );

	// Select beta as in the chart above
	beta.setSelect(weightL_lte0, hkVector4::getConstant<HK_QUADREAL_1>(), beta );
	beta.zeroIfTrue( weightR_lte0 );
	beta.setSelect( weightsEqualZero, alpha, beta );
		
	// Update w according to the above chart
	w.setSelect( weightL_lte0, weightR, w );
	w.setSelect( weightR_lte0, weightL, w );

	// Write the outputs
	alphaOut = beta;
	weightOut = w;

//	HK_ASSERT2( 0x1541a8ed, checkRange01( alphaOut ), "Internal error, calculated alpha not between zero and one." );
//	HK_ASSERT2( 0x11898c90, checkRange01( weightOut ), "Internal error, calculated Weights not between zero and one." );
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::computeBlendFactorAndWeightsAdditive4(
	hkVector4& alphaOut, hkVector4& weightOut,
	const hkVector4& alpha,
	const hkVector4& weightL, const hkVector4& weightR )
{
//	HK_ASSERT2( 0x03979cfa, checkRange01( alpha ), "Alpha must be between zero and one." );
//	HK_ASSERT2( 0x1f683fb0, checkRange01( weightL ), "Weights must be between zero and one." );
//	HK_ASSERT2( 0x1bb02353, checkRange01( weightR ), "Weights must be between zero and one." );

	// Output alpha is input alpha * right weights
	alphaOut.setMul( alpha, weightR );

	// Output weights are the same as the left weights
	weightOut = weightL;
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::normalize4(
	hkQuaternion& qInOut0, hkQuaternion& qInOut1, hkQuaternion& qInOut2, hkQuaternion& qInOut3
	)
{
	hkVector4 x;
	hkVector4 y;
	hkVector4 z;
	hkVector4 w;

	copy4( x, y, z, w, qInOut0.m_vec, qInOut1.m_vec, qInOut2.m_vec, qInOut3.m_vec );
	transpose4( x, y, z, w );

	hkVector4 x2;
	hkVector4 y2;
	hkVector4 z2;
	hkVector4 w2;

	x2.setMul( x, x );
	y2.setMul( y, y );
	z2.setMul( z, z );
	w2.setMul( w, w );


	hkVector4 sum;
	sum.setAdd( x2, y2 );
	sum.add( z2 );
	sum.add( w2 );
	
	hkVector4 invMag;
	invMag.setSqrtInverse<HK_ACC_23_BIT,HK_SQRT_IGNORE>( sum );

	x.mul( invMag );
	y.mul( invMag );
	z.mul( invMag );
	w.mul( invMag );

	transpose4( x, y, z, w );
	copy4( qInOut0.m_vec, qInOut1.m_vec, qInOut2.m_vec, qInOut3.m_vec, x, y, z, w );
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::add4(
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
	const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
	)
{
	dst0.setAdd( srcL0, srcR0 );
	dst1.setAdd( srcL1, srcR1 );
	dst2.setAdd( srcL2, srcR2 );
	dst3.setAdd( srcL3, srcR3 );
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::sub4(
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
	const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
	)
{
	dst0.setSub( srcL0, srcR0 );
	dst1.setSub( srcL1, srcR1 );
	dst2.setSub( srcL2, srcR2 );
	dst3.setSub( srcL3, srcR3 );
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::mul4(
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
	const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
	)
{
	dst0.setMul( srcL0, srcR0 );
	dst1.setMul( srcL1, srcR1 );
	dst2.setMul( srcL2, srcR2 );
	dst3.setMul( srcL3, srcR3 );
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::mul4(
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
	const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3
	)
{
	// Allocate temporary storage for transpose style operations

	// Left values
	hkVector4 xl;
	hkVector4 yl;
	hkVector4 zl;
	hkVector4 wl;

	// Right values
	hkVector4 xr;
	hkVector4 yr;
	hkVector4 zr;
	hkVector4 wr;

	// Transpose the input vectors
	copy4( xl, yl, zl, wl, srcL0.m_vec, srcL1.m_vec, srcL2.m_vec, srcL3.m_vec );
	transpose4( xl, yl, zl, wl );

	copy4( xr, yr, zr, wr, srcR0.m_vec, srcR1.m_vec, srcR2.m_vec, srcR3.m_vec );
	transpose4( xr, yr, zr, wr );

	// ( xl, yl, zl, wl ) * ( xr, yr, zr, wr ) =
	// ( vl, sl ) * ( vr, sr ) =
	// ( sl*vr * sr*vl + vl x vr, sl*sr - vl.vr )

	// Compute the scalar component
	hkVector4 s;
	{
		// Compute the scalar product
		s.setMul( wl, wr );

		// Compute the dot product of the vector part
		s.subMul( xl, xr );
		s.subMul( yl, yr );
		s.subMul( zl, zr );
	}

	// Compute the vector component
	hkVector4 xv;
	hkVector4 yv;
	hkVector4 zv;
	{
		// Compute the cross product
		// {-yr*zl + yl*zr, zl*xr - zr*xl, -xr*yl + xl*yr}
		
		xv.setMul( yl, zr );
		xv.subMul( yr, zl );
		yv.setMul( zl, xr );
		yv.subMul( zr, xl );
		zv.setMul( xl, yr );
		zv.subMul( xr, yl );

		// Add in the vector scalar products

		xv.addMul( wl, xr );
		yv.addMul( wl, yr );
		zv.addMul( wl, zr );

		xv.addMul( wr, xl );
		yv.addMul( wr, yl );
		zv.addMul( wr, zl );
	}
	

	// Transpose back for output
	transpose4( xv, yv, zv, s );
	copy4( dst0.m_vec, dst1.m_vec, dst2.m_vec, dst3.m_vec, xv, yv, zv, s );
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::mulInv4(
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
	const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3
	)
{
	// Allocate temporary storage for transpose style operations

	// Left values
	hkVector4 xl;
	hkVector4 yl;
	hkVector4 zl;
	hkVector4 wl;

	// Right values
	hkVector4 xr;
	hkVector4 yr;
	hkVector4 zr;
	hkVector4 wr;

	// Transpose the input vectors
	copy4( xl, yl, zl, wl, srcL0.m_vec, srcL1.m_vec, srcL2.m_vec, srcL3.m_vec );
	transpose4( xl, yl, zl, wl );

	copy4( xr, yr, zr, wr, srcR0.m_vec, srcR1.m_vec, srcR2.m_vec, srcR3.m_vec );
	transpose4( xr, yr, zr, wr );
	wr.setNeg<4>( wr );

	// ( xl, yl, zl, wl ) * ( xr, yr, zr, wr ) =
	// ( vl, sl ) * ( vr, sr ) =
	// ( sl*vr * sr*vl + vl x vr, sl*sr - vl.vr )

	// Compute the scalar component
	hkVector4 s;
	{
		// Compute the scalar product
		s.setMul( wl, wr );

		// Compute the dot product of the vector part
		s.subMul( xl, xr );
		s.subMul( yl, yr );
		s.subMul( zl, zr );
	}

	// Compute the vector component
	hkVector4 xv;
	hkVector4 yv;
	hkVector4 zv;
	{
		// Compute the cross product
		// {-yr*zl + yl*zr, zl*xr - zr*xl, -xr*yl + xl*yr}
		
		xv.setMul( yl, zr );
		xv.subMul( yr, zl );
		yv.setMul( zl, xr );
		yv.subMul( zr, xl );
		zv.setMul( xl, yr );
		zv.subMul( xr, yl );

		// Add in the vector scalar products

		xv.addMul( wl, xr );
		yv.addMul( wl, yr );
		zv.addMul( wl, zr );

		xv.addMul( wr, xl );
		yv.addMul( wr, yl );
		zv.addMul( wr, zl );
	}
	

	// Transpose back for output
	transpose4( xv, yv, zv, s );
	copy4( dst0.m_vec, dst1.m_vec, dst2.m_vec, dst3.m_vec, xv, yv, zv, s );
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::inv4(
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3
	)
{
	// Allocate temporary storage for transpose style operations

	// Src values
	hkVector4 xsrc;
	hkVector4 ysrc;
	hkVector4 zsrc;
	hkVector4 wsrc;

	// Transpose the input vectors
	copy4( xsrc, ysrc, zsrc, wsrc, srcL0.m_vec, srcL1.m_vec, srcL2.m_vec, srcL3.m_vec );
	transpose4( xsrc, ysrc, zsrc, wsrc );

	// Negate the w components
	wsrc.setNeg<4>( wsrc );

	// Transpose back for output
	transpose4( xsrc, ysrc, zsrc, wsrc );
	copy4( dst0.m_vec, dst1.m_vec, dst2.m_vec, dst3.m_vec, xsrc, ysrc, zsrc, wsrc );
}




template< typename HANDLE_W >
void HK_FORCE_INLINE hkaBatchBlenderUtilities::rotateBase4(
	HANDLE_W handleW,
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkQuaternion& q0, const hkQuaternion& q1, const hkQuaternion& q2, const hkQuaternion& q3,
	const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, const hkVector4& v3
	)
{
	hkVector4 negQuarter; negQuarter.setNeg<4>(hkVector4::getConstant<HK_QUADREAL_INV_4>());

	// Allocate temporary storage for transpose style operations

	// Rotation values
	hkVector4 xq;
	hkVector4 yq;
	hkVector4 zq;
	hkVector4 wq;

	// Transpose the input quaternions
	copy4( xq, yq, zq, wq, q0.m_vec, q1.m_vec, q2.m_vec, q3.m_vec );
	transpose4( xq, yq, zq, wq );

	// Choose positive or negative quaternion values
	handleW( wq );
	

	// Vector values
	hkVector4 xv;
	hkVector4 yv;
	hkVector4 zv;
	hkVector4 wv;

	// Transpose the input vectors
	copy4( xv, yv, zv, wv, v0, v1, v2, v3 );
	transpose4( xv, yv, zv, wv );

	hkVector4 xr;
	hkVector4 yr;
	hkVector4 zr;
	{
		// The quantities below are re-used in the calculation...

		hkVector4 xq2m; // xq^2 - 1/4
		hkVector4 yq2m; // yq^2 - 1/4
		hkVector4 zq2m; // zq^2 - 1/4

		xq2m.setAddMul( negQuarter, xq, xq );
		yq2m.setAddMul( negQuarter, yq, yq );
		zq2m.setAddMul( negQuarter, zq, zq );

		hkVector4 xqxv; // xq*xv
		hkVector4 yqyv; // yq*yv
		hkVector4 zqzv; // zq*zv

		xqxv.setMul( xq, xv );
		yqyv.setMul( yq, yv );
		zqzv.setMul( zq, zv );

		// The following code was partly generated with a numerical algebra package
		// xr/2 = ( 1/2 - yq2 - zq2 )*xv + ( yq*yv + zq*zv )*xq + ( yq*zv - zq*yv )*wq;
		// yr/2 = ( 1/2 - zq2 - xq2 )*yv + ( zq*zv + xq*xv )*yq + ( zq*xv - xq*zv )*wq;
		// zr/2 = ( 1/2 - xq2 - yq2 )*zv + ( xq*xv + yq*yv )*zq + ( xq*yv - yq*xv )*wq;
		// wr = wv

		// xr
		{
			hkVector4 tmpA;
			hkVector4 tmpB;
			hkVector4 tmpC;

			tmpA.setAdd( yq2m, zq2m );
			tmpB.setAdd( yqyv, zqzv );
			tmpC.setMul( yq, zv );
			tmpC.subMul( zq, yv );

			xr.setMul( tmpB, xq );
			xr.addMul( tmpC, wq );
			xr.subMul( tmpA, xv );
			xr.add( xr );
		}

		// yr
		{
			hkVector4 tmpA;
			hkVector4 tmpB;
			hkVector4 tmpC;

			tmpA.setAdd( zq2m, xq2m );
			tmpB.setAdd( zqzv, xqxv );
			tmpC.setMul( zq, xv );
			tmpC.subMul( xq, zv );

			yr.setMul( tmpB, yq );
			yr.addMul( tmpC, wq );
			yr.subMul( tmpA, yv );
			yr.add( yr );
		}

		// zr
		{
			hkVector4 tmpA;
			hkVector4 tmpB;
			hkVector4 tmpC;

			tmpA.setAdd( xq2m, yq2m );
			tmpB.setAdd( xqxv, yqyv );
			tmpC.setMul( xq, yv );
			tmpC.subMul( yq, xv );

			zr.setMul( tmpB, zq );
			zr.addMul( tmpC, wq );
			zr.subMul( tmpA, zv );
			zr.add( zr );
		}
	}

	// Transpose back for output
	transpose4( xr, yr, zr, wv );
	copy4( dst0, dst1, dst2, dst3, xr, yr, zr, wv );
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::rotate4(
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkQuaternion& q0, const hkQuaternion& q1, const hkQuaternion& q2, const hkQuaternion& q3,
	const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, const hkVector4& v3
	)
{
	rotateBase4( PosateFunctor(),
				 dst0, dst1, dst2, dst3,
				 q0, q1, q2, q3,
				 v0, v1, v2, v3 );
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::rotateInv4(
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkQuaternion& q0, const hkQuaternion& q1, const hkQuaternion& q2, const hkQuaternion& q3,
	const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, const hkVector4& v3
	)
{
	rotateBase4( NegateFunctor(),
				 dst0, dst1, dst2, dst3,
				 q0, q1, q2, q3,
				 v0, v1, v2, v3 );
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::transform4(
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkQsTransform& t0, const hkQsTransform& t1, const hkQsTransform& t2, const hkQsTransform& t3,
	const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, const hkVector4& v3
	)
{
	hkVector4 d0;
	hkVector4 d1;
	hkVector4 d2;
	hkVector4 d3;

	// Scale first
	d0.setMul( t0.m_scale, v0 );
	d1.setMul( t1.m_scale, v1 );
	d2.setMul( t2.m_scale, v2 );
	d3.setMul( t3.m_scale, v3 );

	// Rotate
	rotate4( d0, d1, d2, d3,
			 t0.m_rotation, t1.m_rotation, t2.m_rotation, t3.m_rotation,
			 d0, d1, d2, d3 );

	// Translate
	d0.add( t0.m_translation );
	d1.add( t1.m_translation );
	d2.add( t2.m_translation );
	d3.add( t3.m_translation );

	// Copy temporaries back
	copy4( dst0, dst1, dst2, dst3,
		   d0, d1, d2, d3 );
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::transformInv4(
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkQsTransform& t0, const hkQsTransform& t1, const hkQsTransform& t2, const hkQsTransform& t3,
	const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, const hkVector4& v3
	)
{
	hkVector4 d0;
	hkVector4 d1;
	hkVector4 d2;
	hkVector4 d3;

	// Translate
	d0.setSub( v0, t0.m_translation );
	d1.setSub( v1, t1.m_translation );
	d2.setSub( v2, t2.m_translation );
	d3.setSub( v3, t3.m_translation );

	// Rotate
	rotateInv4( d0, d1, d2, d3,
				t0.m_rotation, t1.m_rotation, t2.m_rotation, t3.m_rotation,
				d0, d1, d2, d3 );

	// Scale last
	d0.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( d0, t0.m_scale );
	d1.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( d1, t1.m_scale );
	d2.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( d2, t2.m_scale );
	d3.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( d3, t3.m_scale );

	// Copy temporaries back
	copy4( dst0, dst1, dst2, dst3,
		   d0, d1, d2, d3 );
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::mul4(
	hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
	const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
	const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3
	)
{
	hkQsTransform d0;
	hkQsTransform d1;
	hkQsTransform d2;
	hkQsTransform d3;

	// Rotate the translations first
	rotate4( d0.m_translation, d1.m_translation, d2.m_translation, d3.m_translation,
			 srcL0.m_rotation, srcL1.m_rotation, srcL2.m_rotation, srcL3.m_rotation,
			 srcR0.m_translation, srcR1.m_translation, srcR2.m_translation, srcR3.m_translation );

	// Add the translations
	d0.m_translation.add( srcL0.m_translation );
	d1.m_translation.add( srcL1.m_translation );
	d2.m_translation.add( srcL2.m_translation );
	d3.m_translation.add( srcL3.m_translation );

	// Multiply the quaternions
	mul4( d0.m_rotation, d1.m_rotation, d2.m_rotation, d3.m_rotation,
		  srcL0.m_rotation, srcL1.m_rotation, srcL2.m_rotation, srcL3.m_rotation,
		  srcR0.m_rotation, srcR1.m_rotation, srcR2.m_rotation, srcR3.m_rotation );

	// Scales multiply flat
	d0.m_scale.setMul( srcL0.m_scale, srcR0.m_scale );
	d1.m_scale.setMul( srcL1.m_scale, srcR1.m_scale );
	d2.m_scale.setMul( srcL2.m_scale, srcR2.m_scale );
	d3.m_scale.setMul( srcL3.m_scale, srcR3.m_scale );

	// Copy the temporaries back
	dst0 = d0;
	dst1 = d1;
	dst2 = d2;
	dst3 = d3;
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::mulInv4(
	hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
	const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
	const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3
	)
{
	hkQsTransform d0;
	hkQsTransform d1;
	hkQsTransform d2;
	hkQsTransform d3;

	// Multiply the quaternions first
	mulInv4( d0.m_rotation, d1.m_rotation, d2.m_rotation, d3.m_rotation,
			 srcL0.m_rotation, srcL1.m_rotation, srcL2.m_rotation, srcL3.m_rotation,
			 srcR0.m_rotation, srcR1.m_rotation, srcR2.m_rotation, srcR3.m_rotation );

	// Rotate the translations first
	rotate4( d0.m_translation, d1.m_translation, d2.m_translation, d3.m_translation,
			 d0.m_rotation, d1.m_rotation, d2.m_rotation, d3.m_rotation,
			 srcR0.m_translation, srcR1.m_translation, srcR2.m_translation, srcR3.m_translation );

	// Diff the translations
	d0.m_translation.setSub( srcL0.m_translation, d0.m_translation );
	d1.m_translation.setSub( srcL1.m_translation, d1.m_translation );
	d2.m_translation.setSub( srcL2.m_translation, d2.m_translation );
	d3.m_translation.setSub( srcL3.m_translation, d3.m_translation );

	// Scales multiply flat
	// Scales multiply flat
	d0.m_scale.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( srcL0.m_scale, srcR0.m_scale );
	d1.m_scale.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( srcL1.m_scale, srcR1.m_scale );
	d2.m_scale.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( srcL2.m_scale, srcR2.m_scale );
	d3.m_scale.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( srcL3.m_scale, srcR3.m_scale );

	// Copy the temporaries back
	dst0 = d0;
	dst1 = d1;
	dst2 = d2;
	dst3 = d3;
}

/*
// Adds four hkVector4 pairs
HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::add4(
hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
)
{
dst0.setAdd4( srcL0, srcR0 );
dst1.setAdd4( srcL1, srcR1 );
dst2.setAdd4( srcL2, srcR2 );
dst3.setAdd4( srcL3, srcR3 );
}
	
// Subtracts four hkVector4 pairs
HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::sub4(
hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3
)
{
dst0.setSub4( srcL0, srcR0 );
dst1.setSub4( srcL1, srcR1 );
dst2.setSub4( srcL2, srcR2 );
dst3.setSub4( srcL3, srcR3 );
}
*/	


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::inv4(
	hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
	const hkQsTransform& src0, const hkQsTransform& src1, const hkQsTransform& src2, const hkQsTransform& src3
	)
{
	// Rotation values
	hkQsTransform d0;
	hkQsTransform d1;
	hkQsTransform d2;
	hkQsTransform d3;

	// Transpose the input quaternions
	copy4( d0.m_rotation.m_vec, d1.m_rotation.m_vec, d2.m_rotation.m_vec, d3.m_rotation.m_vec, src0.m_rotation.m_vec, src1.m_rotation.m_vec, src2.m_rotation.m_vec, src3.m_rotation.m_vec );
	transpose4( d0.m_rotation.m_vec, d1.m_rotation.m_vec, d2.m_rotation.m_vec, d3.m_rotation.m_vec );

	// Invert the rotations
	d3.m_rotation.m_vec.setNeg<4>( d3.m_rotation.m_vec );

	// Transpose the rotations back
	transpose4( d0.m_rotation.m_vec, d1.m_rotation.m_vec, d2.m_rotation.m_vec, d3.m_rotation.m_vec );

	// Transform the translations
	rotate4( d0.m_translation, d1.m_translation, d2.m_translation, d3.m_translation,
			 d0.m_rotation, d1.m_rotation, d2.m_rotation, d3.m_rotation,
			 src0.m_translation, src1.m_translation, src2.m_translation, src3.m_translation );

	// Invert the scales
	d0.m_scale.setReciprocal( src0.m_scale );
	d1.m_scale.setReciprocal( src1.m_scale );
	d2.m_scale.setReciprocal( src2.m_scale );
	d3.m_scale.setReciprocal( src3.m_scale );

	// Copy the temporaries back
	dst0 = d0;
	dst1 = d1;
	dst2 = d2;
	dst3 = d3;
}

HK_FORCE_INLINE void hkaBatchBlenderUtilities::PosateFunctor::operator()( hkVector4& vInOut )
{
}

HK_FORCE_INLINE void hkaBatchBlenderUtilities::NegateFunctor::operator()( hkVector4& vInOut )
{
	vInOut.setNeg<4>( vInOut );
}


HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::sin_series_2_terms( hkVector4& out, const hkVector4& theta )
{
	// Abramowitz and Stegun 4.3.96
	// Sin is an odd function, so only need theta^2
	hkVector4 theta_sq;
	theta_sq.setMul( theta, theta );

	// Evaluate by Horner's rule
	hkVector4 tmp = ( hkVector4& )s_sin_series_2_terms_c4;
	tmp.setAddMul( ( hkVector4& )s_sin_series_2_terms_c2, tmp, theta_sq );
	tmp.setAddMul( hkVector4::getConstant<HK_QUADREAL_1>(), theta_sq, tmp );

	out.setMul( tmp, theta );
}

HK_FORCE_INLINE void HK_CALL hkaBatchBlenderUtilities::acos_series_4_terms( hkVector4& out, const hkVector4& cos_theta )
{
	// Abramowitz and Stegun 4.4.45

//	HK_ASSERT2( 0x04c558db, checkRange01( cos_theta ), "Cosine not in range" );

	// Evaluate using horner's rule
	hkVector4 theta = ( hkVector4& )s_acos_series_4_terms_c3;
	theta.setAddMul( ( hkVector4& )s_acos_series_4_terms_c2, theta, cos_theta );
	theta.setAddMul( ( hkVector4& )s_acos_series_4_terms_c1, theta, cos_theta );
	theta.setAddMul( ( hkVector4& )s_acos_series_4_terms_c0, theta, cos_theta );

	hkVector4 tmp;
	tmp.setSub( hkVector4::getConstant<HK_QUADREAL_1>(), cos_theta );
	
	hkVector4 tmp2;
	tmp2.setSqrtInverse<HK_ACC_23_BIT,HK_SQRT_IGNORE>( tmp );

	out.setDiv<HK_ACC_FULL,HK_DIV_IGNORE>( theta, tmp2 );
}

template< typename TYPE >
void HK_CALL hkaBatchBlenderUtilities::blendBase( TYPE* HK_RESTRICT dst, const TYPE* HK_RESTRICT srcL, const TYPE* HK_RESTRICT srcR, const hkSimdReal& alpha, int n, hkaBlender::BLEND_MODE blendMode, hkaBlender::ROTATION_MODE rotationMode )
{
	HK_ASSERT2( 0x100e1ed5, blendMode == hkaBlender::NORMAL || blendMode == hkaBlender::ADDITIVE || blendMode == hkaBlender::SUBTRACTIVE, "Invalid blend type" );
	HK_ASSERT2( 0x14cc5c4c, rotationMode == hkaBlender::LERP || rotationMode == hkaBlender::SLERP, "Invalid rotation interpolation type" );

	if ( rotationMode == hkaBlender::LERP )
	{
		// LERP
		switch ( blendMode )
		{
		case hkaBlender::NORMAL:
			blendCore( dst, HK_NULL, srcL, HK_NULL, srcR, HK_NULL, alpha, n,
				WeightUnweightedFunctor(), BlendNormalFunctor(), LerpFunctor() );
			break;

		case hkaBlender::ADDITIVE:
			blendCore( dst, HK_NULL, srcL, HK_NULL, srcR, HK_NULL, alpha, n,
				WeightUnweightedFunctor(), BlendAdditiveFunctor(), LerpFunctor() );
			break;

		case hkaBlender::SUBTRACTIVE:
			blendCore( dst, HK_NULL, srcL, HK_NULL, srcR, HK_NULL, alpha, n,
				WeightUnweightedFunctor(), BlendSubtractiveFunctor(), LerpFunctor() );
			break;
		}
	}
	else if ( rotationMode == hkaBlender::SLERP )
	{
		// SLERP
		switch ( blendMode )
		{
		case hkaBlender::NORMAL:
			blendCore( dst, HK_NULL, srcL, HK_NULL, srcR, HK_NULL, alpha, n,
				WeightUnweightedFunctor(), BlendNormalFunctor(), SlerpFunctor() );
			break;

		case hkaBlender::ADDITIVE:
			blendCore( dst, HK_NULL, srcL, HK_NULL, srcR, HK_NULL, alpha, n,
				WeightUnweightedFunctor(), BlendAdditiveFunctor(), SlerpFunctor() );
			break;

		case hkaBlender::SUBTRACTIVE:
			blendCore( dst, HK_NULL, srcL, HK_NULL, srcR, HK_NULL, alpha, n,
				WeightUnweightedFunctor(), BlendSubtractiveFunctor(), SlerpFunctor() );
			break;
		}
	}
}

template< typename TYPE >
void HK_CALL hkaBatchBlenderUtilities::blendBase( TYPE* HK_RESTRICT dst, hkReal* HK_RESTRICT weightsOut, const TYPE* HK_RESTRICT srcL, const hkReal* HK_RESTRICT weightL, const TYPE* HK_RESTRICT srcR, const hkReal* HK_RESTRICT weightR, const hkSimdReal& alpha, int n, hkaBlender::BLEND_MODE blendMode, hkaBlender::ROTATION_MODE rotationMode )
{
	HK_ASSERT2( 0x100e1ed5, blendMode == hkaBlender::NORMAL || blendMode == hkaBlender::ADDITIVE || blendMode == hkaBlender::SUBTRACTIVE, "Invalid blend type" );
	HK_ASSERT2( 0x14cc5c4c, rotationMode == hkaBlender::LERP || rotationMode == hkaBlender::SLERP, "Invalid rotation interpolation type" );

	if ( weightsOut == HK_NULL )
	{
		blendBase( dst, srcL, srcR, alpha, n, blendMode, rotationMode );
	}
	else
	{
		// Weighted
		if ( rotationMode == hkaBlender::LERP )
		{
			// LERP
			switch ( blendMode )
			{
			case hkaBlender::NORMAL:
				blendCore( dst, weightsOut, srcL, weightL, srcR, weightR, alpha, n,
						   WeightNormalFunctor(), BlendNormalFunctor(), LerpFunctor() );
				break;

			case hkaBlender::ADDITIVE:
				blendCore( dst, weightsOut, srcL, weightL, srcR, weightR, alpha, n,
						   WeightAdditiveFunctor(), BlendAdditiveFunctor(), LerpFunctor() );
				break;

			case hkaBlender::SUBTRACTIVE:
				blendCore( dst, weightsOut, srcL, weightL, srcR, weightR, alpha, n,
						   WeightAdditiveFunctor(), BlendSubtractiveFunctor(), LerpFunctor() );
				break;
			}
		}
		else if ( rotationMode == hkaBlender::SLERP )
		{
			// SLERP
			switch ( blendMode )
			{
			case hkaBlender::NORMAL:
				blendCore( dst, weightsOut, srcL, weightL, srcR, weightR, alpha, n,
						   WeightNormalFunctor(), BlendNormalFunctor(), SlerpFunctor() );
				break;

			case hkaBlender::ADDITIVE:
				blendCore( dst, weightsOut, srcL, weightL, srcR, weightR, alpha, n,
						   WeightAdditiveFunctor(), BlendAdditiveFunctor(), SlerpFunctor() );
				break;

			case hkaBlender::SUBTRACTIVE:
				blendCore( dst, weightsOut, srcL, weightL, srcR, weightR, alpha, n,
						   WeightAdditiveFunctor(), BlendSubtractiveFunctor(), SlerpFunctor() );
				break;
			}
		}
	}
}


template< typename TYPE, typename BLEND_FUNCTOR, typename WEIGHT_FUNCTOR, typename INTERPOLATION_FUNCTOR  >
void HK_FORCE_INLINE hkaBatchBlenderUtilities::blendCore( TYPE* HK_RESTRICT dst, hkReal* weightsOut, const TYPE* HK_RESTRICT srcL, const hkReal* weightsL, const TYPE* HK_RESTRICT srcR, const hkReal* weightsR, const hkSimdReal& alpha, int n, WEIGHT_FUNCTOR weightFunctor, BLEND_FUNCTOR blendFunctor, INTERPOLATION_FUNCTOR interpFunctor )
{
	HK_ASSERT2( 0x1d210589, ( hkUlong( dst ) & (HK_REAL_ALIGNMENT-1) ) == 0, "dst must be aligned for SIMD." );
	HK_ASSERT2( 0x0ebd6e86, ( hkUlong( weightsOut ) & (HK_REAL_ALIGNMENT-1) ) == 0, "weightsOut must be aligned for SIMD" );
	HK_ASSERT2( 0x1955457a, ( hkUlong( srcL ) & (HK_REAL_ALIGNMENT-1) ) == 0, "srcL must be aligned for SIMD." );
	HK_ASSERT2( 0x1538ddf6, ( hkUlong( srcR ) & (HK_REAL_ALIGNMENT-1) ) == 0, "srcR must be aligned for SIMD." );
	HK_ASSERT2( 0x109d48dc, ( hkUlong( weightsL ) & (HK_REAL_ALIGNMENT-1) ) == 0, "weightL must be aligned for SIMD." );
	HK_ASSERT2( 0x1a8e0ebc, ( hkUlong( weightsR ) & (HK_REAL_ALIGNMENT-1) ) == 0, "weightR must be aligned for SIMD." );

	hkVector4 alphav;
	alphav.setAll( alpha );

	const int num = ( n + 3 ) / 4;

	hkVector4* weightsOutv = reinterpret_cast< hkVector4* >( weightsOut );
	const hkVector4* weightsLv = reinterpret_cast< const hkVector4* >( weightsL );
	const hkVector4* weightsRv = reinterpret_cast< const hkVector4* >( weightsR );

	for ( int i = 0; i < num; ++i, dst += 4, srcL += 4, srcR += 4, ++weightsOutv, ++weightsLv, ++weightsRv )
	{
		hkVector4 beta;
		weightFunctor( beta, *weightsOutv, alphav, *weightsLv, *weightsRv );

		HK_ALIGN_REAL( TYPE comp[ 4 ] );
		blendFunctor( comp[ 0 ], comp[ 1 ], comp[ 2 ], comp[ 3 ],
					  srcL[ 0 ], srcL[ 1 ], srcL[ 2 ], srcL[ 3 ],
					  srcR[ 0 ], srcR[ 1 ], srcR[ 2 ], srcR[ 3 ] );

		interpFunctor( dst[ 0 ], dst[ 1 ], dst[ 2 ], dst[ 3 ],
					   srcL[ 0 ], srcL[ 1 ], srcL[ 2 ], srcL[ 3 ],
					   comp[ 0 ], comp[ 1 ], comp[ 2 ], comp[ 3 ],
					   beta );
	}
}

void hkaBatchBlenderUtilities::LerpFunctor::operator() (
	hkReal& dst0, hkReal& dst1, hkReal& dst2, hkReal& dst3,
	const hkReal& srcL0, const hkReal& srcL1, const hkReal& srcL2, const hkReal& srcL3,
	const hkReal& srcR0, const hkReal& srcR1, const hkReal& srcR2, const hkReal& srcR3,
	const hkVector4& alpha )
{
	hkVector4 srcL0_v; srcL0_v.load<4>(&srcL0);
	hkVector4 srcR0_v; srcR0_v.load<4>(&srcR0);
	hkVector4 tmp;
	tmp.setSub( srcR0_v, srcL0_v );
	tmp.mul( alpha );
	tmp.add( srcL0_v );
	tmp.store<4>(&dst0);
}

void hkaBatchBlenderUtilities::LerpFunctor::operator() (
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
	const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3,
	const hkVector4& alpha )
{
	lerp4( dst0, dst1, dst2, dst3,
		   srcL0, srcL1, srcL2, srcL3,
		   srcR0, srcR1, srcR2, srcR3,
		   alpha );
}

void hkaBatchBlenderUtilities::LerpFunctor::operator() (
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
	const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3,
	const hkVector4& alpha )
{
	qlerp4( dst0, dst1, dst2, dst3,
		   srcL0, srcL1, srcL2, srcL3,
		   srcR0, srcR1, srcR2, srcR3,
		   alpha );
}

void hkaBatchBlenderUtilities::LerpFunctor::operator() (
	hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
	const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
	const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3,
	const hkVector4& alpha )
{
	lerp4( dst0.m_translation, dst1.m_translation, dst2.m_translation, dst3.m_translation,
		   srcL0.m_translation, srcL1.m_translation, srcL2.m_translation, srcL3.m_translation,
		   srcR0.m_translation, srcR1.m_translation, srcR2.m_translation, srcR3.m_translation,
		   alpha );

	qlerp4( dst0.m_rotation, dst1.m_rotation, dst2.m_rotation, dst3.m_rotation,
		   srcL0.m_rotation, srcL1.m_rotation, srcL2.m_rotation, srcL3.m_rotation,
		   srcR0.m_rotation, srcR1.m_rotation, srcR2.m_rotation, srcR3.m_rotation,
		   alpha );

	lerp4( dst0.m_scale, dst1.m_scale, dst2.m_scale, dst3.m_scale,
		   srcL0.m_scale, srcL1.m_scale, srcL2.m_scale, srcL3.m_scale,
		   srcR0.m_scale, srcR1.m_scale, srcR2.m_scale, srcR3.m_scale,
		   alpha );
}

void hkaBatchBlenderUtilities::SlerpFunctor::operator() (
	hkReal& dst0, hkReal& dst1, hkReal& dst2, hkReal& dst3,
	const hkReal& srcL0, const hkReal& srcL1, const hkReal& srcL2, const hkReal& srcL3,
	const hkReal& srcR0, const hkReal& srcR1, const hkReal& srcR2, const hkReal& srcR3,
	const hkVector4& alpha )
{
	hkVector4 srcL0_v; srcL0_v.load<4>(&srcL0);
	hkVector4 srcR0_v; srcR0_v.load<4>(&srcR0);
	hkVector4 tmp;
	tmp.setSub( srcR0_v, srcL0_v );
	tmp.mul( alpha );
	tmp.add( srcL0_v );
	tmp.store<4>( &dst0 );
}

void hkaBatchBlenderUtilities::SlerpFunctor::operator() (
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
	const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3,
	const hkVector4& alpha )
{
	lerp4( dst0, dst1, dst2, dst3,
		   srcL0, srcL1, srcL2, srcL3,
		   srcR0, srcR1, srcR2, srcR3,
		   alpha );
}

void hkaBatchBlenderUtilities::SlerpFunctor::operator() (
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
	const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3,
	const hkVector4& alpha )
{
	slerp4( dst0, dst1, dst2, dst3,
			srcL0, srcL1, srcL2, srcL3,
			srcR0, srcR1, srcR2, srcR3,
			alpha );
}

void hkaBatchBlenderUtilities::SlerpFunctor::operator() (
	hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
	const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
	const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3,
	const hkVector4& alpha )
{
	lerp4( dst0.m_translation, dst1.m_translation, dst2.m_translation, dst3.m_translation,
		   srcL0.m_translation, srcL1.m_translation, srcL2.m_translation, srcL3.m_translation,
		   srcR0.m_translation, srcR1.m_translation, srcR2.m_translation, srcR3.m_translation,
		   alpha );

	slerp4( dst0.m_rotation, dst1.m_rotation, dst2.m_rotation, dst3.m_rotation,
			srcL0.m_rotation, srcL1.m_rotation, srcL2.m_rotation, srcL3.m_rotation,
			srcR0.m_rotation, srcR1.m_rotation, srcR2.m_rotation, srcR3.m_rotation,
			alpha );

	lerp4( dst0.m_scale, dst1.m_scale, dst2.m_scale, dst3.m_scale,
		   srcL0.m_scale, srcL1.m_scale, srcL2.m_scale, srcL3.m_scale,
		   srcR0.m_scale, srcR1.m_scale, srcR2.m_scale, srcR3.m_scale,
		   alpha );
}


void hkaBatchBlenderUtilities::BlendNormalFunctor::operator() (
	hkReal& dst0, hkReal& dst1, hkReal& dst2, hkReal& dst3,
	const hkReal& srcL0, const hkReal& srcL1, const hkReal& srcL2, const hkReal& srcL3,
	const hkReal& srcR0, const hkReal& srcR1, const hkReal& srcR2, const hkReal& srcR3 )
{
	*reinterpret_cast< hkVector4* >( &dst0 ) = *reinterpret_cast< const hkVector4* >( &srcR0 );
}

void hkaBatchBlenderUtilities::BlendNormalFunctor::operator() (
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
	const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3 )
{
	copy4( dst0, dst1, dst2, dst3, srcR0, srcR1, srcR2, srcR3 );
}
		
void hkaBatchBlenderUtilities::BlendNormalFunctor::operator() (
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
	const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3 )
{
	copy4( dst0, dst1, dst2, dst3, srcR0, srcR1, srcR2, srcR3 );
}
		
void hkaBatchBlenderUtilities::BlendNormalFunctor::operator() (
	hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
	const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
	const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3 )
{
	copy4( dst0, dst1, dst2, dst3, srcR0, srcR1, srcR2, srcR3 );
}

void hkaBatchBlenderUtilities::BlendAdditiveFunctor::operator() (
	hkReal& dst0, hkReal& dst1, hkReal& dst2, hkReal& dst3,
	const hkReal& srcL0, const hkReal& srcL1, const hkReal& srcL2, const hkReal& srcL3,
	const hkReal& srcR0, const hkReal& srcR1, const hkReal& srcR2, const hkReal& srcR3 )
{
	reinterpret_cast< hkVector4* >( &dst0 )->setAdd(
		*reinterpret_cast< const hkVector4* >( &srcL0 ),
		*reinterpret_cast< const hkVector4* >( &srcR0 ) );
}

void hkaBatchBlenderUtilities::BlendAdditiveFunctor::operator() (
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
	const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3 )
{
	add4( dst0, dst1, dst2, dst3, srcL0, srcL1, srcL2, srcL3, srcR0, srcR1, srcR2, srcR3 );
}
		
void hkaBatchBlenderUtilities::BlendAdditiveFunctor::operator() (
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
	const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3 )
{
	mul4( dst0, dst1, dst2, dst3, srcL0, srcL1, srcL2, srcL3, srcR0, srcR1, srcR2, srcR3 );
}
		
void hkaBatchBlenderUtilities::BlendAdditiveFunctor::operator() (
	hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
	const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
	const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3 )
{
	mul4( dst0, dst1, dst2, dst3, srcL0, srcL1, srcL2, srcL3, srcR0, srcR1, srcR2, srcR3 );
}

void hkaBatchBlenderUtilities::BlendSubtractiveFunctor::operator() (
	hkReal& dst0, hkReal& dst1, hkReal& dst2, hkReal& dst3,
	const hkReal& srcL0, const hkReal& srcL1, const hkReal& srcL2, const hkReal& srcL3,
	const hkReal& srcR0, const hkReal& srcR1, const hkReal& srcR2, const hkReal& srcR3 )
{
	reinterpret_cast< hkVector4* >( &dst0 )->setSub(
		*reinterpret_cast< const hkVector4* >( &srcL0 ),
		*reinterpret_cast< const hkVector4* >( &srcR0 ) );
}

void hkaBatchBlenderUtilities::BlendSubtractiveFunctor::operator() (
	hkVector4& dst0, hkVector4& dst1, hkVector4& dst2, hkVector4& dst3,
	const hkVector4& srcL0, const hkVector4& srcL1, const hkVector4& srcL2, const hkVector4& srcL3,
	const hkVector4& srcR0, const hkVector4& srcR1, const hkVector4& srcR2, const hkVector4& srcR3 )
{
	sub4( dst0, dst1, dst2, dst3, srcL0, srcL1, srcL2, srcL3, srcR0, srcR1, srcR2, srcR3 );
}
		
void hkaBatchBlenderUtilities::BlendSubtractiveFunctor::operator() (
	hkQuaternion& dst0, hkQuaternion& dst1, hkQuaternion& dst2, hkQuaternion& dst3,
	const hkQuaternion& srcL0, const hkQuaternion& srcL1, const hkQuaternion& srcL2, const hkQuaternion& srcL3,
	const hkQuaternion& srcR0, const hkQuaternion& srcR1, const hkQuaternion& srcR2, const hkQuaternion& srcR3 )
{
	mulInv4( dst0, dst1, dst2, dst3, srcL0, srcL1, srcL2, srcL3, srcR0, srcR1, srcR2, srcR3 );
}
		
void hkaBatchBlenderUtilities::BlendSubtractiveFunctor::operator() (
	hkQsTransform& dst0, hkQsTransform& dst1, hkQsTransform& dst2, hkQsTransform& dst3,
	const hkQsTransform& srcL0, const hkQsTransform& srcL1, const hkQsTransform& srcL2, const hkQsTransform& srcL3,
	const hkQsTransform& srcR0, const hkQsTransform& srcR1, const hkQsTransform& srcR2, const hkQsTransform& srcR3 )
{
	mulInv4( dst0, dst1, dst2, dst3, srcL0, srcL1, srcL2, srcL3, srcR0, srcR1, srcR2, srcR3 );
}

void hkaBatchBlenderUtilities::WeightUnweightedFunctor::operator() (
	hkVector4& alphaOut, hkVector4& weightsOut,
	const hkVector4& alpha,
	const hkVector4& weightL, const hkVector4& weightR )
{
	alphaOut = alpha;
}

void hkaBatchBlenderUtilities::WeightNormalFunctor::operator() (
	hkVector4& alphaOut, hkVector4& weightOut,
	const hkVector4& alpha,
	const hkVector4& weightL, const hkVector4& weightR )
{
	
	
	
	
	

	// Compute a new alpha factor based on the given weights
	hkVector4 beta;

	// If weightL > weightR then want beta < alpha.  Let beta = alpha * weightR / weightL
	hkVector4 betaL;
	betaL.setMul( alpha, weightR );
	// use 23-bit division because we don't need the accuracy and it doesn't cause a div-by-0 exception on win32
	betaL.div<HK_ACC_23_BIT,HK_DIV_IGNORE>( weightL );

	// If weightR > weightL then want (1-beta) < (1-alpha).  Let (1-beta) = (1-alpha) * weightL / weightR
	hkVector4 betaR;
	betaR.setSub( hkVector4::getConstant<HK_QUADREAL_1>(), alpha );
	betaR.mul( weightL );
	// use 23-bit division because we don't need the accuracy and it doesn't cause a div-by-0 exception on win32
	betaR.div<HK_ACC_23_BIT,HK_DIV_IGNORE>( weightR );
	betaR.setSub( hkVector4::getConstant<HK_QUADREAL_1>(), betaR );

	// Select from betaL, betaR
	const hkVector4Comparison l_gt_R =  weightL.greater( weightR );
	beta.setSelect( l_gt_R, betaL, betaR );

	// Temp for output weights
	hkVector4 w;

	// w = blend( weightL, weightR, beta )
	w.setSub( hkVector4::getConstant<HK_QUADREAL_1>(), beta );
	w.mul( weightL );
	w.addMul( beta, weightR );

	// Lastly, handle zero weights

	//               |  weightL > 0                      |  weightL == 0       
	// ------------------------------------------------------------------------
	// weightR > 0   |  beta = (see logic above)         |  w = weightR        
	//               |  w = blend(weightL,weightR,beta)  |  beta = 1           
	// ------------------------------------------------------------------------
	// weightR == 0  |  w = weightL                      |  w = 0              
    //               |  beta = 0                         |  beta = alpha  

	const hkVector4Comparison weightL_lte0 = weightL.lessEqualZero();
	const hkVector4Comparison weightR_lte0 = weightR.lessEqualZero();
	hkVector4Comparison weightsEqualZero;
	weightsEqualZero.setAnd( weightL_lte0, weightR_lte0 );

	// Select beta as in the chart above
	beta.setSelect(weightL_lte0, hkVector4::getConstant<HK_QUADREAL_1>(), beta );
	beta.zeroIfTrue(weightR_lte0);
	beta.setSelect( weightsEqualZero, alpha, beta );
		
	// Update w according to the above chart
	w.setSelect( weightL_lte0, weightR, w );
	w.setSelect( weightR_lte0, weightL, w );

	// Write the outputs
	alphaOut = beta;
	weightOut = w;
}

void hkaBatchBlenderUtilities::WeightAdditiveFunctor::operator() (
	hkVector4& alphaOut, hkVector4& weightOut,
	const hkVector4& alpha,
	const hkVector4& weightL, const hkVector4& weightR )
{
	// Output alpha is input alpha * right weights
	alphaOut.setMul( alpha, weightR );

	// Output weights are the same as the left weights
	weightOut = weightL;
}

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
