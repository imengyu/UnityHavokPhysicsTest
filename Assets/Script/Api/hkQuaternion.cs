using System;
using System.Runtime.InteropServices;

public class hkQuaternion : IDisposable
{
  public hkQuaternion() {}
  public hkQuaternion(float x, float y, float z, float w) {
    ptr = hkQuaternion_new_xyzr(x, y, z, w);
  }
  public hkQuaternion(hkVector4 axis, float w) {
    ptr = hkQuaternion_new_axis(axis.Ptr, w);
  }
  public hkQuaternion(IntPtr nativePtr) {
    ptr = nativePtr;
  }

  public void set(float x, float y, float z, float w) {
    hkQuaternion_set(ptr, x, y, z, w);
  }
  public void set(hkQuaternion quaternion) {
    hkQuaternion_operator_equal(ptr, quaternion.ptr);
  }
  public void setIdentity() {
    hkQuaternion_setIdentity(ptr);
  }
  public void setInverse(hkQuaternion q) {
    hkQuaternion_setInverse(ptr, q.ptr);
  }
  public void setMul(float r, hkQuaternion q) {
    hkQuaternion_setMul(ptr, r, q.ptr);
  }
  public void addMul(float r, hkQuaternion q) {
    hkQuaternion_addMul(ptr, r, q.ptr);
  }
  public void setMul(hkQuaternion q0, hkQuaternion q1) {
    hkQuaternion_setMul(ptr, q0.ptr, q1.ptr);
  }
  public void mul(hkQuaternion q) {
    hkQuaternion_mul(ptr, q.ptr);
  }
  public void setMulInverse(hkQuaternion q0, hkQuaternion q1) {
    hkQuaternion_setMulInverse(ptr, q0.ptr, q1.ptr);
  }
  public void setInverseMul(hkQuaternion q0, hkQuaternion q1) {
    hkQuaternion_setInverseMul(ptr, q0.ptr, q1.ptr);
  }
  public void estimateAngleTo(hkQuaternion to, hkVector4 angleOut) {
    hkQuaternion_estimateAngleTo(ptr, to.ptr, angleOut.Ptr);
  }
  public void setAxisAngle(hkVector4 axis, float angle) {
    hkQuaternion_setAxisAngle(ptr, axis.Ptr, angle);
  }
  public void setFromEulerAngles(float roll, float pitch, float yaw) {
    hkQuaternion_setFromEulerAngles(ptr, roll, pitch, yaw);
  }
  public void removeAxisComponent(hkVector4 axis) {
    hkQuaternion_removeAxisComponent(ptr, axis.Ptr);
  }
  public void decomposeRestAxis(hkVector4 axis, hkQuaternion restOut, float angleOut) {
    hkQuaternion_decomposeRestAxis(ptr, axis.Ptr, restOut.ptr, angleOut);
  }
  public void setSlerp(hkQuaternion q0, hkQuaternion q1, float t) {
    hkQuaternion_setSlerp(ptr, q0.Ptr, q1.ptr, t);
  }
  public void setBarycentric(hkQuaternion qVerts, hkVector4 vLambda) {
    hkQuaternion_setBarycentric(ptr, qVerts.ptr, vLambda.Ptr);
  }
  public void setReal(float r) {
    hkQuaternion_setReal(ptr, r);
  }
  public float getReal() {
    return hkQuaternion_getReal(ptr);
  }
  public void setImag(hkVector4 i) {
    hkQuaternion_setImag(ptr, i.Ptr);
  }
  public hkVector4 getImag() {
    return new hkVector4(hkQuaternion_getImag(ptr));
  }
  public float getAngle() {
    return hkQuaternion_getAngle(ptr);
  }
  public void getAxis(hkVector4 axis) {
    hkQuaternion_getAxis(ptr, axis.Ptr);
  }
  public bool hasValidAxis() {
    return hkQuaternion_hasValidAxis(ptr);
  }
  public void setClosest(hkQuaternion q, hkQuaternion qReference) {
    hkQuaternion_setClosest(ptr, q.ptr, qReference.ptr);
  }
  public void setFlippedRotation(hkVector4 from) {
    hkQuaternion_setFlippedRotation(ptr, from.Ptr);
  }
  public void normalize() {
    hkQuaternion_normalize(ptr);
  }

  public hkVector4 m_vec {
    get {
      hkVector4 m_vec_temp = new hkVector4();
      hkQuaternion_get_m_vec(ptr, m_vec_temp.Ptr);
      return m_vec_temp;
    }
    set {
      hkQuaternion_set_m_vec(ptr, value.Ptr);
    }
  }

  #region API

  private IntPtr ptr = IntPtr.Zero;

  public IntPtr Ptr { get { return ptr; } }

  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkQuaternion_new();
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_delete(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkQuaternion_new_xyzr(float x, float y, float z, float r);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkQuaternion_new_axis(IntPtr axis, float angle);

  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_set(IntPtr ptr, float x, float y, float z, float r);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setIdentity(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setInverse(IntPtr ptr, IntPtr q);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setMul(IntPtr ptr, float r, IntPtr q);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_addMul(IntPtr ptr, float r, IntPtr q);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setMul(IntPtr ptr, IntPtr q0, IntPtr q1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_mul(IntPtr ptr, IntPtr q);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setMulInverse(IntPtr ptr, IntPtr q0, IntPtr q1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setInverseMul(IntPtr ptr, IntPtr q0, IntPtr q1);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_estimateAngleTo(IntPtr ptr, IntPtr to, IntPtr angleOut);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setAxisAngle(IntPtr ptr, IntPtr axis, float angle);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setFromEulerAngles(IntPtr ptr, float roll, float pitch, float yaw);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_removeAxisComponent(IntPtr ptr, IntPtr axis);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_decomposeRestAxis(IntPtr ptr, IntPtr axis, IntPtr restOut, float angleOut);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setSlerp(IntPtr ptr, IntPtr q0, IntPtr q1, float t);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setBarycentric(IntPtr ptr, IntPtr qVerts, IntPtr vLambda);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setReal(IntPtr ptr, float r);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern float hkQuaternion_getReal(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setImag(IntPtr ptr, IntPtr i);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkQuaternion_getImag(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern float hkQuaternion_getAngle(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_getAxis(IntPtr ptr, IntPtr axis);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkQuaternion_hasValidAxis(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setClosest(IntPtr ptr, IntPtr q, IntPtr qReference);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_setFlippedRotation(IntPtr ptr, IntPtr from);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_normalize(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_operator_equal(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_get_m_vec(IntPtr ptr, IntPtr outV);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkQuaternion_set_m_vec(IntPtr ptr, IntPtr outV);

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
      hkQuaternion_delete(ptr);
      ptr = IntPtr.Zero;
      m_disposed = true;
    }
  }

  ~hkQuaternion()
  {
    Dispose(false);
  }

  private bool m_disposed;

  #endregion

  public override string ToString()
  {
    hkVector4 vec = m_vec;
    return "hkQuaternion (" + vec.x + "," + vec.y + "," + vec.z + "," + vec.w + ")";
  }
}