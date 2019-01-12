/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Servo.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-01-10               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Servo.h"
#include "BSP_USART.h"
#include "string.h"
#include "Task_Usart.h"
#include "check.h"
	
/*-------------------------- D E F I N E S -----------------------------------*/



/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/



/*------------------G L O B A L - F U N C T I O N S --------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-10 14:06
	* @brief   
	* @param   void
	* @retval  void
	*/
void Dynamixel_getMassage(uint8_t *DynamixelBuffer)
{
   for(uint8_t i=0;i<20;i++)
   {
      if(DynamixelBuffer[i] == 0xFF && DynamixelBuffer[i+1]==0xFF && \
                                 DynamixelBuffer[i+2] == 0xFD)
      {

      }
   }


}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-10 14:07
	* @brief   
	* @param   void
	* @retval  void
	*/
void Dynamixel_setMassage(uint8_t ID, uint16_t Length, uint8_t Cmd, uint8_t *Data)
{
	USARTSend_t usartSend;
	
	usartSend.USART_x=USART_2;
	usartSend.pUSARTSendBuff[0]=0xFF;
	usartSend.pUSARTSendBuff[1]=0xFF;
	usartSend.pUSARTSendBuff[2]=0xFD;

	usartSend.pUSARTSendBuff[3]=0x00;
	usartSend.pUSARTSendBuff[4]=ID;
	usartSend.pUSARTSendBuff[5]=Length;
	usartSend.pUSARTSendBuff[6]=Length>>8;
	usartSend.pUSARTSendBuff[7]=Cmd;

	memcpy(&usartSend.pUSARTSendBuff[8],Data,Length);

	usartSend.crc=update_crc(0,usartSend.pUSARTSendBuff,5+Length);
	usartSend.pUSARTSendBuff[8+Length]=usartSend.crc;
	usartSend.pUSARTSendBuff[9+Length]=usartSend.crc>>8;
	
	xQueueSend(xusartTxQueue, &usartSend, 20);
   
}


/*---------------------L O C A L - F U N C T I O N S--------------------------*/



/*-----------------------------------FILE OF END------------------------------*/





