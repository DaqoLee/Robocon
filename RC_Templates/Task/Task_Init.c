#include "Task_Init.h"
#include "Task_Usart.h"
#include "Task_Can.h"
#include "Key.h"
#include "OLED.h"
#include "Motor.h"
#include "BSP_USART.h"
#include "Task_Ctrl.h"
#include "BSP_NVIC.h"
#include "DR16.h"
/******************************************************************************/
static void vTaskLED0(void *pvParameters);
static void vTaskLED6(void *pvParameters);
static void LEDTaskcreate(void);
/******************************************************************************/
TaskHandle_t StartTaskHandler=NULL;
static TaskHandle_t TaskLED0Handler=NULL;
static TaskHandle_t TaskLED6Handler=NULL;

/******************************************************************************/

void vTaskStart(void *pvParameters)
{		
	taskENTER_CRITICAL();/*进入临界区*/
	
  BSP_USART1_Init(100000);
  BSP_USART2_Init(115200);
	BSP_CAN1_Init();
	BSP_I2C2_Init();
	BSP_NVIC_Init();
	
  LED_Init();
	KEY_Init();
	DR16_Init();
	MotorParamInit();

	CanTaskCreate();  /* 创建CAN任务 */
	UsartTaskCreate();/* 创建USART任务 */
  LEDTaskcreate();  /* 创建LED任务 */
	
	vTaskDelay(1000);/*延时等待模块稳定*/
	
	ControlTaskCreate();/* 创建控制任务 */
	
	vTaskDelete(StartTaskHandler);/*删除开始任务*/ 
	
  taskEXIT_CRITICAL(); /*退出临界区*/
}

/******************************************************************************/



static void LEDTaskcreate(void)
{
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
//      printf("M6020[1].realAngle = %d\r\n",M6020[1].realAngle);
			vTaskDelay(10);
//		}

	}
}
/******************************************************************************/
