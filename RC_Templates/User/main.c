/**
  ************************************* Copyright ****************************** 
  *
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *                              
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *    
  * FileName   : main.c   
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

#include "stm32f4xx.h"
#include "LED.h"
#include "FreeRTOS.h"
#include "task.h"
#include "BSP_NVIC.h"
#include "BSP_USART.h"
#include "BSP_DMA.h"
#include "BSP_CAN.h"
#include "Task_Init.h"
#include "Key.h"
#include "BSP_I2C.h"
#include "OLED.h"
/******************************************************************************/


/******************************************************************************/


/******************************************************************************/


int main(void)
{	
 /* �����ʼ�� */

	BSP_NVIC_Init();
  BSP_USART1_Init(100000);
	BSP_CAN1_Init();
	BSP_I2C2_Init();
  LED_Init();
	KEY_Init();
//  OLED_Init();
 /* ������ʼ���� */
	xTaskCreate(vTaskStart,           /* ������  */        
					  	"vTaskStart",         /* ������    */      
						  512,       			      /* ����ջ��С*/  
						  NULL,                 /* �������  */    
					  	1,       			        /* �������ȼ�*/
					  	&StartTaskHandler);   /* ������  */ 
	
  /* �������ȣ���ʼִ������ */
	vTaskStartScheduler();            
}

/******************************************************************************/


/******************************************************************************/

