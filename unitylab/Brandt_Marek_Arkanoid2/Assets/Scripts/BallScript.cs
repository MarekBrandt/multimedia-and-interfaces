using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallScript : MonoBehaviour
{
    public int lives = 3;
    public int score = 0;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnCollisionEnter (Collision col)
    {
        if(col.transform.name == "Block")
        {
            Destroy(col.gameObject);
            score++;
           // Debug.Log("Score: " + score);
        }
    }

    public void StartPosition()
    {
        GetComponent<Rigidbody>().Sleep();
        transform.position = new Vector3(0, 0, 0);
    }
}
