using System;
using UnityEngine;

namespace PhysicsRT {

    [AddComponentMenu("PhysicsRT/Constraints/WheelConstraint")]
    public class WheelConstraint : PhysicsConstraint {

        public PhysicsBody Chassis;

        public Vector3 Povit;
        public Vector3 Axle;
        public Vector3 Suspension;
        public Vector3 Steering;
        public float SuspensionLimitMin;
        public float SuspensionLimitMax; 
        public float SuspensionStrength;
        public float SuspensionDamping;

        public override void Create() {
            if(Chassis == null) 
                throw new Exception("Chassis is null");
            var ptr = CreatePre();
            var otherPtr = Chassis.GetPtr();
            if(ptr == IntPtr.Zero)
                throw new Exception("This body hasn't been created yet");
            if(otherPtr == IntPtr.Zero)
                throw new Exception("Chassis hasn't been created yet");
            CreateLastStep(PhysicsApi.API.CreateWheelConstraint(ptr, otherPtr, transform.TransformPoint(Povit), Axle, Suspension,
                Steering, SuspensionLimitMin, SuspensionLimitMax, SuspensionStrength, SuspensionDamping, GetConstraintBreakData()));
        }
    }
}