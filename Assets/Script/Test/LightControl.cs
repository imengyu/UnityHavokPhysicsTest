using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightControl : MonoBehaviour
{
    [SerializeField]
    private bool m_On = false;

    public Material m_OnMaterial = null;
    public Material m_OffMaterial = null;
    public Color m_OnColor = Color.green;
    public Color m_OffColor = Color.red;

    public Light m_Light = null;
    public MeshRenderer m_Sphere = null;

    void Start()
    {
        isOn = m_On;
    }

    public bool isOn {
        get { return m_On; }
        set {
            if(value) {
                m_Light.color = m_OnColor;
                m_Sphere.material = m_OnMaterial;
            } else {
                m_Light.color = m_OffColor;
                m_Sphere.material = m_OffMaterial;
            }
        }
    }
}
