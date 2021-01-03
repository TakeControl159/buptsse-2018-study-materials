using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MANAnime : MonoBehaviour
{

    Animator Ani;

    // Use this for initialization
    void Start()
    {
        Ani = transform.GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void OnAni()
    {
        Ani.SetTrigger("Hit");
    }
}
