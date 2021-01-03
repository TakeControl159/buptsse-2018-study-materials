/**
  ******************************************************************************
  * File Name          : uCOSII_Demo.c
  * Description        : demo code for STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 jkuang@BUPT
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
//#include "main.h"
//#include "stm32f4xx_hal.h"
//#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include	"uCOSII_Demo.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

APP_RECORD App_Record[APP_RECORD_NUM];

//mem partition for message
char mempart1_buf[MEMPART_1_NBLK][MEMPART_1_BLKSIZE];
OS_MEM * mempart1_p;

#define STK_SIZE_DEF	128

//#define DEMO_01
	//DEMO_01: 2 Tasks timedelay Led demo
//#define DEMO_02
	//DEMO_02: 2 Tasks sem demo
#define DEMO_03
	//DEMO_03: Timer test demo

#ifdef DEMO_01
#define TASK1_PRIO    								11
#define TASK2_PRIO    								12

static OS_STK task1_stk[STK_SIZE_DEF];
static OS_STK task2_stk[STK_SIZE_DEF];

static void task1(void *p_arg);
static void task2(void *p_arg);
#endif //DEMO_01

#ifdef DEMO_02
#define TASK_SENDER_PRIO    					17
#define TASK_RECIVER_PRIO    					16

static OS_STK task_sender_stk[STK_SIZE_DEF];
static OS_STK task_reciver_stk[STK_SIZE_DEF];

static void task_sender(void *p_arg);
static void task_reciver(void *p_arg);

OS_EVENT *demo_semp;
#endif //DEMO_02

#ifdef DEMO_03
#define TASK_TMRTST_PRIO    					19
static OS_STK task_tmrtst_stk[STK_SIZE_DEF];
static void task_tmrtst(void *p_arg);
#endif //DEMO_03

//Board key switch Identification, value toggled while specified key pressed.
#define KEY_NUMBER		4	// 4 keys 
INT8U KeySwitch[KEY_NUMBER];

// Key Value
#define KEY_UP				1
#define KEY_DOWN			0

#define KEY1_READ 		HAL_GPIO_ReadPin(GPIOI,GPIO_PIN_9)    //PI9, key3 in Schematic
#define KEY2_READ 		HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_11)	  //PF11, key4 in Schematic 
#define KEY3_READ 		HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)   //PC13, key5 in Schematic
#define KEY4_READ			HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)	  //PA0, key6 in Schematic

#define TASK_KETSCAN_PRIO    					60
static OS_STK task_keyscan_stk[STK_SIZE_DEF];
static void task_keyscan(void *p_arg);

/* Private variables ---------------------------------------------------------*/



/* Private function prototypes -----------------------------------------------*/
INT32U USER_Get_OSIdleCtr(void);
void USER_Print_OSIdleCtr(void);
/* Private function prototypes -----------------------------------------------*/


int User_App_Initial(void)
{
	int i;
	INT8U err;

	// BEEP off
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_RESET );

	// 4 leds off
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7, GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET );

	// Key Switch Record initial
	for(i=0; i<KEY_NUMBER; i++)
	{
		KeySwitch[i] = 1;
	}
	
	// Task record array initial
	for(i=0; i<APP_RECORD_NUM; i++)
	{
		App_Record[i].tQid = 0;
		App_Record[i].tPrio = 0xFF;
	}
	#if OS_TMR_EN > 0u
	App_Record[OS_TID_Timer].tPrio = OS_TASK_TMR_PRIO;  //Timer task record init
	#endif

	//task USART1 Create
	Task_USART1_Creat();

	//mem partition Create
	mempart1_p = OSMemCreate((void*)mempart1_buf,MEMPART_1_NBLK,MEMPART_1_BLKSIZE,&err);
	if(err != OS_ERR_NONE)
	{
		return(0);
	}
//	USER_USART1_print("\n====Mem Partition 1 Created====\n");

#ifdef DEMO_01
	OSTaskCreate(task1,(void*)0,&task1_stk[STK_SIZE_DEF - 1],TASK1_PRIO);
  OSTaskCreate(task2,(void*)0,&task2_stk[STK_SIZE_DEF - 1],TASK2_PRIO);
#endif //DEMO_01

#ifdef DEMO_02
	demo_semp = OSSemCreate(0);
	
	OSTaskCreate(task_sender,(void*)0,&task_sender_stk[STK_SIZE_DEF - 1],TASK_SENDER_PRIO);
  OSTaskCreate(task_reciver,(void*)0,&task_reciver_stk[STK_SIZE_DEF - 1],TASK_RECIVER_PRIO);
#endif //DEMO_02

#ifdef DEMO_03
	err = OSTaskCreate(task_tmrtst,(void*)0,&task_tmrtst_stk[STK_SIZE_DEF - 1],TASK_TMRTST_PRIO);
	if( err == OS_ERR_NONE)
	{
		App_Record[APP_TID_tmrtest].tPrio = TASK_TMRTST_PRIO;
	}
#endif //DEMO_03

	//Creat Key scan task
	OSTaskCreate(	task_keyscan,(void*)0,
								&task_keyscan_stk[STK_SIZE_DEF - 1],TASK_KETSCAN_PRIO);

	return(0);
}

//============================================================
static char aStr[16];
void USER_Print_OSIdleCtr(void)
{
//	char aStr[16];

	sprintf((char*)aStr, "[%08X]", OSIdleCtr);
	USER_USART1_print(aStr);
}


#ifdef DEMO_01
//------------ DEMO 01 ----------------
//============================================================
static void task1(void *p_arg)
{
	USER_USART1_print("\n====Task1 Created====\n");

	while(1)  
	{	       
		USER_Print_OSIdleCtr();
		USER_USART1_print(":Task1\n");

		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);
		OSTimeDlyHMSM(0,0,0,400);

  }
}

//============================================================
static void task2(void *p_arg)
{
	USER_USART1_print("\n====Task2 Created====\n");

	while(1)
	{
		USER_Print_OSIdleCtr();
		USER_USART1_print(":Task2\n");

		HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);
		OSTimeDly(OS_TICKS_PER_SEC);
//		OSTimeDlyHMSM(0,0,0,1000);
    
    }
}
#endif //DEMO_01

#ifdef DEMO_02
//------------ DEMO 02 ----------------
//#define PRINT_EN_DEMO02

//============================================================
static void task_sender(void *p_arg)
{

	USER_USART1_print("\n====Task Sender Created====\n");

	while(1)  
	{	       
		if(KeySwitch[0])	//key1 switch
		{
			HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10); //toggle led1
		}
		OSSemPost(demo_semp);

#ifdef PRINT_EN_DEMO02
		USER_Print_OSIdleCtr();
		USER_USART1_print(":Task Sender\n");
#endif
		OSTimeDlyHMSM(0,0,0,400);

  }
}

//============================================================
static void task_reciver(void *p_arg)
{
	INT8U  err;
  GPIO_PinState bitstatus;
	
	USER_USART1_print("\n====Task Reciver Created====\n");

	while(1)
	{
		OSSemPend (demo_semp, 0, &err);

		if(KeySwitch[1])	//key2 switch
		{
			bitstatus = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10);
			if(bitstatus == GPIO_PIN_RESET) //led2 set reverse state of led1 
			{
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET );
			}else{
				HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET );
			}
		}
#ifdef PRINT_EN_DEMO02
		USER_Print_OSIdleCtr();
		USER_USART1_print(":Task Reciver\n");
#endif
	}
}
#endif //DEMO_02

#ifdef DEMO_03
//------------ DEMO 03 ----------------
#define PRINT_EN_DEMO03

static OS_TMR *MyTmr1; //µÚÒ»¸ö¼ÆÊ±Æ÷£¬¿ØÖÆµÚÒ»¸öµÆÂýÉÁ
static OS_TMR *MyTmr11; //µÚ¶þ¸ö¼ÆÊ±Æ÷£¬¿ØÖÆµÚÒ»¸öµÆ¿ìÉÁ
static OS_TMR *MyTmr2; //µÚÈý¸ö¼ÆÊ±Æ÷£¬¿ØÖÆµÚ¶þ¸öµÆÂýÉÁ
static OS_TMR *MyTmr22; //µÚËÄ¸ö¼ÆÊ±Æ÷£¬¿ØÖÆµÚ¶þ¸öµÆ¿ìÉÁ
static OS_TMR *MyTmr3;// µÚÎå¸ö¼ÆÊ±Æ÷£¬¿ØÖÆµÚÈý¸öµÆÂýÉÁ
static OS_TMR *MyTmr33;// µÚÁù¸ö¼ÆÊ±Æ÷£¬¿ØÖÆµÚÈý¸öµÆ¿ìÉÁ
static OS_TMR *MyTmr4;//timer
//msgQ of timer test task
#define TASK_TMRTST_QSIZE		10
static void *TaskTmrtst_Qarray[TASK_TMRTST_QSIZE];
//============================================================
static void MyTmrCallbackFnct1 (void *p_arg)
{
/* Do something when timer #1 expires */
	INT8U err;
	MESSAGE_HEAD *msgP;
//OSTmrStart(MyTmr1, &err);
	//OSTmrStart(MyTmr1, &err);  //restart timer

	//get msg buf & send msg to tmetst task Q
	msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
	if(msgP)
	{
		msgP->mCode = MC_TMRTST_TMR1;
		msgP->mSendTsk = OS_TID_Timer;
		msgP->mRecvTsk = APP_TID_tmrtest;
		if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
		{
			OSMemPut(mempart1_p,(void *)msgP);
		}
	}
	
}


static void MyTmrCallbackFnct11 (void *p_arg)
{

/* Do something when timer #11 expires */
	INT8U err;
	MESSAGE_HEAD *msgP;
//OSTmrStart(MyTmr1, &err);
	//OSTmrStart(MyTmr1, &err);  //restart timer

	//get msg buf & send msg to tmetst task Q
	msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
	if(msgP)
	{
		msgP->mCode = MC_TMRTST_TMR11;
		msgP->mSendTsk = OS_TID_Timer;
		msgP->mRecvTsk = APP_TID_tmrtest;
		if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
		{
			OSMemPut(mempart1_p,(void *)msgP);
		}
	}
	
}

//============================================================
static void MyTmrCallbackFnct2 (void *p_arg)
{
	
/* Do something when timer #2 expires */
INT8U err;
MESSAGE_HEAD *msgP;
//OSTmrStart(MyTmr2, &err);
//get msg buf & send msg to tmetst task Q
msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
if(msgP)
{
	msgP->mCode = MC_TMRTST_TMR2;
	msgP->mSendTsk = OS_TID_Timer;
	msgP->mRecvTsk = APP_TID_tmrtest;
	if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
	{
		OSMemPut(mempart1_p,(void *)msgP);
	}
}

}

static void MyTmrCallbackFnct22 (void *p_arg)
{
	
/* Do something when timer #22 expires */
INT8U err;
MESSAGE_HEAD *msgP;
//OSTmrStart(MyTmr2, &err);
//get msg buf & send msg to tmetst task Q
msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
if(msgP)
{
	msgP->mCode = MC_TMRTST_TMR22;
	msgP->mSendTsk = OS_TID_Timer;
	msgP->mRecvTsk = APP_TID_tmrtest;
	if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
	{
		OSMemPut(mempart1_p,(void *)msgP);
	}
}

}

//============================================================
static void MyTmrCallbackFnct3 (void *p_arg)
{
/* Do something when timer #3 expires */
	INT8U err;
	MESSAGE_HEAD *msgP;

	//OSTmrStart(MyTmr3, &err);  //restart timer

	//get msg buf & send msg to tmetst task Q
	msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
	if(msgP)
	{
		msgP->mCode = MC_TMRTST_TMR3;
		msgP->mSendTsk = OS_TID_Timer;
		msgP->mRecvTsk = APP_TID_tmrtest;
		if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
		{
			OSMemPut(mempart1_p,(void *)msgP);
		}
	}
	
}

static void MyTmrCallbackFnct33 (void *p_arg)
{
/* Do something when timer #33 expires */
	INT8U err;
	MESSAGE_HEAD *msgP;

	//OSTmrStart(MyTmr3, &err);  //restart timer

	//get msg buf & send msg to tmetst task Q
	msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
	if(msgP)
	{
		msgP->mCode = MC_TMRTST_TMR33;
		msgP->mSendTsk = OS_TID_Timer;
		msgP->mRecvTsk = APP_TID_tmrtest;
		if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
		{
			OSMemPut(mempart1_p,(void *)msgP);
		}
	}
	
}


//============================================================
static void MyTmrCallbackFnct4 (void *p_arg)
{
/* Do something when timer #1 expires */
	INT8U err;
	MESSAGE_HEAD *msgP;

	//OSTmrStart(MyTmr4, &err);  //restart timer

	//get msg buf & send msg to tmetst task Q
	msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
	if(msgP)
	{
		msgP->mCode = MC_TMRTST_TMR4;
		msgP->mSendTsk = OS_TID_Timer;
		msgP->mRecvTsk = APP_TID_tmrtest;
		if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
		{
			OSMemPut(mempart1_p,(void *)msgP);
		}
	}
	
}
//============================================================
static void task_tmrtst(void *p_arg)
{
	INT8U err;
	MESSAGE_HEAD *msgP;//ÏûÏ¢µÄÖ¸Õë
	INT8U	tmr_switch1 = 0;//´ú±íµÚÒ»¸ö°´¼ü£¬°´ÏÂµÄ´ÎÊý[0,3]£¬×î¿ªÊ¼Îª0£¬¼´Ï¨Ãð
	INT8U	tmr_switch2 = 0;//´ú±íµÚ¶þ¸ö°´¼ü£¬°´ÏÂµÄ´ÎÊý[0,3]£¬×î¿ªÊ¼Îª0£¬¼´Ï¨Ãð
	INT8U	tmr_switch3 = 0;//´ú±íµÚÈý¸ö°´¼ü£¬°´ÏÂµÄ´ÎÊý[0,3]£¬×î¿ªÊ¼Îª0£¬¼´Ï¨Ãð
	INT8U	tmr_switch4 = 0;//·äÃùÆ÷
	INT8U beep_on = 1;

	
	//Create ÏûÏ¢¶ÓÁÐ of timer test task
	App_Record[APP_TID_tmrtest].tQid = 
							OSQCreate(&TaskTmrtst_Qarray[0], TASK_TMRTST_QSIZE);
	if(App_Record[APP_TID_tmrtest].tQid == NULL)
	{
		App_Record[APP_TID_tmrtest].tPrio = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}

	//timer create
	//´´½¨µÚÒ»¸ö¼ÆÊ±Æ÷
	MyTmr1 = OSTmrCreate(	(INT32U )0,
												(INT32U )5,//ÂýÉÁÆµÂÊ
												(INT8U )OS_TMR_OPT_PERIODIC,
												(OS_TMR_CALLBACK)MyTmrCallbackFnct1,
												(void *)0,
												(INT8U *)"MyTmr1",
												(INT8U *)&err);
	if(err != OS_ERR_NONE)
	{
		OSTmrDel(MyTmr1,&err);
		OSQDel(App_Record[APP_TID_tmrtest].tQid,OS_DEL_ALWAYS,&err);
		App_Record[APP_TID_tmrtest].tQid = NULL;
		App_Record[APP_TID_tmrtest].tPrio = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	//´´½¨µÚ¶þ¸ö¼ÆÊ±Æ÷
	MyTmr11 = OSTmrCreate(	(INT32U )0,
												(INT32U )1,//¿ìÉÁÆµÂÊ
												(INT8U )OS_TMR_OPT_PERIODIC,
												(OS_TMR_CALLBACK)MyTmrCallbackFnct11,
												(void *)0,
												(INT8U *)"MyTmr11",
												(INT8U *)&err);
	if(err != OS_ERR_NONE)
	{
		OSTmrDel(MyTmr11,&err);
		OSQDel(App_Record[APP_TID_tmrtest].tQid,OS_DEL_ALWAYS,&err);
		App_Record[APP_TID_tmrtest].tQid = NULL;
		App_Record[APP_TID_tmrtest].tPrio = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	//´´½¨µÚÈý¸ö¼ÆÊ±Æ÷
	MyTmr2 = OSTmrCreate(	(INT32U )0,
												(INT32U )5,//ÂýÉÁÆµÂÊ
												(INT8U )OS_TMR_OPT_PERIODIC,
												(OS_TMR_CALLBACK)MyTmrCallbackFnct2,
												(void *)0,
												(INT8U *)"MyTmr2",
												(INT8U *)&err);
	if(err != OS_ERR_NONE)
	{
		OSTmrDel(MyTmr2,&err);
		OSQDel(App_Record[APP_TID_tmrtest].tQid,OS_DEL_ALWAYS,&err);
		App_Record[APP_TID_tmrtest].tQid = NULL;
		App_Record[APP_TID_tmrtest].tPrio = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	//´´½¨µÚËÄ¸ö¼ÆÊ±Æ÷
	MyTmr22 = OSTmrCreate(	(INT32U )0,
												(INT32U )1,//¿ìÉÁÆµÂÊ
												(INT8U )OS_TMR_OPT_PERIODIC,
												(OS_TMR_CALLBACK)MyTmrCallbackFnct22,
												(void *)0,
												(INT8U *)"MyTmr22",
												(INT8U *)&err);
	if(err != OS_ERR_NONE)
	{
		OSTmrDel(MyTmr22,&err);
		OSQDel(App_Record[APP_TID_tmrtest].tQid,OS_DEL_ALWAYS,&err);
		App_Record[APP_TID_tmrtest].tQid = NULL;
		App_Record[APP_TID_tmrtest].tPrio = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	//´´½¨µÚÎå¸ö¼ÆÊ±Æ÷
	MyTmr3 = OSTmrCreate(	(INT32U )0,
												(INT32U )5,//ÂýÉÁÆµÂÊ
												(INT8U )OS_TMR_OPT_PERIODIC,
												(OS_TMR_CALLBACK)MyTmrCallbackFnct3,
												(void *)0,
												(INT8U *)"MyTmr3",
												(INT8U *)&err);
	if(err != OS_ERR_NONE)
	{
		OSTmrDel(MyTmr3,&err);
		OSQDel(App_Record[APP_TID_tmrtest].tQid,OS_DEL_ALWAYS,&err);
		App_Record[APP_TID_tmrtest].tQid = NULL;
		App_Record[APP_TID_tmrtest].tPrio = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	//´´½¨µÚÁù¸ö¼ÆÊ±Æ÷
	MyTmr33 = OSTmrCreate(	(INT32U )0,
												(INT32U )1,//¿ìÉÁÆµÂÊ
												(INT8U )OS_TMR_OPT_PERIODIC,
												(OS_TMR_CALLBACK)MyTmrCallbackFnct33,
												(void *)0,
												(INT8U *)"MyTmr33",
												(INT8U *)&err);
	if(err != OS_ERR_NONE)
	{
		OSTmrDel(MyTmr33,&err);
		OSQDel(App_Record[APP_TID_tmrtest].tQid,OS_DEL_ALWAYS,&err);
		App_Record[APP_TID_tmrtest].tQid = NULL;
		App_Record[APP_TID_tmrtest].tPrio = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}
	
	MyTmr4 = OSTmrCreate(	(INT32U )4,
												(INT32U )5,
												(INT8U )OS_TMR_OPT_PERIODIC,
												(OS_TMR_CALLBACK)MyTmrCallbackFnct4,
												(void *)0,
												(INT8U *)"MyTmr4",
												(INT8U *)&err);
	if(err != OS_ERR_NONE)
	{
		OSTmrDel(MyTmr4,&err);
		OSQDel(App_Record[APP_TID_tmrtest].tQid,OS_DEL_ALWAYS,&err);
		App_Record[APP_TID_tmrtest].tQid = NULL;
		App_Record[APP_TID_tmrtest].tPrio = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}

	OSTmrStart(MyTmr4, &err);
	USER_USART1_print("\n====Task Timer Test Initialized====\n");
	while(1)  
	{	
		msgP = (MESSAGE_HEAD *)OSQPend(App_Record[APP_TID_tmrtest].tQid,0,&err);

		// message legality check
		if(msgP->mRecvTsk != APP_TID_tmrtest)
		{
			OSMemPut(mempart1_p,(void *)msgP);
			continue;
		}

		// message process by mCode
		switch(msgP->mCode)
		{
			case MC_KEY1_SWITCH://°´key1
				tmr_switch1 = (tmr_switch1+1)%4;//Ð¡µÆ4¸ö×´Ì¬£¬Í¨¹ýÄ£4ÔËËãÊµÏÖ¡
				if(tmr_switch1==0)
				{
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET); //Ð¡µÆÃð
				}
				if(tmr_switch1==1)
				{
					OSTmrStart(MyTmr1, &err);//ÂýÉÁ
				}
				if(tmr_switch1==2)
				{
					OSTmrStop(MyTmr1,OS_TMR_OPT_NONE,NULL,&err);//¹ØµôÇ°Ò»¸ö¼ÆÊ±Æ÷
					OSTmrStart(MyTmr11, &err);//¿ªÆôÐÂ¼ÆÊ±Æ÷
				}
				if(tmr_switch1==3)
				{
					OSTmrStop(MyTmr11,OS_TMR_OPT_NONE,NULL,&err);//¹Ø±Õ¼ÆÊ±Æ÷
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET); //³£ÁÁ
				}
				break;
			
			case MC_KEY2_SWITCH://°´key2
				tmr_switch2 = (tmr_switch2+1)%4;//Ð¡µÆ4¸ö×´Ì¬£¬Í¨¹ýÄ£4ÔËËãÊµÏÖ
				if(tmr_switch2==0)
				{
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET); //Ð¡µÆÃð
				}
				if(tmr_switch2==1)
				{
					OSTmrStart(MyTmr2, &err);//ÂýÉÁ
				}
				if(tmr_switch2==2)
				{
					OSTmrStop(MyTmr2,OS_TMR_OPT_NONE,NULL,&err);//¹ØµôÇ°Ò»¸ö¼ÆÊ±Æ÷
					OSTmrStart(MyTmr22, &err);//¿ªÆôÐÂ¼ÆÊ±Æ÷
				}
				if(tmr_switch2==3)
				{
					OSTmrStop(MyTmr22,OS_TMR_OPT_NONE,NULL,&err);//¹Ø±Õ¼ÆÊ±Æ÷
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET); //³£ÁÁ
				}
				break;
			
			case MC_KEY3_SWITCH:
				tmr_switch3 = (tmr_switch3+1)%4;//Ð¡µÆ4¸ö×´Ì¬£¬Í¨¹ýÄ£4ÔËËãÊµÏÖ
				if(tmr_switch3==0)
				{
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET); //Ð¡µÆÃð
				}
				if(tmr_switch3==1)
				{
					OSTmrStart(MyTmr3, &err);//ÂýÉÁ
				}
				if(tmr_switch3==2)
				{
					OSTmrStop(MyTmr3,OS_TMR_OPT_NONE,NULL,&err);//¹Ø±Õ¼ÆÊ±Æ÷
					OSTmrStart(MyTmr33, &err);//¿ìÉÁ
				}
				if(tmr_switch3==3)
				{
					OSTmrStop(MyTmr33,OS_TMR_OPT_NONE,NULL,&err);//¹Ø±Õ¼ÆÊ±Æ÷
					HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);  //³£ÁÁ
				}
				break;

			case MC_KEY4_SWITCH://°´ÏÂkey4
				beep_on ^= 1;
				if(beep_on == 0)
					HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_RESET); //Beep off
				break;

			case MC_TMRTST_TMR1://¼ÆÊ±Æ÷1Ê±¼äµ½£¬½øÐÐÁÁ°µÇÐ»»
	
					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);	//toggle led3
					if(beep_on)
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);	//Toggle Beep

				break;
				
			case MC_TMRTST_TMR11://¼ÆÊ±Æ÷2Ê±¼äµ½£¬½øÐÐÁÁ°µÇÐ»»
	
					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);	//toggle led3
					if(beep_on)
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);	//Toggle Beep

				break;

			case MC_TMRTST_TMR2://¼ÆÊ±Æ÷3Ê±¼äµ½£¬½øÐÐÁÁ°µÇÐ»»
				
					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);	//toggle led3
					if(beep_on)
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);	//Toggle Beep

				break;
					
			case MC_TMRTST_TMR22://¼ÆÊ±Æ÷4Ê±¼äµ½£¬½øÐÐÁÁ°µÇÐ»»
				
					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9);	//toggle led3
					if(beep_on)
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);	//Toggle Beep

				break;
					
			case MC_TMRTST_TMR3://¼ÆÊ±Æ÷5Ê±¼äµ½£¬½øÐÐÁÁ°µÇÐ»»
			
					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8);	//toggle led3
					if(beep_on)
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);	//Toggle Beep
		
				break;
					
			case MC_TMRTST_TMR33://¼ÆÊ±Æ÷6Ê±¼äµ½£¬½øÐÐÁÁ°µÇÐ»»
			
					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8);	//toggle led3
					if(beep_on)
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);	//Toggle Beep
		
				break;
					
			case MC_TMRTST_TMR4://¼ÆÊ±Æ÷Ê±¼äµ½£¬·äÃùÆ÷µÄ×´Ì¬ÇÐ»»//	if(tmr_switch)
			//	{
					HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7);	//toggle led3
					if(beep_on)
						HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6);	//Toggle Beep
			//	}
				break;
					
			default:
				break;
		}
		//release msg buf
		OSMemPut(mempart1_p,(void *)msgP);
		msgP = NULL;

#ifdef PRINT_EN_DEMO03
		USER_Print_OSIdleCtr();
		USER_USART1_print(":Task Timer Test\n");
#endif
  }
}

#endif //DEMO_03

//--------------Key Scan Task--------------------
#define PRINT_EN_KEYSCAN
//============================================================
static void task_keyscan(void *p_arg)
{
	INT8U err;
	MESSAGE_HEAD *msgP;
	INT8U keyscan[KEY_NUMBER]; //'0': key down already, scan halt; '1': key scan enable

	USER_USART1_print("\n====Task KeyScan Created====\n");

	while(1)  
	{	       
		// enable scan while key up
		if(KEY1_READ == KEY_UP)
			keyscan[0] = 1;
		if(KEY2_READ == KEY_UP)
			keyscan[1] = 1;
		if(KEY3_READ == KEY_UP)
			keyscan[2] = 1;
		if(KEY4_READ == KEY_UP)
			keyscan[3] = 1;

		// key down process
		if(	(keyscan[0]&&(KEY1_READ==KEY_DOWN))||
			 	(keyscan[1]&&(KEY2_READ==KEY_DOWN))||
				(keyscan[2]&&(KEY3_READ==KEY_DOWN))||
				(keyscan[3]&&(KEY4_READ==KEY_DOWN)))
		{
			OSTimeDly(OS_TICKS_PER_SEC/10); // È¥¶¶¶¯

			// key 1 down process
			if(KEY1_READ==KEY_DOWN) 
			{
				keyscan[0] = 0;			// key down already
				KeySwitch[0] ^= 1;	// key switch (global Variable)
				msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
				if(msgP)
				{
					msgP->mCode = MC_KEY1_SWITCH;
					msgP->mSendTsk = APP_TID_keyscan;
					msgP->mRecvTsk = APP_TID_tmrtest;
					if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
					{
						OSMemPut(mempart1_p,(void *)msgP);
					}
				}
				
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 1\n");
#endif
			}

			// key 2 down process
			if(KEY2_READ==KEY_DOWN) 
			{
				keyscan[1] = 0;
				KeySwitch[1] ^= 1;
				msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
				if(msgP)
				{
					msgP->mCode = MC_KEY2_SWITCH;
					msgP->mSendTsk = APP_TID_keyscan;
					msgP->mRecvTsk = APP_TID_tmrtest;
					if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
					{
						OSMemPut(mempart1_p,(void *)msgP);
					}
				}
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 2\n");
#endif
			}

			// key 3 down process
			if(KEY3_READ==KEY_DOWN) 
			{
				keyscan[2] = 0;
				KeySwitch[2] ^= 1;

				//get msg buf & send msg to tmetst task Q
				msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
				if(msgP)
				{
					msgP->mCode = MC_KEY3_SWITCH;
					msgP->mSendTsk = APP_TID_keyscan;
					msgP->mRecvTsk = APP_TID_tmrtest;
					if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
					{
						OSMemPut(mempart1_p,(void *)msgP);
					}
				}
				
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 3\n");
#endif
			}

			// key 4 down process
			if(KEY4_READ==KEY_DOWN) 
			{
				keyscan[3] = 0;
				KeySwitch[3] ^= 1;
msgP = (MESSAGE_HEAD*)OSMemGet(mempart1_p,&err);
				//get msg buf & send msg to tmetst task Q
				if(msgP)
				{
					msgP->mCode = MC_KEY4_SWITCH;
					msgP->mSendTsk = APP_TID_keyscan;
					msgP->mRecvTsk = APP_TID_tmrtest;
					if(OSQPost(App_Record[APP_TID_tmrtest].tQid,(void *)msgP))
					{
						OSMemPut(mempart1_p,(void *)msgP);
					}
				}
				
#ifdef PRINT_EN_KEYSCAN
				USER_USART1_print("Key 4\n");
#endif
			}
		}
		else
		{
			OSTimeDly(OS_TICKS_PER_SEC/10);	// task delay
		}
  }
}



/************************ (C) COPYRIGHT jkuang@BUPT *****END OF FILE****/
