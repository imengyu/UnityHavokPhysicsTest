using System;
using UnityEngine;

namespace PhysicsRT {

    [AddComponentMenu("PhysicsRT/Constraints/LimitedHingeConstraint")]
    public class LimitedHingeConstraint : MotorConstraint {
 
        public Vector3 Povit;
        public Vector3 Axis = Vector3.forward;
        public float AgularLimitMin = 0;
        public float AgularLimitMax = 360;

        public override void Create() {
            var ptr = CreatePre();
            var otherPtr = ConnectedBody.GetPtr();
            if(ptr == IntPtr.Zero)
                throw new Exception("This body hasn't been created yet");
            CreateLastStep(PhysicsApi.API.CreateLimitedHingeConstraint(ptr, otherPtr, transform.TransformPoint(Povit), Axis, 
                (AgularLimitMin - 270) * Mathf.Deg2Rad, 
                (AgularLimitMax - 270) * Mathf.Deg2Rad, 
                GetConstraintBreakData(), GetConstraintMotorData()));
        }
    }
}