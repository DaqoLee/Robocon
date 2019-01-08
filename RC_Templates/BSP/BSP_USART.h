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

/********USART1_Pin_define*****************************************************/
#define USART1_TX_GPIO_CLK      RCC_AHB1Periph_GPIOB
#define USART1_TX_GPIO_PORT     GPIOB
#define USART1_TX_Pin          	GPIO_Pin_6
#define USART1_TX_PINSOURCE			GPIO_PinSource6

#define USART1_RX_GPIO_CLK      RCC_AHB1Periph_GPIOB
#define USART1_RX_GPIO_PORT     GPIOB
#define USART1_RX_Pin           GPIO_Pin_7
#define USART1_RX_PINSOURCE			GPIO_PinSource7
/********USART1_Pin_define_END********/

/********USART2_Pin_define*****************************************************/
#define USART2_TX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART2_TX_GPIO_PORT      GPIOD
#define USART2_TX_Pin          	 GPIO_Pin_5
#define USART2_TX_PINSOURCE			 GPIO_PinSource5

#define USART2_RX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART2_RX_GPIO_PORT      GPIOD
#define USART2_RX_Pin            GPIO_Pin_6
#define USART2_RX_PINSOURCE			 GPIO_PinSource6
/********USART2_Pin_define_END********/

/********USART3_Pin_define*****************************************************/
#define USART3_TX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART3_TX_GPIO_PORT      GPIOD
#define USART3_TX_Pin          	 GPIO_Pin_8
#define USART3_TX_PINSOURCE			 GPIO_PinSource8

#define USART3_RX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART3_RX_GPIO_PORT      GPIOD
#define USART3_RX_Pin            GPIO_Pin_9
#define USART3_RX_PINSOURCE			 GPIO_PinSource9
/********USART3_Pin_define_END********/

/********UART4_Pin_define*****************************************************/
#define UART4_TX_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define UART4_TX_GPIO_PORT        GPIOA
#define UART4_TX_Pin          	 	GPIO_Pin_0
#define UART4_TX_PINSOURCE			  GPIO_PinSource0

#define UART4_RX_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define UART4_RX_GPIO_PORT        GPIOA
#define UART4_RX_Pin           		GPIO_Pin_1
#define UART4_RX_PINSOURCE			  GPIO_PinSource1
/********UART4_Pin_define_END********/
/********USART6_Pin_define*****************************************************/
#define USART6_TX_GPIO_CLK        RCC_AHB1Periph_GPIOG
#define USART6_TX_GPIO_PORT       GPIOG
#define USART6_TX_Pin          	 	GPIO_Pin_14
#define USART6_TX_PINSOURCE			  GPIO_PinSource14

#define USART6_RX_GPIO_CLK        RCC_AHB1Periph_GPIOG
#define USART6_RX_GPIO_PORT       GPIOG
#define USART6_RX_Pin           	GPIO_Pin_9
#define USART6_RX_PINSOURCE			  GPIO_PinSource9
/********USART6_Pin_define_END********/

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


 

