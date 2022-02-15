using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TriggerBottom : MonoBehaviour
{

    public BallScript bs;
    public GameController gc;
    // Start is called before the first frame update
    void OnTriggerEnter (Collider col)
    {
        bs.lives--;
        Debug.Log("Pozostalo " + bs.lives + " zyc");
        gc.Reset();
    }
}
