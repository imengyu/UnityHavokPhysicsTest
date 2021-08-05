using System;
using UnityEngine;

namespace PhysicsRT {

    [AddComponentMenu("PhysicsRT/Constraints/PrismaticConstraint")]
    public class PrismaticConstraint : MotorConstraint {

        public PhysicsBody ConnectedBody;
        
        public Vector3 Povit;
        public Vector3 Axis = Vector3.forward;

        public override void Create() {
            var ptr = CreatePre();
            var otherPtr = ConnectedBody.GetPtr();
            if(ptr == IntPtr.Zero)
                throw new Exception("This body hasn't been created yet");
            CreateLastStep(PhysicsApi.API.CreatePrismaticConstraint(ptr, otherPtr, transform.TransformPoint(Povit), Axis, GetConstraintBreakData(), GetConstraintMotorData()));
        }
    }
}