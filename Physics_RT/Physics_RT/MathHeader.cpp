#include "MathHeader.h"

#include <Common/Base/hkBase.h>

WARP_FUNC(hkVector4, hkVector4Ref)
WARP_FUNC(hkVector4fComparison, hkVector4fComparisonRef)
WARP_FUNC(hkQuaternion, hkQuaternionRef)
WARP_FUNC(hkMatrix3, hkMatrix3Ref)
WARP_FUNC(hkRotation, hkRotationRef)

//============================
//hkVector4 Exports
//============================

hkVector4Ref HAVOK_C_CALL hkVector4_new()
{
    return wrap(new hkVector4());
}
hkVector4Ref HAVOK_C_CALL hkVector4_new_xyzw(float x, float y, float z, float w)
{
    return wrap(new hkVector4(x, y, z, w));
}
void HAVOK_C_CALL hkVector4_delete(hkVector4Ref ptr)
{
    delete ptr;
}
void HAVOK_C_CALL hkVector4_set(hkVector4Ref ptr, float x, float y, float z, float w)
{
    unwrap(ptr)->set(x, y, z, w);
}
void HAVOK_C_CALL hkVector4_setW(hkVector4Ref ptr, float w)
{
    unwrap(ptr)->setW(w);
}
float HAVOK_C_CALL hkVector4_getW(hkVector4Ref ptr)
{
    return unwrap(ptr)->getW();
}
void HAVOK_C_CALL hkVector4_setAll(hkVector4Ref ptr, float a)
{
    unwrap(ptr)->setAll(a);
}
void HAVOK_C_CALL hkVector4_setAll3(hkVector4Ref ptr, float a)
{
    unwrap(ptr)->setAll3(a);
}
void HAVOK_C_CALL hkVector4_sub(hkVector4Ref ptr, hkVector4Ref a)
{
    unwrap(ptr)->sub(*unwrap(a));
}
void HAVOK_C_CALL hkVector4_add(hkVector4Ref ptr, hkVector4Ref a)
{
    unwrap(ptr)->add(*unwrap(a));
}
void HAVOK_C_CALL hkVector4_mul(hkVector4Ref ptr, hkVector4Ref a)
{
    unwrap(ptr)->mul(*unwrap(a));
}
void HAVOK_C_CALL hkVector4_div(hkVector4Ref ptr, hkVector4Ref a)
{
    unwrap(ptr)->div(*unwrap(a));
}
void HAVOK_C_CALL hkVector4_setAdd(hkVector4Ref ptr, hkVector4Ref v0, hkVector4Ref v1) {
    unwrap(ptr)->setAdd(*unwrap(v0), *unwrap(v1));
}
void HAVOK_C_CALL hkVector4_setAdd_f(hkVector4Ref ptr, hkVector4Ref v0, float v1) {
    unwrap(ptr)->setAdd(*unwrap(v0), v1);
}
void HAVOK_C_CALL hkVector4_setSub(hkVector4Ref ptr, hkVector4Ref v0, hkVector4Ref v1) {
    unwrap(ptr)->setSub(*unwrap(v0), *unwrap(v1));
}
void HAVOK_C_CALL hkVector4_setSub_f(hkVector4Ref ptr, hkVector4Ref v0, float v1) {
    unwrap(ptr)->setSub(*unwrap(v0), v1);
}
void HAVOK_C_CALL hkVector4_setMul(hkVector4Ref ptr, hkVector4Ref v0, hkVector4Ref v1) {
    unwrap(ptr)->setMul(*unwrap(v0), *unwrap(v1));
}
void HAVOK_C_CALL hkVector4_setMul_f(hkVector4Ref ptr, hkVector4Ref v1, float r) {
    unwrap(ptr)->setMul(*unwrap(v1), r);
}
void HAVOK_C_CALL hkVector4_setDiv(hkVector4Ref ptr, hkVector4Ref v0, hkVector4Ref v1) {
    unwrap(ptr)->setDiv(*unwrap(v0), *unwrap(v1));
}
void HAVOK_C_CALL hkVector4_setDiv4(hkVector4Ref ptr, hkVector4Ref v0, hkVector4Ref v1) {
    unwrap(ptr)->setDiv4(*unwrap(v0), *unwrap(v1));
}
void HAVOK_C_CALL hkVector4_setDot3(hkVector4Ref ptr, hkVector4Ref v0, hkVector4Ref v1) {
    unwrap(ptr)->setDot3(*unwrap(v0), *unwrap(v1));
}
void HAVOK_C_CALL hkVector4_setDot4(hkVector4Ref ptr, hkVector4Ref v0, hkVector4Ref v1) {
    unwrap(ptr)->setDot4(*unwrap(v0), *unwrap(v1));
}
void HAVOK_C_CALL hkVector4_setSubMul_f(hkVector4Ref ptr, hkVector4Ref a, hkVector4Ref b, float r) {
    unwrap(ptr)->setSubMul(*unwrap(a), *unwrap(b), r);
}
void HAVOK_C_CALL hkVector4_setAddMul_f(hkVector4Ref ptr, hkVector4Ref a, hkVector4Ref b, float r) {
    unwrap(ptr)->setAddMul(*unwrap(a), *unwrap(b), r);
}
void HAVOK_C_CALL hkVector4_setAddMul(hkVector4Ref ptr, hkVector4Ref a, hkVector4Ref x, hkVector4Ref y) {
    unwrap(ptr)->setAddMul(*unwrap(a), *unwrap(x), *unwrap(y));
}
void HAVOK_C_CALL hkVector4_setSubMul(hkVector4Ref ptr, hkVector4Ref a, hkVector4Ref x, hkVector4Ref y) {
    unwrap(ptr)->setSubMul(*unwrap(a), *unwrap(x), *unwrap(y));
}
void HAVOK_C_CALL hkVector4_setCross(hkVector4Ref ptr, hkVector4Ref v0, hkVector4Ref v1) {
    unwrap(ptr)->setCross(*unwrap(v0), *unwrap(v1));
}
void HAVOK_C_CALL hkVector4_setReciprocal(hkVector4Ref ptr, hkVector4Ref v) {
    unwrap(ptr)->setReciprocal(*unwrap(v));
}
void HAVOK_C_CALL hkVector4_setSqrt(hkVector4Ref ptr, hkVector4Ref a) {
    unwrap(ptr)->setSqrt(*unwrap(a));
}
void HAVOK_C_CALL hkVector4_setSqrtInverse(hkVector4Ref ptr, hkVector4Ref a) {
    unwrap(ptr)->setSqrtInverse(*unwrap(a));
}
void HAVOK_C_CALL hkVector4_setInterpolate(hkVector4Ref ptr, hkVector4Ref a, hkVector4Ref b, float t) {
    unwrap(ptr)->setInterpolate(*unwrap(a), *unwrap(b), t);
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_equal(hkVector4Ref ptr, hkVector4Ref a) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->equal(*unwrap(a)));
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_notEqual(hkVector4Ref ptr, hkVector4Ref a) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->notEqual(*unwrap(a)));
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_less(hkVector4Ref ptr, hkVector4Ref a) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->less(*unwrap(a)));
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_lessEqual(hkVector4Ref ptr, hkVector4Ref a) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->lessEqual(*unwrap(a)));
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_greater(hkVector4Ref ptr, hkVector4Ref a) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->greater(*unwrap(a)));
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_greaterEqual(hkVector4Ref ptr, hkVector4Ref a) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->greaterEqual(*unwrap(a)));
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_lessZero(hkVector4Ref ptr) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->lessZero());
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_lessEqualZero(hkVector4Ref ptr) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->lessEqualZero());
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_greaterZero(hkVector4Ref ptr) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->greaterZero());
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_greaterEqualZero(hkVector4Ref ptr) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->greaterEqualZero());
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_equalZero(hkVector4Ref ptr) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->equalZero());
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_compare_notEqualZero(hkVector4Ref ptr) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->notEqualZero());
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_signBitClear(hkVector4Ref ptr) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->signBitClear());
}
hkVector4fComparisonRef HAVOK_C_CALL hkVector4_signBitSet(hkVector4Ref ptr) {
    return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->signBitSet());
}
void HAVOK_C_CALL hkVector4_setSelect(hkVector4Ref ptr, hkVector4fComparisonRef compareMask, hkVector4Ref trueValue, hkVector4Ref falseValue) {
    unwrap(ptr)->setSelect(*unwrap(compareMask), *unwrap(trueValue), *unwrap(falseValue));
}
void HAVOK_C_CALL hkVector4_zeroIfFalse(hkVector4Ref ptr, hkVector4fComparisonRef compareMask) {
    unwrap(ptr)->zeroIfFalse(*unwrap(compareMask));
}
void HAVOK_C_CALL hkVector4_zeroIfTrue(hkVector4Ref ptr, hkVector4fComparisonRef compareMask) {
    unwrap(ptr)->zeroIfTrue(*unwrap(compareMask));
}
void HAVOK_C_CALL hkVector4_setFlipSign_m(hkVector4Ref ptr, hkVector4Ref v, hkVector4fComparisonRef mask) {
    unwrap(ptr)->setFlipSign(*unwrap(v), *unwrap(mask));
}
void HAVOK_C_CALL hkVector4_setFlipSign(hkVector4Ref ptr, hkVector4Ref v, hkVector4Ref vSign) {
    unwrap(ptr)->setFlipSign(*unwrap(v), *unwrap(vSign));
}
void HAVOK_C_CALL hkVector4_setFlipSign_f(hkVector4Ref ptr, hkVector4Ref v, float sSign) {
    unwrap(ptr)->setFlipSign(*unwrap(v), sSign);
}
void HAVOK_C_CALL hkVector4_setAbs(hkVector4Ref ptr, hkVector4Ref v) {
    unwrap(ptr)->setAbs(*unwrap(v));
}
void HAVOK_C_CALL hkVector4_setMin(hkVector4Ref ptr, hkVector4Ref a, hkVector4Ref b) {
    unwrap(ptr)->setMin(*unwrap(a), *unwrap(b));
}
void HAVOK_C_CALL hkVector4_setMax(hkVector4Ref ptr, hkVector4Ref a, hkVector4Ref b) {
    unwrap(ptr)->setMax(*unwrap(a), *unwrap(b));
}
void HAVOK_C_CALL hkVector4_setClamped(hkVector4Ref ptr, hkVector4Ref a, hkVector4Ref minVal, hkVector4Ref maxVal) {
    unwrap(ptr)->setClamped(*unwrap(a), *unwrap(minVal), *unwrap(maxVal));
}
void HAVOK_C_CALL hkVector4_setClampedToMaxLength(hkVector4Ref ptr, hkVector4Ref vSrc, float maxLen) {
    unwrap(ptr)->setClampedToMaxLength(*unwrap(vSrc), maxLen);
}

void HAVOK_C_CALL hkVector4_equal(hkVector4Ref ptr, hkVector4Ref a)
{
    *unwrap(ptr) = *unwrap(a);
}
void HAVOK_C_CALL hkVector4_normalize3(hkVector4Ref ptr)
{
    unwrap(ptr)->normalize3();
}
void HAVOK_C_CALL hkVector4_normalize4(hkVector4Ref ptr)
{
    unwrap(ptr)->normalize4();
}
void HAVOK_C_CALL hkVector4_normalize3IfNotZero(hkVector4Ref ptr)
{
    unwrap(ptr)->normalize3IfNotZero();
}
float HAVOK_C_CALL hkVector4_length3(hkVector4Ref ptr)
{
    return unwrap(ptr)->length3();
}
float HAVOK_C_CALL hkVector4_length4(hkVector4Ref ptr)
{
    return unwrap(ptr)->length4();
}
bool HAVOK_C_CALL hkVector4_isOk1(hkVector4Ref ptr) {
    return unwrap(ptr)->isOk<1>();
}
bool HAVOK_C_CALL hkVector4_isOk2(hkVector4Ref ptr) {
    return unwrap(ptr)->isOk<2>();
}
bool HAVOK_C_CALL hkVector4_isOk3(hkVector4Ref ptr) {
    return unwrap(ptr)->isOk<3>();
}
bool HAVOK_C_CALL hkVector4_isOk4(hkVector4Ref ptr) {
    return unwrap(ptr)->isOk<4>();
}

float HAVOK_C_CALL hkVector4_getComponent(hkVector4Ref ptr, int component)
{
    return unwrap(ptr)->getComponent(component);
}
void HAVOK_C_CALL hkVector4_setComponent(hkVector4Ref ptr, int component, float val)
{
    unwrap(ptr)->setComponent(component, val);
}

//============================
//hkVector4 Exports
//============================


hkVector4fComparisonRef HAVOK_C_CALL hkVector4fComparison_new(int mask) { 
    auto c = new hkVector4fComparison();
    c->set((hkVector4fComparison::Mask)mask);
    return wrap(c);
}
void HAVOK_C_CALL hkVector4fComparison_delete(hkVector4fComparisonRef ptr) { delete ptr; }
int HAVOK_C_CALL hkVector4fComparison_getMask(hkVector4fComparisonRef ptr) { return unwrap(ptr)->getMask(); }
int HAVOK_C_CALL hkVector4fComparison_getMask(hkVector4fComparisonRef ptr, int m){ return unwrap(ptr)->getMask((hkVector4fComparison::Mask)m); }
bool HAVOK_C_CALL hkVector4fComparison_allAreSet(hkVector4fComparisonRef ptr) { return unwrap(ptr)->allAreSet(); }
bool HAVOK_C_CALL hkVector4fComparison_anyIsSet(hkVector4fComparisonRef ptr) { return unwrap(ptr)->anyIsSet(); }
int HAVOK_C_CALL hkVector4fComparison_getIndexOfFirstComponentSet(hkVector4fComparisonRef ptr) { return unwrap(ptr)->getIndexOfFirstComponentSet(); }
int HAVOK_C_CALL hkVector4fComparison_getIndexOfLastComponentSet(hkVector4fComparisonRef ptr) { return unwrap(ptr)->getIndexOfLastComponentSet(); }
hkVector4fComparisonRef HAVOK_C_CALL hkVector4fComparison_horizontalAnd1(hkVector4fComparisonRef ptr) { return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->horizontalAnd<1>()); }
hkVector4fComparisonRef HAVOK_C_CALL hkVector4fComparison_horizontalAnd2(hkVector4fComparisonRef ptr) { return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->horizontalAnd<2>()); }
hkVector4fComparisonRef HAVOK_C_CALL hkVector4fComparison_horizontalAnd3(hkVector4fComparisonRef ptr) { return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->horizontalAnd<3>()); }
hkVector4fComparisonRef HAVOK_C_CALL hkVector4fComparison_horizontalAnd4(hkVector4fComparisonRef ptr) { return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->horizontalAnd<4>()); }
hkVector4fComparisonRef HAVOK_C_CALL hkVector4fComparison_horizontalOr1(hkVector4fComparisonRef ptr) { return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->horizontalOr<1>()); }
hkVector4fComparisonRef HAVOK_C_CALL hkVector4fComparison_horizontalOr2(hkVector4fComparisonRef ptr) { return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->horizontalOr<2>()); }
hkVector4fComparisonRef HAVOK_C_CALL hkVector4fComparison_horizontalOr3(hkVector4fComparisonRef ptr) { return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->horizontalOr<3>()); }
hkVector4fComparisonRef HAVOK_C_CALL hkVector4fComparison_horizontalOr4(hkVector4fComparisonRef ptr) { return CopyClassToHeap<hkVector4fComparison>(unwrap(ptr)->horizontalOr<4>()); }

//============================
//hkVector4 Exports
//============================

hkQuaternionRef HAVOK_C_CALL hkQuaternion_new()
{
    return wrap(new hkQuaternion());
}
void HAVOK_C_CALL hkQuaternion_delete(hkQuaternionRef ptr)
{
    delete ptr;
}
hkQuaternionRef HAVOK_C_CALL hkQuaternion_new_xyzr(float x, float y, float z, float r)
{
    return wrap(new hkQuaternion(x, y, z, r));
}
hkQuaternionRef HAVOK_C_CALL hkQuaternion_new_axis(hkVector4Ref axis, float angle)
{
    return wrap(new hkQuaternion(*unwrap(axis), angle));
}
void HAVOK_C_CALL hkQuaternion_set(hkQuaternionRef ptr, float x, float y, float z, float r)
{
    unwrap(ptr)->set(x, y, z, r);
}
void HAVOK_C_CALL hkQuaternion_setIdentity(hkQuaternionRef ptr) {
    unwrap(ptr)->setIdentity();
}
void HAVOK_C_CALL hkQuaternion_setInverse(hkQuaternionRef ptr, hkQuaternionRef q) {
    unwrap(ptr)->setInverse(*unwrap(q));
}
void HAVOK_C_CALL hkQuaternion_setMul(hkQuaternionRef ptr, float r, hkQuaternionRef q) {
    unwrap(ptr)->setMul(r, *unwrap(q));
}
void HAVOK_C_CALL hkQuaternion_addMul(hkQuaternionRef ptr, float r, hkQuaternionRef q) {
    unwrap(ptr)->addMul(r, *unwrap(q));
}
void HAVOK_C_CALL hkQuaternion_setMul(hkQuaternionRef ptr, hkQuaternionRef q0, hkQuaternionRef q1) {
    unwrap(ptr)->setMul(*unwrap(q0), *unwrap(q1));
}
void HAVOK_C_CALL hkQuaternion_mul(hkQuaternionRef ptr, hkQuaternionRef q) {
    unwrap(ptr)->mul(*unwrap(q));
}
void HAVOK_C_CALL hkQuaternion_setMulInverse(hkQuaternionRef ptr, hkQuaternionRef q0, hkQuaternionRef q1) {
    unwrap(ptr)->setMulInverse(*unwrap(q0), *unwrap(q1));
}
void HAVOK_C_CALL hkQuaternion_setInverseMul(hkQuaternionRef ptr, hkQuaternionRef q0, hkQuaternionRef q1) {
    unwrap(ptr)->setInverseMul(*unwrap(q0), *unwrap(q1));
}
void HAVOK_C_CALL hkQuaternion_estimateAngleTo(hkQuaternionRef ptr, hkQuaternionRef to, hkVector4Ref angleOut) {
    unwrap(ptr)->estimateAngleTo(*unwrap(to), *unwrap(angleOut));
}
void HAVOK_C_CALL hkQuaternion_setAxisAngle(hkQuaternionRef ptr, hkVector4Ref axis, float angle) {
    unwrap(ptr)->setAxisAngle(*unwrap(axis), angle);
}
void HAVOK_C_CALL hkQuaternion_setFromEulerAngles(hkQuaternionRef ptr, float roll, float pitch, float yaw) {
    unwrap(ptr)->setFromEulerAngles(roll, pitch, yaw);
}
void HAVOK_C_CALL hkQuaternion_removeAxisComponent(hkQuaternionRef ptr, hkVector4Ref axis) {
    unwrap(ptr)->removeAxisComponent(*unwrap(axis));
}
void HAVOK_C_CALL hkQuaternion_decomposeRestAxis(hkQuaternionRef ptr, hkVector4Ref axis, hkQuaternionRef restOut, float angleOut) {
    hkSimdFloat32 _angleOut = angleOut;
    unwrap(ptr)->decomposeRestAxis(*unwrap(axis), *unwrap(restOut), _angleOut);
}
void HAVOK_C_CALL hkQuaternion_setSlerp(hkQuaternionRef ptr, hkQuaternionRef q0, hkQuaternionRef q1, float t) {
    unwrap(ptr)->setSlerp(*unwrap(q0), *unwrap(q1), t);
}
void HAVOK_C_CALL hkQuaternion_setBarycentric(hkQuaternionRef ptr, hkQuaternionRef qVerts, hkVector4Ref vLambda) {
    unwrap(ptr)->setBarycentric(unwrap(qVerts), *unwrap(vLambda));
}
void HAVOK_C_CALL hkQuaternion_setReal(hkQuaternionRef ptr, float r) {
    unwrap(ptr)->setReal(r);
}
float HAVOK_C_CALL hkQuaternion_getReal(hkQuaternionRef ptr) {
    return unwrap(ptr)->getReal();
}
void HAVOK_C_CALL hkQuaternion_setImag(hkQuaternionRef ptr, hkVector4Ref i) {
    unwrap(ptr)->setImag(*unwrap(i));
}
hkVector4Ref HAVOK_C_CALL hkQuaternion_getImag(hkQuaternionRef ptr) {
    return (hkVector4Ref)CopyClassToHeap<hkVector4>(unwrap(ptr)->getImag());
}
float HAVOK_C_CALL hkQuaternion_getAngle(hkQuaternionRef ptr) {
    return unwrap(ptr)->getAngle();
}
void HAVOK_C_CALL hkQuaternion_getAxis(hkQuaternionRef ptr, hkVector4Ref axis) {
    hkVector4 out;
    unwrap(ptr)->getAxis(out);
    unwrap(axis)->setXYZ(out);
}
bool HAVOK_C_CALL hkQuaternion_hasValidAxis(hkQuaternionRef ptr) {
    return unwrap(ptr)->hasValidAxis();
}
void HAVOK_C_CALL hkQuaternion_setClosest(hkQuaternionRef ptr, hkQuaternionRef q, hkQuaternionRef qReference) {
    unwrap(ptr)->setClosest(*unwrap(q), *unwrap(qReference));
}
void HAVOK_C_CALL hkQuaternion_setFlippedRotation(hkQuaternionRef ptr, hkVector4Ref from) {
    unwrap(ptr)->setFlippedRotation(*unwrap(from));
}
void HAVOK_C_CALL hkQuaternion_normalize(hkQuaternionRef ptr) {
    unwrap(ptr)->normalize();
}
void HAVOK_C_CALL hkQuaternion_setAndNormalize(hkQuaternionRef ptr, const hkRotationf& r) {
    //unwrap(ptr)->setAndNormalize();
}
void HAVOK_C_CALL hkQuaternion_operator_equal(hkQuaternionRef ptr, hkQuaternionRef a)
{
    *unwrap(ptr) = *unwrap(a);
}
void HAVOK_C_CALL hkQuaternion_get_m_vec(hkQuaternionRef ptr, hkVector4Ref out)
{
    *unwrap(out) = unwrap(ptr)->m_vec;
}
void HAVOK_C_CALL hkQuaternion_set_m_vec(hkQuaternionRef ptr, hkVector4Ref a)
{
    unwrap(ptr)->m_vec = *unwrap(a);
}
bool HAVOK_C_CALL hkQuaternion_isOk(hkQuaternionRef ptr, float epsilon) {
    return unwrap(ptr)->isOk(epsilon);
}

//============================
//hkMatrix3 Exports
//============================

hkMatrix3Ref HAVOK_C_CALL hkMatrix3_new()
{
    return wrap(new hkMatrix3());
}
void HAVOK_C_CALL hkMatrix3_delete(hkMatrix3Ref ptr)
{
    delete ptr;
}
hkVector4Ref HAVOK_C_CALL hkMatrix3_getColumn(hkMatrix3Ref ptr, int i) {
    return (hkVector4Ref)CopyClassToHeap<hkVector4>(unwrap(ptr)->getColumn(i));
}
void HAVOK_C_CALL hkMatrix3_getRow(hkMatrix3Ref ptr, int row, hkVector4Ref r) {
    unwrap(ptr)->getRow(row, *unwrap(r));
}
void HAVOK_C_CALL hkMatrix3_setColumn0(hkMatrix3Ref ptr, hkVector4Ref c) {
    unwrap(ptr)->setColumn<0>(*unwrap(c));
}
void HAVOK_C_CALL hkMatrix3_setColumn1(hkMatrix3Ref ptr, hkVector4Ref c) {
    unwrap(ptr)->setColumn<1>(*unwrap(c));
}
void HAVOK_C_CALL hkMatrix3_setColumn2(hkMatrix3Ref ptr, hkVector4Ref c) {
    unwrap(ptr)->setColumn<2>(*unwrap(c));
}
void HAVOK_C_CALL hkMatrix3_setRows(hkMatrix3Ref ptr, hkVector4Ref r0, hkVector4Ref r1, hkVector4Ref r2) {
    unwrap(ptr)->setRows(*unwrap(r0), *unwrap(r1), *unwrap(r2));
}
void HAVOK_C_CALL hkMatrix3_getRows(hkMatrix3Ref ptr, hkVector4Ref r0, hkVector4Ref r1, hkVector4Ref r2) {
    unwrap(ptr)->getRows(*unwrap(r0), *unwrap(r1), *unwrap(r2));
}
void HAVOK_C_CALL hkMatrix3_setCols(hkMatrix3Ref ptr, hkVector4Ref c0, hkVector4Ref c1, hkVector4Ref c2) {
    unwrap(ptr)->setCols(*unwrap(c0), *unwrap(c1), *unwrap(c2));
}
void HAVOK_C_CALL hkMatrix3_getCols(hkMatrix3Ref ptr, hkVector4Ref c0, hkVector4Ref c1, hkVector4Ref c2) {
    unwrap(ptr)->getCols(*unwrap(c0), *unwrap(c1), *unwrap(c2));
}
void HAVOK_C_CALL hkMatrix3_setZero(hkMatrix3Ref ptr) {
    unwrap(ptr)->setZero();
}
void HAVOK_C_CALL hkMatrix3_setIdentity(hkMatrix3Ref ptr) {
    unwrap(ptr)->setIdentity();
}
hkMatrix3Ref HAVOK_C_CALL hkMatrix3_getIdentity() {
    return (hkMatrix3Ref)CopyClassToHeap<hkMatrix3>(hkMatrix3::getIdentity());
}
bool HAVOK_C_CALL hkMatrix3_isApproximatelyEqual(hkMatrix3Ref ptr, hkMatrix3Ref m, float epsilon) {
    return unwrap(ptr)->isApproximatelyEqual(*unwrap(m), epsilon);
}
bool HAVOK_C_CALL hkMatrix3_isSymmetric(hkMatrix3Ref ptr, float epsilon) {
    return unwrap(ptr)->isSymmetric(epsilon);
}
void HAVOK_C_CALL hkMatrix3_setCrossSkewSymmetric(hkMatrix3Ref ptr, hkVector4Ref r) {
    unwrap(ptr)->setCrossSkewSymmetric(*unwrap(r));
}
int8_t HAVOK_C_CALL hkMatrix3_invert(hkMatrix3Ref ptr, float epsilon) {
    return (int8_t)unwrap(ptr)->invert(epsilon).m_enum;
}
void HAVOK_C_CALL hkMatrix3_setInverseSymmetric(hkMatrix3Ref ptr, hkMatrix3Ref src) {
    unwrap(ptr)->setInverseSymmetric(*unwrap(src));
}
void HAVOK_C_CALL hkMatrix3_solveSymmetric(hkMatrix3Ref ptr, hkVector4Ref b, hkVector4Ref v) {
    unwrap(ptr)->solveSymmetric(*unwrap(b), *unwrap(v));
}
void HAVOK_C_CALL hkMatrix3_invertSymmetric(hkMatrix3Ref ptr) {
    unwrap(ptr)->invertSymmetric();
}
float HAVOK_C_CALL hkMatrix3_frobeniusNormSqr(hkMatrix3Ref ptr) {
    return unwrap(ptr)->frobeniusNormSqr();
}
void HAVOK_C_CALL hkMatrix3_transpose(hkMatrix3Ref ptr) {
    unwrap(ptr)->transpose();
}
void HAVOK_C_CALL hkMatrix3_setTranspose(hkMatrix3Ref ptr, hkMatrix3Ref s) {
    unwrap(ptr)->setTranspose(*unwrap(s));
}
void HAVOK_C_CALL hkMatrix3_setMul(hkMatrix3Ref ptr, hkMatrix3Ref a, hkMatrix3Ref b) {
    unwrap(ptr)->setMul(*unwrap(a), *unwrap(b));
}
void HAVOK_C_CALL hkMatrix3_setMulInverse(hkMatrix3Ref ptr, hkMatrix3Ref a, hkRotationRef b) {
    unwrap(ptr)->setMulInverse(*unwrap(a), *unwrap(b));
}
void HAVOK_C_CALL hkMatrix3_setMulInverseMul(hkMatrix3Ref ptr, hkRotationRef a, hkMatrix3Ref b) {
    unwrap(ptr)->setMulInverseMul(*unwrap(a), *unwrap(b));
}
void HAVOK_C_CALL hkMatrix3_setMul_scale(hkMatrix3Ref ptr, float scale, hkMatrix3Ref a) {
    unwrap(ptr)->setMul(scale, *unwrap(a));
}
void HAVOK_C_CALL hkMatrix3_setDiagonalMul(hkMatrix3Ref ptr, hkVector4Ref vDiag, hkMatrix3Ref a) {
    unwrap(ptr)->setDiagonalMul(*unwrap(vDiag), *unwrap(a));
}
void HAVOK_C_CALL hkMatrix3_addDiagonal(hkMatrix3Ref ptr, float diag) {
    unwrap(ptr)->addDiagonal(diag);
}
void HAVOK_C_CALL hkMatrix3_setTransposeMul(hkMatrix3Ref ptr, hkMatrix3Ref a, hkMatrix3Ref b) {
    unwrap(ptr)->setTransposeMul(*unwrap(a), *unwrap(b));
}
void HAVOK_C_CALL hkMatrix3_addMul(hkMatrix3Ref ptr, float scale, hkMatrix3Ref a) {
    unwrap(ptr)->addMul(scale, *unwrap(a));
}
void HAVOK_C_CALL hkMatrix3_changeBasis(hkMatrix3Ref ptr, hkRotationRef t) {
    unwrap(ptr)->changeBasis(*unwrap(t));
}
void HAVOK_C_CALL hkMatrix3_add(hkMatrix3Ref ptr, hkMatrix3Ref a) {
    unwrap(ptr)->add(*unwrap(a));
}
void HAVOK_C_CALL hkMatrix3_sub(hkMatrix3Ref ptr, hkMatrix3Ref a) {
    unwrap(ptr)->sub(*unwrap(a));
}
void HAVOK_C_CALL hkMatrix3_mul(hkMatrix3Ref ptr, hkMatrix3Ref a) {
    unwrap(ptr)->mul(*unwrap(a));
}
void HAVOK_C_CALL hkMatrix3_mul_scale(hkMatrix3Ref ptr, float scale) {
    unwrap(ptr)->mul(scale);
}
void HAVOK_C_CALL hkMatrix3_operator_equal(hkMatrix3Ref ptr, hkMatrix3Ref a) {
    *unwrap(ptr) = *unwrap(a);
}
bool HAVOK_C_CALL hkMatrix3_isOk(hkMatrix3Ref ptr) {
    return unwrap(ptr)->isOk();
}
void HAVOK_C_CALL hkMatrix3_multiplyVector(hkMatrix3Ref ptr, hkVector4Ref vectorIn, hkVector4Ref resultOut) {
    unwrap(ptr)->multiplyVector(*unwrap(vectorIn), *unwrap(resultOut));
}
float HAVOK_C_CALL hkMatrix3_getDeterminant(hkMatrix3Ref ptr) {
    return unwrap(ptr)->getDeterminant();
}
int8_t HAVOK_C_CALL hkMatrix3_diagonalizeSymmetric(hkMatrix3Ref ptr, hkRotationRef eigenVec, hkVector4Ref eigenVal, int maxIter, float epsilon) {
    return (int8_t)unwrap(ptr)->diagonalizeSymmetric(*unwrap(eigenVec), *unwrap(eigenVal), maxIter, epsilon).m_enum;
}
int8_t HAVOK_C_CALL hkMatrix3_diagonalizeSymmetricWarmStart(hkMatrix3Ref ptr, hkMatrix3Ref eigenVec, hkVector4Ref eigenVal, int maxIter, float epsilon) {
    return (int8_t)unwrap(ptr)->diagonalizeSymmetricWarmStart(*unwrap(eigenVec), *unwrap(eigenVal), maxIter, epsilon).m_enum;
}
void HAVOK_C_CALL hkMatrix3_diagonalizeSymmetricApproximation(hkMatrix3Ref ptr, hkRotationRef eigenVec, hkVector4Ref eigenVal, int maxIter) {
    unwrap(ptr)->diagonalizeSymmetricApproximation(*unwrap(eigenVec), *unwrap(eigenVal), maxIter); 
}

//============================
//hkRotation Exports
//============================

void HAVOK_C_CALL hkRotation_delete(hkRotationRef ptr)
{
    delete ptr;
}
void HAVOK_C_CALL hkRotation_set(hkRotationRef ptr, hkQuaternionRef q)
{
    unwrap(ptr)->set(*unwrap(q));
}
void HAVOK_C_CALL hkRotation_setAxisAngle(hkRotationRef ptr, hkVector4Ref axis, float angle)
{
    unwrap(ptr)->set(*unwrap(axis), angle);
}
bool HAVOK_C_CALL hkRotation_isOrthonormal(hkRotationRef ptr, float epsilon)
{
    return unwrap(ptr)->isOrthonormal(epsilon);
}
bool HAVOK_C_CALL hkRotation_isOk(hkRotationRef ptr)
{
    return unwrap(ptr)->isOk();
}
void HAVOK_C_CALL hkRotation_renormalize(hkRotationRef ptr)
{
    unwrap(ptr)->renormalize();
}
