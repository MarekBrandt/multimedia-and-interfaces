using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PaddleControler : MonoBehaviour
{
    public float paddleMoveSpeed = 0.1f;
    public float paddleRotateSpeed = 1.0f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.RightArrow))
        {
            transform.Translate(paddleMoveSpeed, 0, 0, Space.World);
           // Debug.Log("prawo");
        }
        else if (Input.GetKey(KeyCode.LeftArrow))
        {
            transform.Translate(-paddleMoveSpeed, 0, 0, Space.World);
            // Debug.Log("prawo");
        }
        else if (Input.GetKey(KeyCode.UpArrow))
        {
            transform.Rotate(0, 0, paddleRotateSpeed, Space.World);
            // Debug.Log("prawo");
        }
        else if (Input.GetKey(KeyCode.DownArrow))
        {
            transform.Rotate(0, 0, -paddleRotateSpeed, Space.World);
            // Debug.Log("prawo");
        }

    }

    public void StartPosition()
    {
        transform.position = new Vector3(0, -0.8f, 0);
        transform.eulerAngles = new Vector3(0, 0, 0);
    }
}
