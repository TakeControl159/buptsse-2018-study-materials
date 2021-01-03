 using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Map : MonoBehaviour {

    public GameObject Ground,BlueGround,GroundUp;
	public int i=1;
    GameObject Top;
	GameObject Target,Man;

	// Use this for initialization
	void Start () {
        Top = GameObject.Find("GroundTop");
		Man = GameObject.Find ("Man");
	}
	
	// Update is called once per frame
	void Update () {
		if (Man.transform.position.y > Top.transform.position.y) {
			OnGround ();
		}
	}

    public void OnGround()
    {
		i=Random.Range (1,100);//1 ~ 9
		if (i<=2) {
			Target = GroundUp;
		} else if (i >=90) {
			Target = BlueGround;
		}
		else {
			Target = Ground;
		}
		GameObject Groundins = Instantiate(Target) as GameObject;
        Groundins.transform.position = new Vector3(Random.Range(-2.3f, 2.3f), Top.transform.position.y + Random.Range(0.7f, 1.5f), 0);
        Top = Groundins;    
    }
}
