
using UnityEditor;
using UnityEngine;

public class PhysicsOptions : ScriptableObject
{
    public bool EnableMultithreaded = false;


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
    [MenuItem("PhysicsRT/Setting")]
    public static void Open() {
        Selection.activeObject = Instance;
    }
    #endif

    #endregion
}
