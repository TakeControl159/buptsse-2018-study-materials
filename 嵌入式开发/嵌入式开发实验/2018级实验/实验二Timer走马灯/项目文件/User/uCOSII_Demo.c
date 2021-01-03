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


/* USER CODE BEGIN Includes */
#include	"farsight_f407.h"
#include	"uCOSII_Demo.h"
#include <stdbool.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

APP_RECORD App_Record[APP_RECORD_NUM];

//DEMO_01: 2 Tasks timedelay Led demo
//#define DEMO_01
//DEMO_02: 2 Tasks sem demo
#define DEMO_03

// ÊµÀdemoÑÝÊ¾ý****************************
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


//*********************** demo3 Timer×ßÂíµÆÊµÑé(º¯ÊýÉùÃ÷) **************************
#ifdef DEMO_03
// ´Ëº¯ÊýÓÃÓÚ¼ì²â4¸ö°´¼üÊÇ·ñ°´ÏÂ, ¼ì²âÖ®ºóÖ´ÐÐÏàÓ¦²Ù×÷
static void led_light(void *p_arg);

// ´Ëº¯ÊýÓÃÓÚÓÃÓÚµãÁÁ²»Í¬µÄLEDµÆ
static void Turn_On_LED(uint8_t LED_NUM);

// timerÖ¸Õë, ÓÃÓÚÐÞ¸ÄtimerµÄÑ­»·ÖÜÆÚ
OS_TMR  *LEDTimer;
#endif //DEMO_03


//============================================================
int User_App_Initial(void)
{
	int 	i;
	INT8U err;

	//BEEP off
	BEEP_OFF;
	
	//4 leds off
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	LED4_OFF;


	//Task record array initial
	for(i=0; i<APP_RECORD_NUM; i++)
	{
		App_Record[i].tQid = 0;
		App_Record[i].tPrio = 0xFF;
	}

#if OS_TMR_EN > 0u
	App_Record[OS_TID_Timer].tPrio = OS_TASK_TMR_PRIO;  //Timer task record init
#endif

	//UART Send buffer init
	Uart_Sendbuf_Init();

	//task USART1 Create
	err = Task_USART1_Creat();
	if(err)
		return(err);
	
	//task KeyScan Create
	err = Task_KeyScan_Creat();
	if(err)
		return(err);

#ifdef DEMO_01
	OSTaskCreate(task1, (void*)0, &task1_stk[STK_SIZE_DEF-1], TASK1_PRIO);
	OSTaskCreate(task2, (void*)0, &task2_stk[STK_SIZE_DEF-1], TASK2_PRIO);
#endif //DEMO_01

#ifdef DEMO_02
	demo_semp = OSSemCreate(0);
	if(demo_semp == 0)
		return(255);
	
	err = OSTaskCreate(task_sender, (void*)0, &task_sender_stk[STK_SIZE_DEF-1], TASK_SENDER_PRIO);
	if(err)
		return(err);

  err = OSTaskCreate(task_reciver, (void*)0, &task_reciver_stk[STK_SIZE_DEF-1], TASK_RECIVER_PRIO);
	if(err)
		return(err);
#endif //DEMO_02
	
	
//*********************** Ñ­»·ÔËÐÐ demo3 ÖÐµÄled_lightº¯Êý***************
#ifdef DEMO_03
	LEDTimer = OSTmrCreate(	(INT32U )10,
													(INT32U )20,
													(INT8U )OS_TMR_OPT_PERIODIC,
													(OS_TMR_CALLBACK)led_light,
													(void *)0,
													 NULL,
													(INT8U *)&err);
	OSTmrStart(LEDTimer, &err);

#endif
	

	return(0);
}

//============================================================
void USER_Print_Decimal(INT32U value)
{
	char* aStr;

	aStr = Uart_Sendbuf_Get();

	sprintf((char*)aStr, "%d", value);
	USER_USART1_print(aStr);
}

//============================================================
//static char aStr[16];
void USER_Print_OSIdleCtr(void)
{
//	static char aStr[16];	//×¢Òâ£ºÁÙ½ç×ÊÔ´£¡
	char* aStr;

	aStr = Uart_Sendbuf_Get();

	sprintf((char*)aStr, "[%08X]", OSIdleCtr);
	USER_USART1_print(aStr);
}


// *************** ¶¨Òådemo_03×ßÂíµÆÊµÑéÖ÷Òªº¯Êý***************
#ifdef DEMO_03

// ×ßÂíµÆÁ÷¶¯·½Ïò
bool direction = true;
// ¼ÆÊýÆ÷,ÓÃÓÚ±ê¼ÇµãÁÁÄÇÒ»ÕµLEDµÆ
int count = 0;
// ¼ÇÂ¼ËÄ¸ö°´¼üµÄÖµ,ÓÃÓÚÅÐ¶Ï°´¼üÊÇ·ñ°´ÏÂ
int key1_value = 1;
int key2_value = 1;
int key3_value = 1;
int key4_value = 1;

// µãÁÁLED
static void Turn_On_LED(uint8_t LED_NUM)
{
		switch(LED_NUM)
	{
        case 0:    
					LED1_ON;  /*µãÁÁ1µÆ*/
          break;
        case 1:
		      LED2_ON;  /*µãÁÁ2µÆ*/
          break;
        case 2:
					LED3_ON;  /*µãÁÁ3µÆ*/
          break;
        case 3:
					LED4_ON;  /*µãÁÁ4µÆ*/
          break;          
        default:
          break;
	}
}

// Ö÷¿Øº¯Êý
static void led_light(void *p_arg)
{
		// ¹Ø±ÕËùÓÐµÄLEDµÆ
		LED1_OFF;
		LED2_OFF;
		LED3_OFF;
		LED4_OFF;
	
		// ¸ù¾ÝcountÈ¡Öµ,µãÁÁ¶ÔÓ¦µÄledµÆ
		Turn_On_LED(count%4);
	
		// ÅÐ¶ÏÄÇ¸ö°´¼ü±»°´ÏÂ
		// Èç¹ûKEY1~3±»°´ÏÂ, Ôò¸Ä±ätimerÖÜÆÚ
		// Èç¹ûKEY4±»°´ÏÂ,Ôò¸Ä±äledµÆÁ÷¶¯·½Ïò
		if(key1_value != KEYSWITCH(1))	
		{
			key1_value = KEYSWITCH(1);
			LEDTimer->OSTmrPeriod = 3;
		}else if(key2_value != KEYSWITCH(2))
		{
			key2_value = KEYSWITCH(2);
			LEDTimer->OSTmrPeriod = 7;
		}else if(key3_value != KEYSWITCH(3))
		{
			key3_value = KEYSWITCH(3);
			LEDTimer->OSTmrPeriod = 12;
		}else if(key4_value != KEYSWITCH(4))
		{
			key4_value = KEYSWITCH(4);
			direction = !direction;
		}
		
		//ÅÐ¶Ï×ßÂíµÆµÄ·½Ïò
		if(direction)
		{
			count++;  //¼ÆÊýÆ÷×ÔÔö,1,2,3,4ºÅLEDµÆÒÀ´ÎµãÁÁ
		}
		else
		{
			count--;
			if(count < 1)
			{
				count = 4;//¼ÆÊýÆ÷×Ô¼õ,4,3,2,1ºÅLEDµÆÒÀ´ÎµãÁÁ
			}
		}
}


// *************** ¶¨Òådemo_03×ßÂíµÆÊµÑéÖ÷Òªº¯Êý½áÊø***************
#endif //DEMO_03

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

		LED1_TOGGLE;
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

		LED2_TOGGLE;
		BEEP_TOGGLE;
		OSTimeDly(OS_TICKS_PER_SEC);
//		OSTimeDlyHMSM(0,0,0,1000);
    
   }
}
#endif //DEMO_01

#ifdef DEMO_02
//------------ DEMO 02 ----------------
#define PRINT_EN_DEMO02

//============================================================
static void task_sender(void *p_arg)
{
	INT32U task_active_cnt = 0;

	App_Record[APP_TID_sender].tPrio = TASK_SENDER_PRIO;

	USER_USART1_print("\n====Task Sender Created====\n");

	while(1)  
	{	       
		if(KEYSWITCH(1))	//key1 switch
		{
			LED1_TOGGLE;
		}
		if(OSSemPost(demo_semp))
			USER_USART1_print("Task Sender SEM-POST ERR!\n");

#ifdef PRINT_EN_DEMO02
		USER_Print_OSIdleCtr();
		task_active_cnt++;
		USER_USART1_print(" Task Sender active:");
		USER_Print_Decimal(task_active_cnt);
		USER_USART1_print("\n");
#endif
		OSTimeDlyHMSM(0,0,0,400);

  }
}

//============================================================
static void task_reciver(void *p_arg)
{
	INT8U  				err;
  GPIO_PinState bitstatus;
	INT32U 				task_active_cnt = 0;

	
	App_Record[APP_TID_receiver].tPrio = TASK_RECIVER_PRIO;

	USER_USART1_print("\n====Task Reciver Created====\n");

	while(1)
	{
		OSSemPend (demo_semp, 0, &err);
		if(err)
			USER_USART1_print("Task Reciver SEM-PEND ERR!\n");

		if(KEYSWITCH(2))	//key2 switch
		{
			bitstatus = LED1_READ;
			if(bitstatus == GPIO_PIN_RESET) //led2 set reverse state of led1 
			{
				LED2_OFF;
			}else{
				LED2_ON;
			}
			if(KEYSWITCH(4))	//key4 switch
			{
				BEEP_TOGGLE;
			}
		}
#ifdef PRINT_EN_DEMO02
		USER_Print_OSIdleCtr();
		task_active_cnt++;
		USER_USART1_print(" Task Reciver active:");
		USER_Print_Decimal(task_active_cnt);
		USER_USART1_print("\n");
#endif
	}
}
#endif //DEMO_02




/************************ (C) COPYRIGHT jkuang@BUPT *****END OF FILE****/
