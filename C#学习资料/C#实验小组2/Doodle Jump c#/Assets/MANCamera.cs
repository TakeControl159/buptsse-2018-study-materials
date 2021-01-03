using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MANCamera : MonoBehaviour {

    GameObject Eyes, Man;
    Vector2 CameraPos, ManPos;
    public int velocity = 1;
   

	// Use this for initialization
	void Start () {
        Eyes = GameObject.Find("Eyes");
        Man = GameObject.Find("Man");
	}
	
	// Update is called once per frame
	void Update () {
        CameraPos = Eyes.transform.position;
        ManPos = Man.transform.position;
        if(ManPos.y>CameraPos.y)
        {
            Eyes.transform.position = Vector2.MoveTowards(CameraPos, new Vector2(CameraPos.x, ManPos.y),velocity);
        }
	}
}
