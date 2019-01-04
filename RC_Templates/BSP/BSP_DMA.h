/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : BSP_DMA.h   
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



#ifndef __BSP_DMA_H_
#define __BSP_DMA_H_
#include "stm32f4xx.h"



/********USART1_DMA_define********/
#define USART1_RX_ADDR					(uint32_t)(&USART1->DR)	/*串口1数据寄存器地址*/
#define USART1_RX_DMA_CHANNEL   DMA_Channel_4	         	/*DMA通道号*/
#define USART1_RX_DMA_STREAM    DMA2_Stream2		        /*DMA数据流*/
/********USART1_DMA_define_END********/

/********USART2_DMA_define********/
#define USART2_RX_ADDR						(uint32_t)(&USART2->DR)	//串口1数据寄存器地址
#define USART2_RX_DMA_CHANNEL           	DMA_Channel_4		//DMA通道号
#define USART2_RX_DMA_STREAM           		DMA1_Stream5		//DMA数据流
/********USART2_DMA_define_END********/

/********USART3_DMA_define********/
#define USART3_RX_ADDR						(uint32_t)(&USART3->DR)	//串口1数据寄存器地址
#define USART3_RX_DMA_CHANNEL           	DMA_Channel_4		//DMA通道号
#define USART3_RX_DMA_STREAM           		DMA1_Stream1		//DMA数据流
/********USART3_DMA_define_END********/

void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize);
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize);
#endif


 

