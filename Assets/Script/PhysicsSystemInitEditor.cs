using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

[InitializeOnLoad]
public class PhysicsSystemInitEditor
{
    static bool firstPlay = false;

    static PhysicsSystemInitEditor()
    {
        EditorApplication.pauseStateChanged += PauseStateChanged;
        EditorApplication.quitting += Quitting;
    }

    static void PauseStateChanged(PauseState state)
    {
        if (EditorApplication.isPaused)
        {
            return;
        }
        if (!(EditorApplication.isPlaying && EditorApplication.isPlayingOrWillChangePlaymode))
        {
            return;
        }
        if (firstPlay)
        {
            return;
        }
        firstPlay = true;
        PhysicsSystemInit.DoInit();
    }
    static void Quitting() {
        PhysicsSystemInit.DoDestroy();
    }
}