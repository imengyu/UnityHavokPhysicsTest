using UnityEngine;
using PhyicsRT;

public class Test : MonoBehaviour {
    private void Start() {
        PhysicsApi.API.TestAssert();
    }
}