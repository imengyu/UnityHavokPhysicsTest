using UnityEditor;
using UnityEngine;

class StaticEditors : ScriptableObject
{

    [MenuItem("PhysicsRT/Edit PhysicsBody tag names")]
    public static void EditCustomPhysicsBodyTagNames()
    {
        Selection.activeObject = AssetDatabase.LoadAssetAtPath<CustomPhysicsBodyTagNames>("Assets/Resources/CustomPhysicsBodyTagNames.asset");
    }
    [MenuItem("PhysicsRT/Edit Physics material tag names")]
    public static void EditCustomMaterialTagNames()
    {
        Selection.activeObject = AssetDatabase.LoadAssetAtPath<CustomPhysicsMaterialTagNames>("Assets/Resources/CustomMaterialTagNames.asset");
    }
    [MenuItem("PhysicsRT/Edit Physics category names")]
    public static void EditPhysicsCategoryNames()
    {
        Selection.activeObject = AssetDatabase.LoadAssetAtPath<PhysicsCategoryNames>("Assets/Resources/PhysicsCategoryNames.asset");
    }
    
}
