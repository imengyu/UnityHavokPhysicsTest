using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[AddComponentMenu("PhysicsRT/Physics List Shape")]
[DefaultExecutionOrder(110)]
[DisallowMultipleComponent] 
public class PhysicsListShape : PhysicsShapeContainer
{
    [SerializeField]
    List<PhysicsShape> m_childShapes;

    public List<PhysicsShape> ChildShapes => m_childShapes;

    protected override IntPtr CreatePtr() {
        return IntPtr.Zero;
    }
    protected override void DestroyPtr() {
        
    }
  
}
