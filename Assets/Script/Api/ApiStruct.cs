using System;
using System.Runtime.InteropServices;

namespace PhyicsRT
{
  [StructLayout(LayoutKind.Sequential)]
  internal struct sInitStruct
  {
    public IntPtr errCallback;
    public bool mulithread;
    public int smallPoolSize;
  };
  [StructLayout(LayoutKind.Sequential)]
  struct sConvexHullResult
  {
      [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8, ArraySubType = UnmanagedType.R4)]
      float[] aabb; //min(4) max(4) 
      int verticesCount;
      int trianglesCount;
  };
}