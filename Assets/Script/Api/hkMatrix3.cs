using System;
using System.Runtime.InteropServices;

public class hkMatrix3 : IDisposable
{
  public hkMatrix3() { ptr = hkMatrix3_new(); }
  public hkMatrix3(IntPtr nativePtr) { ptr = nativePtr; }

  public hkVector4 getColumn(int i) {  return new hkVector4(hkMatrix3_getColumn(ptr, i)); }
  public void getRow(int i, hkVector4 outVector) { hkMatrix3_getRow(ptr, i, outVector.Ptr); }
  public void setColumn0(hkVector4 c) { hkMatrix3_setColumn0(ptr, c.Ptr); }
  public void setColumn1(hkVector4 c) { hkMatrix3_setColumn1(ptr, c.Ptr); }  
  public void setColumn2(hkVector4 c) { hkMatrix3_setColumn2(ptr, c.Ptr); }
  public void setRows(hkVector4 r0, hkVector4 r1, hkVector4 r2) { hkMatrix3_setRows(ptr, r0.Ptr, r1.Ptr, r2.Ptr); }
  public void getRows(hkVector4 r0, hkVector4 r1, hkVector4 r2) { hkMatrix3_getRows(ptr, r0.Ptr, r1.Ptr, r2.Ptr); }
  public void setCols(hkVector4 r0, hkVector4 r1, hkVector4 r2) { hkMatrix3_setCols(ptr, r0.Ptr, r1.Ptr, r2.Ptr); }
  public void getCols(hkVector4 r0, hkVector4 r1, hkVector4 r2) { hkMatrix3_getCols(ptr, r0.Ptr, r1.Ptr, r2.Ptr); }
  public void setZero() { hkMatrix3_setZero(ptr); }
  public void setIdentity() { hkMatrix3_setIdentity(ptr); }
  public static hkMatrix3 getIdentity() { return new hkMatrix3(hkMatrix3_getIdentity()); }
  
  public bool isApproximatelyEqual(hkMatrix3 m, float epsilon = 1e-3f) { return hkMatrix3_isApproximatelyEqual(ptr, m.Ptr, epsilon); }
  public bool isSymmetric(float epsilon = 1e-3f) { return hkMatrix3_isSymmetric(ptr, epsilon); }
  public void setCrossSkewSymmetric(hkVector4 r) { hkMatrix3_setCrossSkewSymmetric(ptr, r.Ptr); }
  public hkResult invert(float epsilon) { return hkMatrix3_invert(ptr, epsilon); }
  public void setInverseSymmetric(hkMatrix3 m) { hkMatrix3_setInverseSymmetric(ptr, m.Ptr); }
  public void solveSymmetric(hkVector4 b, hkVector4 v) { hkMatrix3_solveSymmetric(ptr, b.Ptr, v.Ptr); }
  public void invertSymmetric() { hkMatrix3_invertSymmetric(ptr); }
  public void frobeniusNormSqr() { hkMatrix3_frobeniusNormSqr(ptr); }
  public void transpose() { hkMatrix3_transpose(ptr); }
  public bool isOk() { return hkMatrix3_isOk(ptr); }
  public float getDeterminant() { return hkMatrix3_getDeterminant(ptr); }
  public void setTranspose(hkMatrix3 s){ hkMatrix3_setTranspose(ptr, s.Ptr); }
  public void setMul(hkMatrix3 a, hkMatrix3 b){ hkMatrix3_setMul(ptr, a.Ptr, b.Ptr); }
  public void setMulInverse(hkMatrix3 a, hkRotation b){ hkMatrix3_setMulInverse(ptr, a.Ptr, b.Ptr); }
  public void setMulInverseMul(hkRotation a, hkMatrix3 b){ hkMatrix3_setMulInverseMul(ptr, a.Ptr, b.Ptr); }
  public void setMul(float scale, hkMatrix3 a){ hkMatrix3_setMul_scale(ptr, scale, a.Ptr); }
  public void setDiagonalMul(hkVector4 vDiag, hkMatrix3 a){ hkMatrix3_setDiagonalMul(ptr, vDiag.Ptr, a.Ptr); }
  public void addDiagonal(float diag){ hkMatrix3_addDiagonal(ptr, diag); }
  public void setTransposeMul(hkMatrix3 a, hkMatrix3 b){ hkMatrix3_setTransposeMul(ptr, a.Ptr, b.Ptr); }
  public void addMul(float scale, hkMatrix3 a) { hkMatrix3_addMul(ptr, scale, a.Ptr); }
  public void changeBasis(hkRotation t){ hkMatrix3_changeBasis(ptr, t.Ptr); }
  public void add(hkMatrix3 a) { hkMatrix3_add(ptr, a.Ptr); }
  public void sub(hkMatrix3 a) { hkMatrix3_sub(ptr, a.Ptr); }
  public void mul(hkMatrix3 a) { hkMatrix3_mul(ptr, a.Ptr); }
  public void mul(float scale) { hkMatrix3_mul_scale(ptr, scale); }
  public void set(hkMatrix3 a) { hkMatrix3_operator_equal(ptr, a.Ptr); }
  public void multiplyVector(hkVector4 vectorIn, hkVector4 resultOut){ hkMatrix3_multiplyVector(ptr, vectorIn.Ptr, resultOut.Ptr); }

  #region API

  private IntPtr ptr = IntPtr.Zero;

  public IntPtr Ptr { get { return ptr; } }

  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkMatrix3_new();
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_delete(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkMatrix3_getColumn(IntPtr ptr, int i);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_getRow(IntPtr ptr, int row, IntPtr r);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setColumn0(IntPtr ptr, IntPtr c);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setColumn1(IntPtr ptr, IntPtr c);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setColumn2(IntPtr ptr, IntPtr c);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setRows(IntPtr ptr, IntPtr r0, IntPtr r1, IntPtr r2);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_getRows(IntPtr ptr, IntPtr r0, IntPtr r1, IntPtr r2);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setCols(IntPtr ptr, IntPtr c0, IntPtr c1, IntPtr c2);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_getCols(IntPtr ptr, IntPtr c0, IntPtr c1, IntPtr c2);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setZero(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setIdentity(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkMatrix3_getIdentity();
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkMatrix3_isApproximatelyEqual(IntPtr ptr, IntPtr m, float epsilon = 1e-3f);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkMatrix3_isSymmetric(IntPtr ptr, float epsilon = 1e-3f);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setCrossSkewSymmetric(IntPtr ptr, IntPtr r);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  [return:MarshalAs(UnmanagedType.I8)]
  public static extern hkResult hkMatrix3_invert(IntPtr ptr, float epsilon);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setInverseSymmetric(IntPtr ptr, IntPtr src);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_solveSymmetric(IntPtr ptr, IntPtr b, IntPtr v);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_invertSymmetric(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern  float hkMatrix3_frobeniusNormSqr(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_transpose(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setTranspose(IntPtr ptr, IntPtr s);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setMul(IntPtr ptr, IntPtr a, IntPtr b);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setMulInverse(IntPtr ptr, IntPtr a, IntPtr b);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setMulInverseMul(IntPtr ptr, IntPtr a, IntPtr b);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setMul_scale(IntPtr ptr, float scale, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setDiagonalMul(IntPtr ptr, IntPtr vDiag, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_addDiagonal(IntPtr ptr, float diag);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_setTransposeMul(IntPtr ptr, IntPtr a, IntPtr b);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_addMul(IntPtr ptr, float scale, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_changeBasis(IntPtr ptr, IntPtr t);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_add(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_sub(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_mul(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_mul_scale(IntPtr ptr, float scale);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_operator_equal(IntPtr ptr, IntPtr a);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern  bool hkMatrix3_isOk(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_multiplyVector(IntPtr ptr, IntPtr vectorIn, IntPtr resultOut);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern float hkMatrix3_getDeterminant(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  [return:MarshalAs(UnmanagedType.I8)]
  public static extern hkResult hkMatrix3_diagonalizeSymmetric(IntPtr ptr, IntPtr eigenVec, IntPtr eigenVal, int maxIter = 20, float epsilon = PhysicsApi.HK_FLOAT_EPSILON);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  [return:MarshalAs(UnmanagedType.I8)]
  public static extern hkResult hkMatrix3_diagonalizeSymmetricWarmStart(IntPtr ptr, IntPtr eigenVec, IntPtr eigenVal, int maxIter = 20, float epsilon = PhysicsApi.HK_FLOAT_EPSILON);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkMatrix3_diagonalizeSymmetricApproximation(IntPtr ptr, IntPtr eigenVec, IntPtr eigenVal, int maxIter = 10);

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
      hkMatrix3_delete(ptr);
      ptr = IntPtr.Zero;
      m_disposed = true;
    }
  }

  ~hkMatrix3()
  {
    Dispose(false);
  }

  private bool m_disposed;

  #endregion

}