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
#define USART1_RX_ADDR					(uint32_t)(&USART1->DR)	/*����1���ݼĴ�����ַ*/
#define USART1_RX_DMA_CHANNEL   DMA_Channel_4	         	/*DMAͨ����*/
#define USART1_RX_DMA_STREAM    DMA2_Stream2		        /*DMA������*/
/********USART1_DMA_define_END********/

void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);
#endif


 

