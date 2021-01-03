using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Blue : MonoBehaviour {

	public int Velocity=1;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if (transform.position.x > 2.6f) {
			if (Velocity > 0) {
				Velocity = -Velocity;
			}
		}
		if (transform.position.x < -2.6f) {
			if (Velocity < 0) {
				Velocity = -Velocity;
			}
		}
		transform.Translate (Velocity * Time.deltaTime, 0, 0);
	}
}
