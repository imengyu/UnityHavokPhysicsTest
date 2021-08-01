
using UnityEditor;
using UnityEngine;

public class PhysicsOptions : ScriptableObject
{
    [Tooltip("�Ƿ����ö��߳�ģ��")]
    public bool EnableMultithreaded = false;
    [Tooltip("С�ڴ�صĴ�С")]
    [Range(8, 2048)]
    public int SmallPoolSize = 32;
    [Tooltip("�����ڴ滺�����Ĵ�С")]
    [Range(16, 2048)]
    public int UpdateBufferSize = 128;

    #region Base

    private static PhysicsOptions _instance = null;
    
    public static PhysicsOptions Instance{
        get {
            if(_instance == null) {
                _instance = Resources.Load<PhysicsOptions>("PhysicsOptions");

            #if UNITY_EDITOR
                if(_instance == null){
                    _instance =  PhysicsOptions.CreateInstance<PhysicsOptions>();
                    try
                    {
                        AssetDatabase.CreateAsset(_instance, "Assets/Resources/PhysicsOptions.asset");
                    }
                    catch {
                        
                    }
                }
            #endif

            }
            return _instance;
        }
    }
    #if UNITY_EDITOR
    [MenuItem("PhysicsRT/Settings")]
    public static void Open() {
        Selection.activeObject = Instance;
    }
    #endif

    #endregion
}
