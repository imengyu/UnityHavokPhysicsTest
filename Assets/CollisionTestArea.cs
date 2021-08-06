using PhysicsRT;
using UnityEngine;

public class CollisionTestArea : MonoBehaviour
{
    public TextMesh StatusText;
    public MeshRenderer CollisionTestAreaMeshRenderer;
    public Material NormalMaterial;
    public Material ActiveMaterial;

    void Start()
    {
        var rigid = GetComponent<PhysicsBody>();
        rigid.onCollisionEnter += onCollisionEnter;
        rigid.onCollisionStay += onCollisionStay;
        rigid.onCollisionLeave += onCollisionLeave;
    }

    int ixx = 0;

    private void Update() {
        if(ixx < 65535) ixx ++;
        else ixx = 0;

        if(ixx % 30 == 0) {
            StatusText.text = "enterCount: " + enterCount + "\nspeed: " + speed;
        }
    }


    float speed = 0;
    int _enterCount = 0;
    int enterCount {
        get => _enterCount;
        set {
            _enterCount = value;
            CollisionTestAreaMeshRenderer.material = _enterCount == 0 ? NormalMaterial : ActiveMaterial;
        }
    }

    void onCollisionEnter(PhysicsBody body, PhysicsBody other, PhysicsBodyCollisionInfo info) {
        speed = info.separatingVelocity;
        enterCount++;
    }
    void onCollisionStay(PhysicsBody body, PhysicsBody other, PhysicsBodyCollisionInfo info) {
        speed = info.separatingVelocity;
    }
    void onCollisionLeave(PhysicsBody body, PhysicsBody other) {
        enterCount--;
    }
}
