#include "Task_Init.h"
#include "Task_Usart.h"
#include "Task_CanSend.h"
#include "Key.h"
#include "OLED.h"
#include "Motor.h"
#include "BSP_USART.h"
/******************************************************************************/
static void vTaskLED0(void *pvParameters);
static void vTaskLED6(void *pvParameters);
/******************************************************************************/
TaskHandle_t StartTaskHandler=NULL;
static TaskHandle_t TaskLED0Handler=NULL;
static TaskHandle_t TaskLED6Handler=NULL;

/******************************************************************************/

void vTaskStart(void *pvParameters)
{		
	xUsart1RxQueue =xQueueCreate(20,20*sizeof(uint8_t));
	xCan1RxQueue=xQueueCreate(10,sizeof(CanRxMsg));
	xCan2RxQueue=xQueueCreate(10,sizeof(CanRxMsg));
	xCanSendQueue=xQueueCreate(20, sizeof(CanSend_t));
	
	vTaskDelay(1000);
	
	taskENTER_CRITICAL();      
  
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
						
 		xTaskCreate(vTaskCanSend,            
						"vTaskCanSend",          
						128,       			   
						NULL,                 
						1,       			   
						&xHandleCanSend); 
		xTaskCreate(vTaskLED0,       /* 任务函数  */   
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
//	CanSend_t CANSendData;
	
	while(1)
	{
//		KeyScan();
//		if(!KeyStatus)
//		{
//			LED_TOGGLE(LED_R);
//		    CANSendData.SendCanTxMsg.DLC   =   8;
//      M6020_setCurrent(CAN_1);
      printf("M6020[1].realAngle = %d\r\n",M6020[1].realAngle);
			vTaskDelay(10);
//		}

	}
}

