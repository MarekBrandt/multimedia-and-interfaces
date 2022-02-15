using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class GameController : MonoBehaviour
{
    public BallScript bs;
    public PaddleControler pc;
    public Text TextLives;
    public Text TextScore;

    public bool stopped;

    public void Reset()
    {
        stopped = true;
        bs.StartPosition();
        pc.StartPosition();
    }
    // Start is called before the first frame update
    void Start()
    {
        Reset();
        SetTexts();
    }

    // Update is called once per frame
    void Update()
    {
        SetTexts();
        if(stopped && bs.lives>0 && Input.GetKey(KeyCode.Space))
        {
            stopped = false;
            bs.GetComponent<Rigidbody>().AddRelativeForce(0, -400, 0);
        }
    }

    void SetTexts()
    {
        TextLives.text = "Lives: \n"+bs.lives;
        TextScore.text = "Score: \n"+bs.score;
       // Debug.Log("Called");
    }
}
