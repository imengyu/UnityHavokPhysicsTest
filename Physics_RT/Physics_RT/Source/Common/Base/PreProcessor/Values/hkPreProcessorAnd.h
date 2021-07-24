/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_PRE_PROCESSOR_BITWISE_AND_IMPL_H
#define HK_PRE_PROCESSOR_BITWISE_AND_IMPL_H

//
//	These macros compute x & y where x and y are bits

#define HK_PREPROCESSOR_AND_00	0
#define HK_PREPROCESSOR_AND_01	0
#define HK_PREPROCESSOR_AND_10	0
#define HK_PREPROCESSOR_AND_11	1

#define HK_PREPROCESSOR_AND_BITS(x, y)			HK_PREPROCESSOR_AND_##x##y
#define HK_PREPROCESSOR_EVAL_AND_BITS(x, y)		HK_PREPROCESSOR_AND_BITS(x, y)

//
//	These macros recurse to compute x & y

#define HK_PREPROCESSOR_BITWISE_AND_16_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_15_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_15_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_14_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_14_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_13_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_13_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_12_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_12_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_11_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_11_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_10_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_10_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_9_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_9_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_8_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_8_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_7_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_7_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_6_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_6_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_5_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_5_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_4_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_4_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_3_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_3_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_BITWISE_AND_2_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)

#define HK_PREPROCESSOR_BITWISE_AND_2_BITS(x, y)\
	HK_PREPROCESSOR_BITWISE_OR_LAST_BIT(\
		HK_PREPROCESSOR_TEMP_SHL_COUNT_1(\
			HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_TEMP_SHR_COUNT_1(x), HK_PREPROCESSOR_TEMP_SHR_COUNT_1(y))\
		),\
		HK_PREPROCESSOR_EVAL_AND_BITS(HK_PREPROCESSOR_LSB(x), HK_PREPROCESSOR_LSB(y))\
	)


#endif	//	HK_PRE_PROCESSOR_BITWISE_AND_IMPL_H

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
