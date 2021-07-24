/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKMATH_HEADERUNIONS_H
#define HKMATH_HEADERUNIONS_H

// Union that allows us to initialize the int values of an int vector
union hkQuadFloat32Union
{
	hkFloat32 r[4];
	hkQuadFloat32 q;
};

union hkQuadDouble64Union
{
	hkDouble64 r[4];
	hkQuadDouble64 q;
};

union hkQuadIntUnion
{
	hkInt32 u[4];
	hkQuadUint q;
};

union hkQuadUintUnion
{
	hkUint32 u[4];
	hkQuadUint q;
};

union hkQuadShortUnion
{
	hkInt16 u[8];
	hkQuadUint q;
};

union hkQuadUshortUnion
{
	hkUint16 u[8];
	hkQuadUint q;
};

union hkQuadCharUnion
{
	hkUint8 u[16];
	hkQuadUint q;
};

union hkQuadUcharUnion
{
	hkUint8 u[16];
	hkQuadUint q;
};


union hkIntUnion64
{
	HK_ALIGN8(hkInt64 i64);    
	hkUint64 u64;
	hkInt32 i32[2];
	hkUint32 u32[2];
	hkInt16 i16[4];
	hkUint16 u16[4];
	hkInt8 i8[8];
	hkUint8 u8[8];
};

#endif //HKMATH_HEADERUNIONS_H

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
