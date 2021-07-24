using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Serialization;

public interface ITagNames
{
    IReadOnlyList<string> TagNames { get; }
}

[CreateAssetMenu(menuName = "PhysicsRT/Custom Physics Material Tag Names", fileName = "Custom Material Tag Names")]
public sealed partial class CustomPhysicsMaterialTagNames : ScriptableObject, ITagNames
{
    CustomPhysicsMaterialTagNames() { }

    public IReadOnlyList<string> TagNames => m_TagNames;
    [SerializeField]
    [FormerlySerializedAs("m_FlagNames")]
    string[] m_TagNames = Enumerable.Range(0, 8).Select(i => string.Empty).ToArray();

    void OnValidate()
    {
        if (m_TagNames.Length != 8)
            Array.Resize(ref m_TagNames, 8);
    }
}
