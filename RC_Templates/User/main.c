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
#include "Task_Usart.h"
#include "Task_CanSend.h"
/******************************************************************************/
static void vTaskStart(void *pvParameters);
static void vTaskLED0(void *pvParameters);
static void vTaskLED6(void *pvParameters);
/******************************************************************************/
static TaskHandle_t StartTaskHandler=NULL;
static TaskHandle_t TaskLED0Handler=NULL;
static TaskHandle_t TaskLED6Handler=NULL;
uint32_t Usart1RxMsg[20];
/******************************************************************************/


int main(void)
{	
 /* 外设初始化 */

	BSP_NVIC_Init();
  BSP_USART1_Init(100000);
	BSP_CAN1_Init();
  LED_Init();
	
 /* 创建开始任务 */
	xTaskCreate(vTaskStart,           /* 任务函数  */        
					  	"vTaskStart",         /* 任务名    */      
						  512,       			      /* 任务栈大小*/  
						  NULL,                 /* 任务参数  */    
					  	1,       			        /* 任务优先级*/
					  	&StartTaskHandler);   /* 任务句柄  */ 
	
  /* 启动调度，开始执行任务 */
	vTaskStartScheduler();            
}

/******************************************************************************/

static void vTaskStart(void *pvParameters)
{	
	taskENTER_CRITICAL();      
  
	xTaskCreate(vTaskLED0,            
						"vTaskLED0",          
						128,       			   
						NULL,                 
						1,       			   
						&TaskLED0Handler);   
	
	xTaskCreate(vTaskLED6,            
						"vTaskLED6",          
						128,       			   
						NULL,                 
						1,       			   
						&TaskLED6Handler); 
	
	xTaskCreate(vTaskUsart1Receive,            
						"vTaskUsart1Receive",          
						128,       			   
						NULL,                 
						2,       			   
						&xHandleUsart1Receive);
						
 		xTaskCreate(vTaskCan1Receive,            
						"vTaskCan1Receive",          
						128,       			   
						NULL,                 
						2,       			   
						&xHandleCan1Receive); 
	vTaskDelete(StartTaskHandler); 
	taskEXIT_CRITICAL();
}


static void vTaskLED0(void *pvParameters)
{
	while(1)
	{
		LED_ON(LED0);
		for(uint8_t i=1;i<7;i++)
		{
				LED_ON(i);
				vTaskDelay(30); 
		}
		for(uint8_t i=6;i>0;i--)
		{
				LED_OFF(i);
				vTaskDelay(30);
		}
	
	}
}

static void vTaskLED6(void *pvParameters)
{
	
	while(1)
	{
//    LED_TOGGLE(LED_R);
		vTaskDelay(180);

	}
}
/******************************************************************************/

