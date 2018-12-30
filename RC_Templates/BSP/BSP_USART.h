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
#include "stm32f4xx.h"
#include "BSP_DMA.h"
#include "BSP_GPIO.h"
#include "stdio.h"	
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

/********USART2_DMA_define************/
#define USART2_RX_ADDR					 (uint32_t)(&USART2->DR)	/*串口2数据寄存器地址*/
#define USART2_RX_DMA_CHANNEL    DMA_Channel_4	        	/*DMA通道号*/
#define USART2_RX_DMA_STREAM     DMA1_Stream5	        	/*DMA数据流*/
/********USART2_DMA_define_END********/

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

/********USART3_DMA_define********/
#define USART3_RX_ADDR					 (uint32_t)(&USART3->DR)/*串口3数据寄存器地址*/
#define USART3_RX_DMA_CHANNEL    DMA_Channel_4	        /*DMA通道号*/
#define USART3_RX_DMA_STREAM     DMA1_Stream1	        	/*DMA数据流*/
/********USART3_DMA_define_END********/

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

/********UART4_DMA_define********/
#define UART4_RX_ADDR						  (uint32_t)(&UART4->DR)/*串口4数据寄存器地址*/
#define UART4_RX_DMA_CHANNEL      DMA_Channel_4       	/*DMA通道号*/
#define UART4_RX_DMA_STREAM       DMA1_Stream2	        /*DMA数据流*/
/********UART4_DMA_define_END********/

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

/********USART6_DMA_define********/
#define USART6_RX_ADDR						(uint32_t)(&USART6->DR)	/*串口6数据寄存器地址*/
#define USART6_RX_DMA_CHANNEL     DMA_Channel_5		        /*DMA通道号*/
#define USART6_RX_DMA_STREAM      DMA2_Stream1		        /*DMA数据流*/
/********USART6_DMA_define_END********/

/******************************************************************************/
extern uint8_t Usart1Buffer[20];
extern uint8_t Usart2Buffer[24];
/******************************************************************************/
void BSP_USART1_Init(uint32_t BaudRate);
void BSP_USART2_Init(uint32_t BaudRate);
#endif


 

