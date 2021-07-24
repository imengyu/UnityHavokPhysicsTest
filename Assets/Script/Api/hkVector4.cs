using System;
using System.Runtime.InteropServices;
using UnityEngine;

public class hkVector4 : IDisposable, IEquatable<hkVector4>
{
  public hkVector4()
  {
    ptr = hkVector4_new();
  }
  public hkVector4(float x, float y, float z, float w = 0)
  {
    ptr = hkVector4_new_xyzw(x, y, z, w);
  }
  public hkVector4(IntPtr nativePtr)
  {
    ptr = nativePtr;
  }
  public hkVector4(Vector4 vec4)
  {
    ptr = hkVector4_new_xyzw(vec4.x, vec4.y, vec4.z, vec4.w);
  }
  public hkVector4(Vector3 vec3)
  {
    ptr = hkVector4_new_xyzw(vec3.x, vec3.y, vec3.z, 0);
  }

  public Vector4 ToUnityVector4() {
    return new Vector4(x, y, z, w);
  }

  public void set(float x, float y, float z, float w)
  {
    hkVector4_set(ptr, x, y, z, w);
  }
  public void setW(float w)
  {
    hkVector4_setW(ptr, w);
  }
  public void setAll(float a)
  {
    hkVector4_setAll(ptr, a);
  }
  public void setAll3(float a)
  {
    hkVector4_setAll3(ptr, a);
  }
  public void set(hkVector4 a) { hkVector4_equal(ptr, a.ptr); }
  public void setZero() { setAll(0); }

  public hkVector4fComparison equal(hkVector4 a) { return new hkVector4fComparison(hkVector4_compare_equal(ptr, a.ptr)); }
  public hkVector4fComparison notEqual(hkVector4 a) { return new hkVector4fComparison(hkVector4_compare_notEqual(ptr, a.ptr)); }
  public hkVector4fComparison less(hkVector4 a) { return new hkVector4fComparison(hkVector4_compare_less(ptr, a.ptr)); }
  public hkVector4fComparison lessEqual(hkVector4 a) { return new hkVector4fComparison(hkVector4_compare_lessEqual(ptr, a.ptr)); }
  public hkVector4fComparison greater(hkVector4 a) { return new hkVector4fComparison(hkVector4_compare_greater(ptr, a.ptr)); }
  public hkVector4fComparison greaterEqual(hkVector4 a) { return new hkVector4fComparison(hkVector4_compare_greaterEqual(ptr, a.ptr)); }
  public hkVector4fComparison lessZero() { return new hkVector4fComparison(hkVector4_compare_lessZero(ptr)); }
  public hkVector4fComparison lessEqualZero() { return new hkVector4fComparison(hkVector4_compare_lessEqualZero(ptr)); }
  public hkVector4fComparison equalZero() { return new hkVector4fComparison(hkVector4_compare_equalZero(ptr)); }
  public hkVector4fComparison greaterZero() { return new hkVector4fComparison(hkVector4_compare_greaterZero(ptr)); }
  public hkVector4fComparison greaterEqualZero() { return new hkVector4fComparison(hkVector4_compare_greaterEqualZero(ptr)); }
  public hkVector4fComparison notEqualZero() { return new hkVector4fComparison(hkVector4_compare_notEqualZero(ptr)); }
  public hkVector4fComparison signBitSet() { return new hkVector4fComparison(hkVector4_signBitSet(ptr)); }
  public hkVector4fComparison signBitClear() { return new hkVector4fComparison(hkVector4_signBitClear(ptr)); }
  public void add(hkVector4 a) { hkVector4_add(ptr, a.ptr); }
  public void sub(hkVector4 a) { hkVector4_sub(ptr, a.ptr); }
  public void mul(hkVector4 a) { hkVector4_mul(ptr, a.ptr); }
  public void div(hkVector4 a) { hkVector4_div(ptr, a.ptr); }
  public void setAdd(hkVector4 v0, hkVector4 v1) {
    hkVector4_setAdd(ptr, v0.ptr, v1.ptr);
  }
  public void setAdd(hkVector4 v0, float v1) {
    hkVector4_setAdd_f(ptr, v0.ptr, v1);
  }
  public void setSub(hkVector4 v0, hkVector4 v1){
    hkVector4_setSub(ptr, v0.ptr, v1.ptr);
  }
  public void setSub(hkVector4 v0, float v1) {
    hkVector4_setSub_f(ptr, v0.ptr, v1);
  }
  public void setMul(hkVector4 v0, hkVector4 v1){
    hkVector4_setMul(ptr, v0.ptr, v1.ptr);
  }
  public void setMul(hkVector4 v1, float r){
    hkVector4_setMul_f(ptr, v1.ptr, r);
  } 
  public void setDiv(hkVector4 v0, hkVector4 v1){
    hkVector4_setDiv(ptr, v0.ptr, v1.ptr);
  }
  public void setDiv4(hkVector4 v0, hkVector4 v1){
    hkVector4_setDiv4(ptr, v0.ptr, v1.ptr);
  }
  public void setDot3(hkVector4 v0, hkVector4 v1){
    hkVector4_setDot3(ptr, v0.ptr, v1.ptr);
  }
  public void setDot4(hkVector4 v0, hkVector4 v1){
    hkVector4_setDot4(ptr, v0.ptr, v1.ptr);
  }
  public void setSubMul(hkVector4 a, hkVector4 b, float r) {
    hkVector4_setSubMul_f(ptr, a.ptr, b.ptr, r);
  }
  public void setAddMul(hkVector4 a, hkVector4 b, float r) {
    hkVector4_setAddMul_f(ptr, a.ptr, b.ptr, r);
  }
  public void setAddMul(hkVector4 a, hkVector4 x, hkVector4 y) {
    hkVector4_setAddMul(ptr, a.ptr, x.ptr, y.ptr);
  }
  public void setSubMul(hkVector4 a, hkVector4 x, hkVector4 y) {
    hkVector4_setSubMul(ptr, a.ptr, x.ptr, y.ptr);
  }
  public void setCross(hkVector4 v0, hkVector4 v1) {
    hkVector4_setCross(ptr, v0.ptr, v1.ptr);
  }
  public void setReciprocal(hkVector4 a) {
    hkVector4_setReciprocal(ptr, a.ptr);
  }
  public void setSqrt(hkVector4 a) {
    hkVector4_setSqrt(ptr, a.ptr);
  }
  public void setSqrtInverse(hkVector4 a) {
    hkVector4_setSqrtInverse(ptr, a.ptr);
  }
  public void setInterpolate(hkVector4 a, hkVector4 b, float t) {
    hkVector4_setInterpolate(ptr, a.ptr, b.ptr, t);
  }  
  
  public void setSelect(hkVector4fComparison compareMask, hkVector4 trueValue, hkVector4 falseValue) {
    hkVector4_setSelect(ptr, compareMask.Ptr, trueValue.ptr, falseValue.ptr);
  }  
  public void zeroIfFalse(hkVector4fComparison compareMask) {
    hkVector4_zeroIfFalse(ptr, compareMask.Ptr);
  }  
  public void zeroIfTrue(hkVector4fComparison compareMask) {
    hkVector4_zeroIfTrue(ptr, compareMask.Ptr);
  }  
  public void setFlipSign(hkVector4 v, hkVector4fComparison mask) {
    hkVector4_setFlipSign_m(ptr, v.Ptr, mask.Ptr);
  }  
  public void setFlipSign(hkVector4 v, hkVector4 vSign) {
    hkVector4_setFlipSign(ptr, v.Ptr, vSign.ptr);
  }  
  public void setFlipSign(hkVector4 v, float sSign) {
    hkVector4_setFlipSign_f(ptr, v.Ptr, sSign);
  }  
  public void setAbs(hkVector4 v) {
    hkVector4_setAbs(ptr, v.ptr);
  }
  public void setMin(hkVector4 a, hkVector4 b) {
    hkVector4_setMin(ptr, a.ptr, b.ptr);
  }
  public void setMax(hkVector4 a, hkVector4 b) {
      hkVector4_setMax(ptr, a.ptr, b.ptr);
  }
  public void setClamped(hkVector4 a, hkVector4 minVal, hkVector4 maxVal) {
    hkVector4_setClamped(ptr, a.ptr, minVal.ptr, maxVal.ptr);
  }
  public void setClampedToMaxLength(hkVector4 vSrc, float maxLen) {
    hkVector4_setClampedToMaxLength(ptr, vSrc.ptr, maxLen);
  }

  public void normalize3() { hkVector4_normalize3(ptr); }
  public void normalize4() { hkVector4_normalize4(ptr); }
  public void normalize3IfNotZero() { hkVector4_normalize3IfNotZero(ptr); }
  public float length3() { return hkVector4_length3(ptr); }
  public float length4() { return hkVector4_length4(ptr); }
  public bool isOk1() { return hkVector4_isOk1(ptr); }
  public bool isOk2() { return hkVector4_isOk2(ptr); }
  public bool isOk3() { return hkVector4_isOk3(ptr); }
  public bool isOk4() { return hkVector4_isOk4(ptr); }

  public float x { 
    get { return hkVector4_getComponent(ptr, 0); } 
    set { hkVector4_setComponent(ptr, 0, value); }
  } 
  public float y { 
    get { return hkVector4_getComponent(ptr, 1); } 
    set { hkVector4_setComponent(ptr, 1, value); }
  } 
  public float z { 
    get { return hkVector4_getComponent(ptr, 2); } 
    set { hkVector4_setComponent(ptr, 2, value); }
  } 
  public float w { 
    get { return hkVector4_getW(ptr); }
    set { hkVector4_setComponent(ptr, 3, value); }
  } 
  
  public static bool operator== (hkVector4 a, hkVector4 b)
  {
    using(var cp = a.equal(b))
      return (cp.getMask() & hkVector4fComparison.Mask.MASK_XYZW) == hkVector4fComparison.Mask.MASK_XYZW;
  }
  public static bool operator!= (hkVector4 a, hkVector4 b)
  {
    using(var cp = a.notEqual(b))
      return (cp.getMask() & hkVector4fComparison.Mask.MASK_XYZW) == hkVector4fComparison.Mask.MASK_XYZW;
  }
  public static hkVector4 operator+ (hkVector4 a, hkVector4 b)
  {
    hkVector4 ret = new hkVector4();
    hkVector4_setAdd(ret.ptr, a.ptr, b.ptr);
    return ret;
  }
  public static hkVector4 operator+ (hkVector4 a, float b)
  {
    hkVector4 ret = new hkVector4();
    hkVector4_setAdd_f(ret.ptr, a.ptr, b);
    return ret;
  }
  public static hkVector4 operator- (hkVector4 a, hkVector4 b)
  {
    hkVector4 ret = new hkVector4();
    hkVector4_setSub(ret.ptr, a.ptr, b.ptr);
    return ret;
  }
  public static hkVector4 operator- (hkVector4 a, float b)
  {
    hkVector4 ret = new hkVector4();
    hkVector4_setSub_f(ret.ptr, a.ptr, b);
    return ret;
  }
  public static hkVector4 operator* (hkVector4 a, hkVector4 b)
  {
    hkVector4 ret = new hkVector4();
    hkVector4_setMul(ret.ptr, a.ptr, b.ptr);
    return ret;
  }
  public static hkVector4 operator* (hkVector4 a, float b)
  {
    hkVector4 ret = new hkVector4();
    hkVector4_setMul_f(ret.ptr, a.ptr, b);
    return ret;
  }
  public static hkVector4 operator/ (hkVector4 a, hkVector4 b)
  {
    hkVector4 ret = new hkVector4();
    hkVector4_setDiv(ret.ptr, a.ptr, b.ptr);
    return ret;
  }

  public override bool Equals(object obj)
  {
    if(obj is hkVector4)
      return (obj as hkVector4).ptr == ptr;
    return base.Equals(obj);
  }
  public bool Equals(hkVector4 other)
  {
    return other.ptr == ptr;
  }
  public override int GetHashCode()
  {
    return ptr.ToInt32();
  }
  public override string ToString()
  {
    return "hkVector4 (" + x + "," + y + "," + z + "," + w + ")";
  }

  #region API

  private IntPtr ptr = IntPtr.Zero;

  public IntPtr Ptr { get { return ptr; } }

  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_new();
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_new_xyzw(float x, float y, float z, float w);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_delete(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_set(IntPtr ptr, float x, float y, float z, float w);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setW(IntPtr ptr, float w);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern float hkVector4_getW(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern float hkVector4_getComponent(IntPtr ptr, int component);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setComponent(IntPtr ptr, int component, float val);

  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setAll(IntPtr ptr, float a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setAll3(IntPtr ptr, float a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_sub(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_add(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_mul(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_div(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setAdd(IntPtr ptr, IntPtr v0, IntPtr v1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setAdd_f(IntPtr ptr, IntPtr v0, float v1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setSub(IntPtr ptr, IntPtr v0, IntPtr v1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setSub_f(IntPtr ptr, IntPtr v0, float v1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setMul(IntPtr ptr, IntPtr v0, IntPtr v1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setMul_f(IntPtr ptr, IntPtr v1, float r);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setDiv(IntPtr ptr, IntPtr v0, IntPtr v1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setDiv4(IntPtr ptr, IntPtr v0, IntPtr v1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setDot3(IntPtr ptr, IntPtr v0, IntPtr v1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setDot4(IntPtr ptr, IntPtr v0, IntPtr v1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setSubMul_f(IntPtr ptr, IntPtr a, IntPtr b, float r);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setAddMul_f(IntPtr ptr, IntPtr a, IntPtr b, float r);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setAddMul(IntPtr ptr, IntPtr a, IntPtr x, IntPtr y);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setSubMul(IntPtr ptr, IntPtr a, IntPtr x, IntPtr y);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setCross(IntPtr ptr, IntPtr v0, IntPtr v1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setReciprocal(IntPtr  ptr, IntPtr v);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setSqrt(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setSqrtInverse(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setInterpolate(IntPtr ptr, IntPtr a, IntPtr b, float t);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_equal(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_notEqual(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_less(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_lessEqual(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_greater(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_greaterEqual(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_lessZero(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_lessEqualZero(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_greaterZero(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_greaterEqualZero(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_equalZero(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_compare_notEqualZero(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_signBitSet(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4_signBitClear(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setSelect(IntPtr ptr, IntPtr compareMask, IntPtr trueValue, IntPtr falseValue);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_zeroIfFalse(IntPtr ptr, IntPtr compareMask);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_zeroIfTrue(IntPtr ptr, IntPtr compareMask);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setFlipSign_m(IntPtr ptr, IntPtr v, IntPtr mask);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setFlipSign(IntPtr ptr, IntPtr v, IntPtr vSign);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setFlipSign_f(IntPtr ptr, IntPtr v, float sSign);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setAbs(IntPtr ptr, IntPtr v);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setMin(IntPtr ptr, IntPtr a, IntPtr b);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setMax(IntPtr ptr, IntPtr a, IntPtr b);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setClamped(IntPtr ptr, IntPtr a, IntPtr minVal, IntPtr maxVal);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_setClampedToMaxLength(IntPtr ptr, IntPtr vSrc, float maxLen);

  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkVector4_isOk1(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkVector4_isOk2(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkVector4_isOk3(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkVector4_isOk4(IntPtr ptr);

  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_equal(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_normalize3(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_normalize4(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4_normalize3IfNotZero(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern float hkVector4_length3(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern float hkVector4_length4(IntPtr ptr);

  #endregion

  #region IDisposable

  public void Dispose()
  {
    Dispose(true);
    GC.SuppressFinalize(this);
  }

  protected virtual void Dispose(bool disposing)
  {
    if (!m_disposed)
    {
      if (disposing)
      {
        // Release managed resources            
      }

      // Release unmanaged resources    
      hkVector4_delete(ptr);
      ptr = IntPtr.Zero;
      m_disposed = true;
    }
  }

  ~hkVector4()
  {
    Dispose(false);
  }

  private bool m_disposed;

  #endregion
}