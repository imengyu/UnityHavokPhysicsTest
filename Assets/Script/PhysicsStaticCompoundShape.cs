using System;
using System.Collections.Generic;
using UnityEngine;

[AddComponentMenu("PhysicsRT/Physics Static Compound Shape")]
[DefaultExecutionOrder(110)]
[DisallowMultipleComponent] 
public class PhysicsStaticCompoundShape : PhysicsShapeContainer
{
    [SerializeField]
    List<PhysicsShape> m_instances;

    public List<PhysicsShape> Instances => m_instances;

    public void AddInstance(PhysicsShape physicsShape) {
        m_instances.Add(physicsShape);


    }
    public void Bake() {

    }

    protected override IntPtr CreatePtr() {
        return IntPtr.Zero;
    }
    protected override void DestroyPtr() {
        
    }
}
