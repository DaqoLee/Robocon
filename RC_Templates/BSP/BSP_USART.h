/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : BSP_USART.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-12         
  * Description:    
  * Function List:  
  	1. ....
  	   <version>: 		
  <modify staff>:
  		  <data>:
   <description>:  
  	2. ...
  ******************************************************************************
 */



#ifndef __BSP_USART_H_
#define __BSP_USART_H_
#include "BSP_DMA.h"
#include "BSP_GPIO.h"
#include "stdio.h"	

/******************************************************************************/
typedef enum
{
  USART_1=1,
  USART_2=2,
  USART_3=3,
  UART_4 =4,
  UART_5 =5,
  USART_6=6,
}USARTx_e;
typedef struct
{
  USARTx_e USART_x;
  uint16_t crc;
  uint8_t pUSARTSendBuff[20];
}USARTSend_t;



/******************************************************************************/
extern uint8_t Usart1Buffer[20];
extern uint8_t Usart2Buffer[26];
extern uint8_t Usart3Buffer[26];
/******************************************************************************/
void BSP_USART1_Init(uint32_t BaudRate);
void BSP_USART2_Init(uint32_t BaudRate);
void BSP_USART3_Init(uint32_t BaudRate);
void USART_sendChar(USART_TypeDef* USARTx, char ch);
#endif


 

