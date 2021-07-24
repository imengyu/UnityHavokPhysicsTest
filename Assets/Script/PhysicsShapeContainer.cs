using System;
using UnityEngine;

[DefaultExecutionOrder(110)]
[DisallowMultipleComponent] 
public class PhysicsShapeContainer : MonoBehaviour
{
  private void Awake() {
    ptr = CreatePtr();
  }
  private void OnDestroy() {
    DestroyPtr();
  }

  private IntPtr ptr = IntPtr.Zero;

  public IntPtr Ptr => ptr;

  protected virtual IntPtr CreatePtr() {
    return IntPtr.Zero;
  }
  protected virtual void DestroyPtr() {
    
  }
  
}
