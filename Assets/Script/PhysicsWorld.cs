using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace PhyicsRT
{
    [AddComponentMenu("PhysicsRT/Physics World")]
    [DefaultExecutionOrder(90)]
    [DisallowMultipleComponent]
    public class PhysicsWorld : MonoBehaviour
    {
        [Tooltip("如果需要任何连续模拟，请使用此模拟。")]
        public bool Continuous = false;
        [Tooltip("世界的引力。默认值是 (0, -9.8, 0).")]
        public Vector3 Gravity = new Vector3(0, -9.81f, 0);
        [Tooltip("指定物理引擎将执行的解算器迭代次数。值越高，稳定性越高，但性能也越差。")]
        public int SolverIterationCount = 4;
        [Tooltip("设置物理边界为边长原点为中心的立方体。")]
        public float BroadPhaseWorldSize = 1000;
        [Tooltip("碰撞容限。这用于创建和保持接触点，即使对于非穿透性对象也是如此。这大大提高了系统的稳定性。默认碰撞容限为0.1f。")]
        public float CollisionTolerance = 0.1f;
        [Tooltip("是否启用物理模拟")]
        public bool Simulating = true;

        /// <summary>
        /// 所有物理场景
        /// </summary>
        /// <typeparam name="int">Unity场景的buildIndex</typeparam>
        /// <typeparam name="PhysicsWorld"></typeparam>
        /// <returns></returns>
        public static Dictionary<int, PhysicsWorld> PhysicsWorlds { get; } = new Dictionary<int, PhysicsWorld>();
        /// <summary>
        /// 获取当前场景的物理场景
        /// </summary>
        /// <returns></returns>
        public static PhysicsWorld GetCurrentScensePhysicsWorld() {
            int currentScenseIndex = SceneManager.GetActiveScene().buildIndex;
            if(PhysicsWorlds.TryGetValue(currentScenseIndex, out var a))
                return a;
            return null;
        }

        private List<PhysicsBody> bodys = new List<PhysicsBody>();
        private IntPtr physicsWorldPtr = IntPtr.Zero;

        private void Awake() {
            int currentScenseIndex = SceneManager.GetActiveScene().buildIndex;
            if(PhysicsWorlds.ContainsKey(currentScenseIndex)) 
                Debug.LogError("There can only one PhysicsWorld instance in a scense.");
            else {
                PhysicsWorlds.Add(currentScenseIndex, this);
                physicsWorldPtr = PhysicsApi.API.CreatePhysicsWorld(
                    PhysicsApi.API.CreateVec3(Gravity.x, Gravity.y, Gravity.z),
                    SolverIterationCount,
                    BroadPhaseWorldSize,
                    CollisionTolerance);
            }
        }
        private void OnDestroy() {
            int currentScenseIndex = SceneManager.GetActiveScene().buildIndex;
            if(PhysicsWorlds.ContainsKey(currentScenseIndex)) 
                PhysicsWorlds.Remove(currentScenseIndex);
            PhysicsApi.API.DestroyPhysicsWorld(physicsWorldPtr);
            physicsWorldPtr = IntPtr.Zero;
        }
        private void Start()
        {
            
        }
        private void Update()
        {
            
        }
        private void FixedUpdate() {
            if(Simulating) {

                //StepWorld
                PhysicsApi.API.StepPhysicsWorld(physicsWorldPtr, Time.deltaTime);

                //Update all bodys position
                foreach(PhysicsBody body in bodys) {
                    if(body.gameObject.activeSelf) {
                        
                    }
                }
            }
        }

        public void AddBody(PhysicsBody body) {
            if(!bodys.Contains(body)) {
                bodys.Add(body);
            }
        }
        public void RemoveBody(PhysicsBody body) {
            if(bodys.Contains(body)) {
                bodys.Remove(body);
            }
        }
    }
}
