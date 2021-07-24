using System;
using System.Runtime.InteropServices;

public class hkVector4fComparison : IDisposable
{
  public enum Mask
  {
    INDEX_W = 3,  // Index of the w component
    INDEX_Z = 2,
    INDEX_Y = 1,
    INDEX_X = 0,

    MASK_NONE = 0x0,          // 0000
    MASK_W = (1 << INDEX_W),    // 0001
    MASK_Z = (1 << INDEX_Z),    // 0010
    MASK_ZW = (MASK_Z | MASK_W),  // 0011

    MASK_Y = (1 << INDEX_Y),    // 0100
    MASK_YW = (MASK_Y | MASK_W),  // 0101
    MASK_YZ = (MASK_Y | MASK_Z),  // 0110
    MASK_YZW = (MASK_YZ | MASK_W),  // 0111

    MASK_X = (1 << INDEX_X),    // 1000
    MASK_XW = (MASK_X | MASK_W),  // 1001
    MASK_XZ = (MASK_X | MASK_Z),  // 1010
    MASK_XZW = (MASK_XZ | MASK_W),  // 1011

    MASK_XY = (MASK_X | MASK_Y),  // 1100
    MASK_XYW = (MASK_XY | MASK_W),  // 1101
    MASK_XYZ = (MASK_XY | MASK_Z),  // 1110
    MASK_XYZW = (MASK_XY | MASK_ZW) // 1111
  };

  public hkVector4fComparison(IntPtr nativeptr)
  {
    ptr = nativeptr;
  }
  public hkVector4fComparison(Mask mask)
  {
    ptr = hkVector4fComparison_new((int)mask);
  }

  public Mask getMask() {
    return (Mask)hkVector4fComparison_getMask(ptr);
  }
  public Mask getMask(Mask mask) {
    return (Mask)hkVector4fComparison_getMask(ptr, (int)mask);
  }
  public bool allAreSet() {
    return hkVector4fComparison_allAreSet(ptr);
  }
  public bool anyIsSet() {
    return hkVector4fComparison_anyIsSet(ptr);
  }
  public int getIndexOfFirstComponentSet() {
    return hkVector4fComparison_getIndexOfFirstComponentSet(ptr);
  }
  public int getIndexOfLastComponentSet() {
    return hkVector4fComparison_getIndexOfLastComponentSet(ptr);
  }
  public hkVector4fComparison horizontalAnd1() {
    return new hkVector4fComparison(hkVector4fComparison_horizontalAnd1(ptr));
  }
  public hkVector4fComparison horizontalAnd2() {
    return new hkVector4fComparison(hkVector4fComparison_horizontalAnd2(ptr));
  }  
  public hkVector4fComparison horizontalAnd3() {
    return new hkVector4fComparison(hkVector4fComparison_horizontalAnd3(ptr));
  } 
  public hkVector4fComparison horizontalAnd4() {
    return new hkVector4fComparison(hkVector4fComparison_horizontalAnd4(ptr));
  }
  public hkVector4fComparison horizontalOr1() {
    return new hkVector4fComparison(hkVector4fComparison_horizontalOr1(ptr));
  }
  public hkVector4fComparison horizontalOr2() {
    return new hkVector4fComparison(hkVector4fComparison_horizontalOr2(ptr));
  }
  public hkVector4fComparison horizontalOr3() {
    return new hkVector4fComparison(hkVector4fComparison_horizontalOr3(ptr));
  }
  public hkVector4fComparison horizontalOr4() {
    return new hkVector4fComparison(hkVector4fComparison_horizontalOr4(ptr));
  }

  #region API

  private IntPtr ptr = IntPtr.Zero;

  public IntPtr Ptr { get { return ptr; } }

  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4fComparison_new(int mask);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern void hkVector4fComparison_delete(IntPtr ptr);
  [DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern int hkVector4fComparison_getMask(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern int hkVector4fComparison_getMask(IntPtr ptr, int m);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkVector4fComparison_allAreSet(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern bool hkVector4fComparison_anyIsSet(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern int hkVector4fComparison_getIndexOfFirstComponentSet(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern int hkVector4fComparison_getIndexOfLastComponentSet(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4fComparison_horizontalAnd1(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4fComparison_horizontalAnd2(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern IntPtr hkVector4fComparison_horizontalAnd3(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern  IntPtr hkVector4fComparison_horizontalAnd4(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern  IntPtr hkVector4fComparison_horizontalOr1(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern  IntPtr hkVector4fComparison_horizontalOr2(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern  IntPtr hkVector4fComparison_horizontalOr3(IntPtr ptr);
	[DllImport(PhysicsApi.DLL_NNAME, CallingConvention = PhysicsApi._CallingConvention)]
  public static extern  IntPtr hkVector4fComparison_horizontalOr4(IntPtr ptr);

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
      hkVector4fComparison_delete(ptr);
      ptr = IntPtr.Zero;
      m_disposed = true;
    }
  }

  ~hkVector4fComparison()
  {
    Dispose(false);
  }

  private bool m_disposed;

  #endregion

}