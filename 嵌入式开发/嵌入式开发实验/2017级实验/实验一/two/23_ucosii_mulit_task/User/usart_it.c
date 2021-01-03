/**
  ******************************************************************************
  * File Name          : usart_it.c
  * Description        : USATR driver code for STM32F407 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 jkuang@BUPT
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "usart.h"
//#include "gpio.h"

//#include  "ucos_ii.h"
#include 	"string.h"
#include 	"uCOSII_Demo.h"

/* variables ---------------------------------------------------------*/

//USART1 Task
#define  TASK_USART1_PRIO               5
#define  TASK_USART1_STK_SIZE           128
OS_STK Task_USART1_Stk[TASK_USART1_STK_SIZE];

//msgQ of USART1
#define TASK_USART1_QSIZE		10
void *TaskUsart1_Qarray[TASK_USART1_QSIZE];

//Rx message buffer of USART1
#define UART1_RXMSGBUF_NUM			2
static UART_RX_MSG uart1_rxmsgbuf[UART1_RXMSGBUF_NUM];
static INT8U Rxmsg_idx;

//sendbuf Q of USART1
static OS_EVENT* SendBufQid = NULL;			// sendbuf Q ID
static char *SendbufP;
#define SENDBUF_USART1_QSIZE		15
void *SendBuf_QArray[SENDBUF_USART1_QSIZE];
/* variables ---------------------------------------------------------*/


//============================================================
static void USER_USART1_send(char *pData)
{
	while(*pData)
	{
		while(READ_BIT(huart1.Instance->SR, UART_FLAG_TXE) == RESET);

		huart1.Instance->DR = (uint8_t)*pData;
		pData++;
	}
}

//============================================================
void USER_USART1_print(char *pData)
{

	if((pData == NULL)||(*pData == 0))
		return;

	if(SendBufQid)
	{
		if(OSQPost(SendBufQid,(void *)pData) == OS_ERR_NONE)
		{
			SET_BIT(huart1.Instance->CR1, USART_CR1_TXEIE); //TXEIE int enable
		}
	}
	else
	{
		USER_USART1_send(pData); // print to HW directly
#ifdef HAL
    uint16_t len = 0;
		char *p = pData;
		while((*p)&&(len<=256)) 
		{
				len++; 
				p++;
		}
		HAL_UART_Transmit(&huart1, (uint8_t*)pData, len, 100);
#endif
	} 

}

//============================================================
//task USART1 Create
void Task_USART1_Creat(void)
{
	INT8U err;

	err = OSTaskCreate( task_USART1,(void*)0,
							&Task_USART1_Stk[TASK_USART1_STK_SIZE- 1],TASK_USART1_PRIO);
	if( err == OS_ERR_NONE)
	{
		App_Record[APP_TID_usart1].tPrio = TASK_USART1_PRIO;
	}
}

//============================================================
#define USART1_ECHO_TEST
static void task_USART1 (void* p_arg)
{
	INT8U err;
	char c;
	UART_RX_MSG *pmsg;


	//Rx message buffer initial
	{
		for(Rxmsg_idx=0; Rxmsg_idx<UART1_RXMSGBUF_NUM; Rxmsg_idx++)
		{
			uart1_rxmsgbuf[Rxmsg_idx].mCode = MC_USART1_IRQ_RXNE;
			uart1_rxmsgbuf[Rxmsg_idx].mSendTsk = DRV_ID_usart1;
			uart1_rxmsgbuf[Rxmsg_idx].mRecvTsk = APP_TID_usart1;
		}
		Rxmsg_idx = 0;
	}

	//Create Q of USART1
	App_Record[APP_TID_usart1].tQid = 
							OSQCreate(&TaskUsart1_Qarray[0], TASK_USART1_QSIZE);
	if(App_Record[APP_TID_usart1].tQid == NULL)
	{
		App_Record[APP_TID_usart1].tPrio = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}

	//sendbuf Q of USART1 initial
	SendbufP = NULL;
	SendBufQid = OSQCreate(&SendBuf_QArray[0], SENDBUF_USART1_QSIZE);
	if(SendBufQid == NULL)
	{
		OSQDel(App_Record[APP_TID_usart1].tQid,OS_DEL_ALWAYS,&err);
		App_Record[APP_TID_usart1].tQid = NULL;
		App_Record[APP_TID_usart1].tPrio = 0xFF;
		OSTaskDel(OS_PRIO_SELF);
		return;
	}

	// NVIC IRQ enable of USART1
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	SET_BIT(huart1.Instance->CR3, USART_CR3_EIE);
	/* Enable the UART Parity Error/Data Register not empty Interrupts */
	SET_BIT(huart1.Instance->CR1, USART_CR1_PEIE | USART_CR1_RXNEIE);
	
	USER_USART1_print("\n====Task USART1 Initialized====\n");

	while(1)
	{
		pmsg = OSQPend(App_Record[APP_TID_usart1].tQid,0,&err); // wait forever

		if(	(pmsg->mCode != MC_USART1_IRQ_RXNE) ||
				(pmsg->mRecvTsk != APP_TID_usart1) ||
				(pmsg->mSendTsk != DRV_ID_usart1))
			continue;

		c = pmsg->aChr;
#ifdef USART1_ECHO_TEST
		{
			while(READ_BIT(huart1.Instance->SR, UART_FLAG_TXE) == RESET);
			huart1.Instance->DR = (uint8_t)c;
		}
#endif

		//Shell Functions, may be ....

		
	} // while(1)

}


//============================================================
//USART1 IRQHandler

void OS_CPU_USART1_IRQHandler(void)
{
	OS_CPU_SR  	cpu_sr;
	uint32_t 		isrflags;
	uint32_t 		cr1its;
	uint32_t 		cr3its;
	uint32_t 		errorflags;
	uint8_t 		data;
	INT8U 			err;

	OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
	OSIntNesting++;
	OS_EXIT_CRITICAL();

  isrflags 	= READ_REG(huart1.Instance->SR);
	cr1its 		= READ_REG(huart1.Instance->CR1);
	cr3its 		= READ_REG(huart1.Instance->CR3);

	/* UART in mode Receiver -------------------------------------------------*/
	if(((isrflags & USART_SR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
	{
		data = (uint8_t)(huart1.Instance->DR);
		if(App_Record[APP_TID_usart1].tQid != NULL) 
		{
			uart1_rxmsgbuf[Rxmsg_idx].aChr = data;
			OSQPost(App_Record[APP_TID_usart1].tQid,(void *)&uart1_rxmsgbuf[Rxmsg_idx]); //send to task_uasrt1
			Rxmsg_idx ^= 1;
		}

	}

  /* If some errors occur */
  errorflags = (isrflags & (uint32_t)(USART_SR_PE | USART_SR_FE | USART_SR_ORE | USART_SR_NE));
  if((errorflags != RESET) && (((cr3its & USART_CR3_EIE) != RESET) || ((cr1its & (USART_CR1_RXNEIE | USART_CR1_PEIE)) != RESET)))
  {
    /* UART parity error interrupt occurred ----------------------------------*/
    if(((isrflags & USART_SR_PE) != RESET) && ((cr1its & USART_CR1_PEIE) != RESET))
    {
      huart1.ErrorCode |= HAL_UART_ERROR_PE;
    }
    
    /* UART noise error interrupt occurred -----------------------------------*/
    if(((isrflags & USART_SR_NE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    {
      huart1.ErrorCode |= HAL_UART_ERROR_NE;
    }
    
    /* UART frame error interrupt occurred -----------------------------------*/
    if(((isrflags & USART_SR_FE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    {
      huart1.ErrorCode |= HAL_UART_ERROR_FE;
    }
    
    /* UART Over-Run interrupt occurred --------------------------------------*/
    if(((isrflags & USART_SR_ORE) != RESET) && ((cr3its & USART_CR3_EIE) != RESET))
    { 
      huart1.ErrorCode |= HAL_UART_ERROR_ORE;
    }
  }

	//Transmit ...
  if(((isrflags & USART_SR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
  {
		if((SendbufP)&&(*SendbufP != 0))
		{
			huart1.Instance->DR = (uint8_t)(*SendbufP);
			SendbufP++;
		}
		else //SendbufP == NULL or str end
		{
			SendbufP = OSQAccept(SendBufQid,&err);
			if(SendbufP == NULL)
				CLEAR_BIT(huart1.Instance->CR1, USART_CR1_TXEIE); //TXEIE int disable
		}


  }

	OSIntExit();                                 /* Tell uC/OS-II that we are leaving the ISR          */
}


