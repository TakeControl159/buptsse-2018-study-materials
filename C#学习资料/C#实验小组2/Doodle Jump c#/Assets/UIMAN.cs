using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIMAN : MonoBehaviour
{

    public int velocity = 100;

    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    void OnCollisionStay2D(Collision2D other)
    {
        if(other.gameObject.CompareTag("Ground"))
        {
            OnJump();
        }
    
    }

    void OnJump()
    {
        transform.GetComponent<Rigidbody2D>().AddForce(Vector2.up * velocity);
    }

}


