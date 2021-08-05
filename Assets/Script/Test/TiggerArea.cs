using PhysicsRT;
using UnityEngine;

public class TiggerArea : MonoBehaviour {
    public LightControl m_Light;

    private void Start() {
        var rigid = GetComponent<PhysicsBody>();
        if(rigid) {
            rigid.onTiggerEnter += OnBodyCollEnterCallback;
            rigid.onTiggerLeave += OnBodyCollLeaveCallback;
        }
    }

    int enterCount = 0;

    void OnBodyCollEnterCallback(PhysicsBody body, PhysicsBody other) {
        enterCount++;
         if(enterCount >= 0 && !m_Light.isOn)
            m_Light.isOn = true;
    }
    void OnBodyCollLeaveCallback(PhysicsBody body, PhysicsBody other) {
        enterCount--;
        if(enterCount <= 0)
            m_Light.isOn = false;
    }
}