/**
  ******************************************************************************
  * File Name          : message.h
  * Description        : demo code of message header 
  ******************************************************************************
  *
  * COPYRIGHT(c) 2019 jkuang@BUPT
  *
  ******************************************************************************
  */

#ifndef   MESSAGE_H
#define   MESSAGE_H
#ifdef __cplusplus
		 extern "C" {
#endif

/**************************************************************************
	message head format :
 
     mCode         message general code inside one CPU system
     mSendTsk      message sender TaskID or Mudule ID
     mRecvTsk      message receiver TaskID or Mudule ID
			 0-255:Task, -1 and bellow: ISR or Other Module
     mSendInst     message sender instance ID
     mRecvInst     message receiver instance ID
     mLen          Data length follow mLen
**************************************************************************/
typedef struct _MESSAGE_HEAD
{
		INT16U	mCode;
		INT16S 	mSendTsk;
		INT16S 	mRecvTsk;
    INT16U  mSendInst;
    INT16U  mRecvInst;
    INT16U  mLen;
} MESSAGE_HEAD;

#define pMSG_HEAD(x) ((MESSAGE_HEAD *)&(x))


// UART DATA MSG definition ================================================
typedef struct _UART_RX_MSG
{
	INT16U	mCode;
	INT16S	mSendTsk;
	INT16S	mRecvTsk;
	char		aChr;
}UART_RX_MSG;

#define pUART_RX_MSG(x) ((UART_RX_MSG *)&(x))

// message Code definition ==========================================
#define MC_USART1_IRQ_RXNE				100			//USART1 IRQ RXNE
//#define MC_USART1_IRQ_TXE					101			//USART1 IRQ TXE
//#define MC_USART1_DATA_SEND				102			//USART1 data send

#define MC_TMRTST_TMR1						150
#define MC_TMRTST_TMR2						151
#define MC_TMRTST_TMR3						152
#define MC_TMRTST_TMR4						153
#define MC_TMRTST_TMR11						154
#define MC_TMRTST_TMR22						155
#define MC_TMRTST_TMR33						156

#define MC_KEY1_SWITCH						171			//KEY 1 switch
#define MC_KEY2_SWITCH						172			//KEY 2 switch
#define MC_KEY3_SWITCH						173			//KEY 3 switch
#define MC_KEY4_SWITCH						174			//KEY 4 switch


#ifdef __cplusplus
}
#endif 
#endif  //MESSAGE_H
