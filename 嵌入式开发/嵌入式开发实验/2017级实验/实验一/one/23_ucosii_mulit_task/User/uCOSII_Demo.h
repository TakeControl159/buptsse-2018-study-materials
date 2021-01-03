/**
  ******************************************************************************
  * File Name          : uCOSII_Demo.h
  * Description        : demo code for STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 jkuang@BUPT
  *
  ******************************************************************************
  */
#ifndef UCOSII_DEMO_H
#define UCOSII_DEMO_H
#ifdef __cplusplus
		 extern "C" {
#endif

#include  "ucos_ii.h"
#include 	"usart_it.h"
#include  "message.h"

//===================================================================
//app task record 
typedef struct _APP_RECORD
{
	OS_EVENT*	tQid;			// task Q ID
	INT16U    tPrio;		// task priority
	INT16U		tRes;			// reserved
} APP_RECORD;

#define APP_RECORD_NUM	OS_MAX_TASKS	//Max. number of tasks supported

extern APP_RECORD App_Record[APP_RECORD_NUM];

#define DRV_ID_usart1			-1

#define OS_TID_Timer			0		// OS Timer task id use '0'

#define APP_TID_usart1		1
#define APP_TID_keyscan		2
#define APP_TID_sender		3
#define APP_TID_receiver	4
#define APP_TID_tmrtest		5


//===================================================================
//mem partition for message
#define MEMPART_1_NBLK		10
#define MEMPART_1_BLKSIZE	16
extern char mempart1_buf[MEMPART_1_NBLK][MEMPART_1_BLKSIZE];
extern OS_MEM * mempart1_p;



//===================================================================
// prototypes
int User_App_Initial(void);


#ifdef __cplusplus
}
#endif
#endif /* UCOSII_DEMO_H */

/************************ (C) COPYRIGHT jkuang@BUPT *****END OF FILE****/
