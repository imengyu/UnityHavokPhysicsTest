using System;
using System.Runtime.InteropServices;

public class hkRotation : hkMatrix3
{
  public hkRotation(IntPtr nativePtr) : base(nativePtr)
  {
  }

  public void set(hkQuaternion q) {
    hkRotation_set(Ptr, q.Ptr);
  }
  public void setAxisAngle(hkVector4 axis, float angle) {
    hkRotation_setAxisAngle(Ptr, axis.Ptr, angle);
  }
  public bool isOrthonormal(float epsilon) {
    return hkRotation_isOrthonormal(Ptr, epsilon);
  }
  public new bool isOk() {
    return hkRotation_isOk(Ptr);
  }
  public void renormalize() {
    hkRotation_renormalize(Ptr);
  }
  
  #region API

  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkRotation_set(IntPtr ptr, IntPtr q);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkRotation_setAxisAngle(IntPtr ptr, IntPtr axis, float angle);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkRotation_isOrthonormal(IntPtr ptr, float epsilon = 1e-5f);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkRotation_isOk(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkRotation_renormalize(IntPtr ptr);

  #endregion
}