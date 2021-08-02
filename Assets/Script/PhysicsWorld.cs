using PhyicsRT.Utils;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace PhyicsRT
{
    [AddComponentMenu("PhysicsRT/Physics World")]
    [DefaultExecutionOrder(190)]
    [DisallowMultipleComponent]
    public class PhysicsWorld : MonoBehaviour
    {
        [Tooltip("如果需要任何连续模拟，请使用此模拟。 (创建后更改此值无效)")]
        public bool Continuous = false;
        [Tooltip("世界的引力。默认值是 (0, -9.8, 0). (创建后更改此值无效，请使用)")]
        public Vector3 Gravity = new Vector3(0, -9.81f, 0);
        [Tooltip("指定物理引擎将执行的解算器迭代次数。值越高，稳定性越高，但性能也越差。 (创建后更改此值无效)")]
        public int SolverIterationCount = 4;
        [Tooltip("设置物理边界为边长原点为中心的立方体。 (创建后更改此值无效)")]
        public float BroadPhaseWorldSize = 1000;
        [Tooltip("碰撞容限。这用于创建和保持接触点，即使对于非穿透性对象也是如此。这大大提高了系统的稳定性。默认碰撞容限为0.1f。 (创建后更改此值无效)")]
        public float CollisionTolerance = 0.1f;
        [Tooltip("是否启用物理模拟")]
        public bool Simulating = true;
        [Tooltip("是否启用VisualDebugger (创建后更改此值无效)")]
        public bool VisualDebugger = true;

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

        private SimpleLinkedList<PhysicsBody> bodysList = new SimpleLinkedList<PhysicsBody>();
        private PhysicsBody bodyCurrent = null;
        private IntPtr physicsWorldPtr = IntPtr.Zero;
        private IntPtr bodysUpdateBuffer = IntPtr.Zero;
        private int updateBufferSize = 0;

        private void Awake() {
            var layerNames = Resources.Load<PhysicsLayerNames>("PhysicsLayerNames");
            Debug.Assert(layerNames != null);

            updateBufferSize = PhysicsOptions.Instance.UpdateBufferSize;

            int currentScenseIndex = SceneManager.GetActiveScene().buildIndex;
            if(PhysicsWorlds.ContainsKey(currentScenseIndex)) 
                Debug.LogError("There can only one PhysicsWorld instance in a scense.");
            else {
                PhysicsWorlds.Add(currentScenseIndex, this);
                physicsWorldPtr = PhysicsApi.API.CreatePhysicsWorld(
                    PhysicsApi.API.CreateVec3(Gravity.x, Gravity.y, Gravity.z),
                    SolverIterationCount,
                    BroadPhaseWorldSize,
                    CollisionTolerance,
                    Continuous,
                    VisualDebugger,
                    0xffffffff,
                    layerNames.GetGroupFilterMasks());
                bodysUpdateBuffer = Marshal.AllocHGlobal(Marshal.SizeOf<float>() * 8 * updateBufferSize);
            }
        }
        private void OnDestroy() {
            int currentScenseIndex = SceneManager.GetActiveScene().buildIndex;
            if(PhysicsWorlds.ContainsKey(currentScenseIndex)) 
                PhysicsWorlds.Remove(currentScenseIndex);
            if (physicsWorldPtr != IntPtr.Zero)
            {
                PhysicsApi.API.DestroyPhysicsWorld(physicsWorldPtr);
                physicsWorldPtr = IntPtr.Zero;
            }
            if (bodysUpdateBuffer != IntPtr.Zero)
            {
                Marshal.FreeHGlobal(bodysUpdateBuffer);
                bodysUpdateBuffer = IntPtr.Zero;
            }
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
                UpdateAllBodys();
            }
        }

        private void UpdateAllBodys()
        {
            float[] dat = new float[8 * updateBufferSize];

            bodyCurrent = bodysList.getBegin();
            while(bodyCurrent != bodysList.getEnd() && bodyCurrent != null)
            {
                PhysicsApi.API.ReadPhysicsWorldBodys(physicsWorldPtr, bodysUpdateBuffer, updateBufferSize);
                Marshal.Copy(bodysUpdateBuffer, dat, 0, 8 * updateBufferSize);

                int count = 0;
                while(bodyCurrent != null && count < updateBufferSize)
                {
                    bodyCurrent.transform.position = new Vector3(
                        dat[count * 8 + 0],
                        dat[count * 8 + 1],
                        dat[count * 8 + 2]
                    );
                    bodyCurrent.transform.rotation = new Quaternion(
                        dat[count * 8 + 3], 
                        dat[count * 8 + 4], 
                        dat[count * 8 + 5], 
                        dat[count * 8 + 6]
                    );

                    count++;
                    bodyCurrent = bodyCurrent.next;
                }
            }
        }

        public void AddBody(PhysicsBody body) {
            bodysList.add(body);
        }
        public void RemoveBody(PhysicsBody body) {
            bodysList.remove(body);
        }
        public IntPtr GetPtr() { return physicsWorldPtr; }
    }
}
