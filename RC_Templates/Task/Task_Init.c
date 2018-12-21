#include "Task_Init.h"
#include "Task_Usart.h"
#include "Task_CanSend.h"
#include "Key.h"
#include "OLED.h"
/******************************************************************************/

/******************************************************************************/
TaskHandle_t StartTaskHandler=NULL;
static TaskHandle_t TaskLED0Handler=NULL;
static TaskHandle_t TaskLED6Handler=NULL;

/******************************************************************************/

void vTaskStart(void *pvParameters)
{		
	
	taskENTER_CRITICAL();      
  
	xTaskCreate(vTaskLED0,         /* 任务函数  */   
						"vTaskLED0",         /* 任务名    */ 
						128,       			     /* 任务栈大小*/
						NULL,                /* 任务参数  */
						1,       			   		 /* 任务优先级*/
						&TaskLED0Handler);   /* 任务句柄  */ 
	
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
		KeyScan();
		if(!KeyStatus)
		{
//			LED_TOGGLE(LED_R);
			vTaskDelay(180);
		}

	}
}

