using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MANUP : MonoBehaviour {

    public bool Ground = false,IsHit=false;
    public int Velocity = 400, LRVelocity = 10;
    private GameObject foot = null;
    Rigidbody2D GetR;
    BoxCollider2D GetB;
    void Start()
    {
        GetR = transform.GetComponent<Rigidbody2D>();
        GetB = transform.GetComponent<BoxCollider2D>();
    }


    void Update()
    {   
        if(transform.position.x > 2.8f)
        {
            transform.position = new Vector2(-2.8f, transform.position.y);
        }
        if(transform.position.x < -2.8f)
        {
            transform.position = new Vector2(2.8f, transform.position.y);
        }

        if (Ground)
        {
            GetR.AddForce(Vector2.up*Velocity);
            Ground = false;
        }
        if (GetR.velocity.y > 0)
        {
            GetB.isTrigger = true;
        }
        else
        {
			if(IsHit==false)
            	GetB.isTrigger = false;
        }
        if (Input.GetKey(KeyCode.A))
        {
            GetR.AddForce(Vector2.left * LRVelocity);
            transform.rotation = new Quaternion(0, 180, 0, 0);
        }
        if (Input.GetKey(KeyCode.D))
        {
            GetR.AddForce(Vector2.right * LRVelocity);
            transform.rotation = new Quaternion(0, 0, 0, 0);
        }
    }
    void OnCollisionStay2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Floor"))
        {
            GetR.velocity = new Vector2(GetR.velocity.x, 0);
            Ground = true;
        }
    }
    void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Floor") && !other.gameObject.Equals(foot))
        {
            foot = other.gameObject;
            transform.GetComponent<Map>().OnGround();
            transform.GetComponent<Map>().OnGround();

        }
        
        transform.GetComponent<MANAnime>().OnAni();
    }
    void OnTriggerEnter2D(Collider2D other)
    {
		IsHit = true;
		if (other.gameObject.CompareTag ("Up")) {
			other.gameObject.GetComponent<Animator> ().SetTrigger ("HitUp");
			GetR.AddForce(Vector2.up * Velocity*3/2);
			Destroy (other.gameObject);
		}
		if (other.gameObject.CompareTag("Die"))
        {
            print("die");
        }
    }
	void OnTriggerExit2D(Collider2D other){
		IsHit = false;
	}
}
