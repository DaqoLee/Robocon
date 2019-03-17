/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Task_Init.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-01-12               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Task_Init.h"
#include "Task_Usart.h"
#include "Task_Can.h"
#include "Key.h"
#include "OLED.h"
#include "Motor.h"
#include "BSP_USART.h"
#include "BSP_TIM.h"
#include "Task_Ctrl.h"
#include "BSP_NVIC.h"
#include "DR16.h"
#include "Gyro.h"
#include "Servo.h"
#include "Filter.h" 
/*-------------------------- D E F I N E S -----------------------------------*/

TaskHandle_t StartTaskHandler=NULL;

static TaskHandle_t TaskLED0Handler=NULL;
static TaskHandle_t TaskLED6Handler=NULL;
volatile uint32_t ulHighFrequencyTimerTicks = 0UL;
/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static void vTaskLED0(void *pvParameters);
static void vTaskLED6(void *pvParameters);
static void LEDTaskCreate(void);

/*------------------G L O B A L - F U N C T I O N S --------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-12 17:22
	* @brief   
	* @param   void
	* @retval  void
	*/
void vTaskStart(void *pvParameters)
{		
	taskENTER_CRITICAL();/*进入临界区*/
	/*------------------BSP初始化------------------*/
  BSP_USART1_Init(100000); /*DR16接收机*/
  BSP_USART2_Init(115200);  /*SMS舵机*/
	BSP_USART3_Init(57600);  /*GY955陀螺仪*/
	BSP_USART6_Init(57600);  /*DXL舵机*/
	BSP_UART7_Init(57600);   /*摄像头*/
	BSP_UART8_Init(57600);
	
	DMA_USART1RxConfig((uint32_t)DR16.buff,20);
	DMA_USART2RxConfig((uint32_t)DigitalServo.SmsBuff,20);
	DMA_USART3RxConfig((uint32_t)GY955.buff,20);
	DMA_USART6RxConfig((uint32_t)DigitalServo.DxlBuff,20);

	BSP_CAN1_Init();
	BSP_I2C2_Init();
	BSP_NVIC_Init();
//	BSP_TIM6Init(0,20000);
	/*---------------Devices初始化----------------*/
  LED_Init();
	KEY_Init();
	DR16_Init();
	MotorParamInit();

	Filter_Init();
	/*-----------------Task创建-------------------*/
	CanTaskCreate();   /* 创建CAN任务 */
	UsartTaskCreate(); /* 创建USART任务 */
  LEDTaskCreate();   /* 创建LED任务 */
	vTaskDelay(1000);  /*延时等待模块稳定*/
	ControlTaskCreate();/* 创建控制任务 */
	/*-------------------------------------------*/
	
	vTaskDelete(StartTaskHandler);/*删除开始任务*/ 
  taskEXIT_CRITICAL(); /*退出临界区*/
}


/*---------------------L O C A L - F U N C T I O N S--------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-12 17:22
	* @brief   
	* @param   void
	* @retval  void
	*/
static void LEDTaskCreate(void)
{
	xTaskCreate(vTaskLED0,         /* 任务函数  */   
						"vTaskLED0",         /* 任务名    */ 
						128,       			     /* 任务栈大小*/
						NULL,                /* 任务参数  */
						1,       			   		 /* 任务优先级*/
						&TaskLED0Handler);   /* 任务句柄  */ 
	
	xTaskCreate(vTaskLED6,            
						"vTaskLED6",          
						256,       			   
						NULL,                 
						1,       			   
						&TaskLED6Handler); 
}
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-12 17:22
	* @brief   
	* @param   void
	* @retval  void
	*/
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
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-12 17:22
	* @brief   
	* @param   void
	* @retval  void
	*/
static void vTaskLED6(void *pvParameters)
{
//  uint8_t pcWriteBuffer[500];
	while(1)
	{
//		printf("=================================================\r\n");
//		printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
//		vTaskList((char *)&pcWriteBuffer);
//		printf("%s\r\n", pcWriteBuffer);
//	
//		printf("\r\n任务名       运行计数         使用率\r\n");
//		vTaskGetRunTimeStats((char *)&pcWriteBuffer);
//		printf("%s\r\n", pcWriteBuffer);
		vTaskDelay(100);

	}
}

/*-----------------------------------FILE OF END------------------------------*/
