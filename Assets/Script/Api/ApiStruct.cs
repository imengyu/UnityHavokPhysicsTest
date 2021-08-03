using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace PhyicsRT
{
  [StructLayout(LayoutKind.Sequential)]
  internal struct sVec3
  {
    public float x;
    public float y;
    public float z;

    public static Vector3 FromNativeToVector3(IntPtr ptr) { 
      var vOut = Marshal.PtrToStructure<sVec3>(ptr);
      return new Vector3(vOut.x, vOut.y, vOut.z);
    }
  };
  [StructLayout(LayoutKind.Sequential)]
  internal struct sVec4
  {
    public float x;
    public float y;
    public float z;
    public float w;

    public static Vector4 FromNativeToVector4(IntPtr ptr) { 
      var vOut = Marshal.PtrToStructure<sVec4>(ptr);
      return new Vector4(vOut.x, vOut.y, vOut.z, vOut.w);
    }
  };

  [StructLayout(LayoutKind.Sequential)]
  internal struct sInitStruct
  {
    public IntPtr errCallback;
    public bool mulithread;
    public int smallPoolSize;
  };
  [StructLayout(LayoutKind.Sequential)]
  public struct sConvexHullResult
  {
      [MarshalAs(UnmanagedType.ByValArray, SizeConst = 8, ArraySubType = UnmanagedType.R4)]
      public float[] aabb; //min(4) max(4) 
      public int verticesCount;
      public int trianglesCount;
  };
}