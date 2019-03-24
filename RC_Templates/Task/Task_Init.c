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
#include "Ultrasonic.h" 
#include "Camera.h" 
#include "Photoelectric.h" 
#include "Chassis.h"
#include "math.h"
#include "Encoder.h" 
/*-------------------------- D E F I N E S -----------------------------------*/

TaskHandle_t StartTaskHandler=NULL;

static TaskHandle_t TaskLEDHandler=NULL;
static TaskHandle_t TaskTestHandler=NULL;
static TaskHandle_t TaskMonitorHandler=NULL;

volatile uint32_t ulHighFrequencyTimerTicks = 0UL;
/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static void vTaskLED(void *pvParameters);
static void vTaskTest(void *pvParameters);
static void vTaskMonitor(void *pvParameters);

static void TestTaskCreate(void);

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
	BSP_UART8_Init(57600);   /*超声波*/
	
	DMA_USART1RxConfig((uint32_t)DR16.buff,20);
	DMA_USART2RxConfig((uint32_t)Posture.Buff,28);
	DMA_USART3RxConfig((uint32_t)GY955.buff,20);
	DMA_USART6RxConfig((uint32_t)DigitalServo.DxlBuff,20);
	DMA_UART8RxConfig((uint32_t)Ultrasonic.buff,20);
	DMA_UART7RxConfig((uint32_t)Camera.buff,20);

	BSP_CAN1_Init();
	BSP_I2C2_Init();
	BSP_NVIC_Init();
	/*---------------Devices初始化----------------*/

  LED_Init();
	KEY_Init();
	DR16_Init();
	Motor_Init();
	Photoelectric_Init();
  /*---------------Apps初始化----------------*/

	Filter_Init();
	Chassis_Init();
	/*-----------------Task创建-------------------*/
	
	CanTaskCreate();   /* 创建CAN相关任务 */
	UsartTaskCreate(); /* 创建USART相关任务 */
  TestTaskCreate();  /* 创建测试相关任务 */

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
static void TestTaskCreate(void)
{
	xTaskCreate(vTaskLED,         /* 任务函数  */   
						"vTaskLED",         /* 任务名    */ 
						32,       			     /* 任务栈大小*/
						NULL,                /* 任务参数  */
						1,       			   		 /* 任务优先级*/
						&TaskLEDHandler);   /* 任务句柄  */ 
#if 1
	xTaskCreate(vTaskTest,            
						"vTaskTest",          
						256,       			   
						NULL,                 
						1,       			   
						&TaskTestHandler); 
#endif

#if 0			
	xTaskCreate(vTaskMonitor,            
						"vTaskMonitor",          
						256,       			   
						NULL,                 
						1,       			   
						&TaskMonitorHandler); 
#endif
}
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-12 17:22
	* @brief   
	* @param   void
	* @retval  void
	*/
static void vTaskLED(void *pvParameters)
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
static void vTaskTest(void *pvParameters)
{
	float x=0.0f;//1000
	int8_t i=0;
	while(1)
	{
//		for(;x<5250;x+=30)
//		{
//		  i++;
//		  printf("%f, ",	(13*PI*cos((PI*(x - 750))/1500))/30);
//			if(i==5)
//		  {
//				i=0;
//				printf("\r\n");
//			}
//		  vTaskDelay(1);
//		}

    // PhotoelectricScan();/*光电开关扫描*/

    // if (!PhoFlg.LF || !PhoFlg.LH || !PhoFlg.RF || !PhoFlg.RH)
		// {
		// 	LED_ON(LED_G);
		// }
		// else
		// {
		// 	LED_OFF(LED_G);
		// }
		
		vTaskDelay(5);
	}
}

/**
	* @Data    2019-03-18 15:31
	* @brief   
	* @param   void
	* @retval  void
	*/
static void vTaskMonitor(void *pvParameters)
{
	uint8_t pcWriteBuffer[500];
	BSP_USART2_Init(115200);
	BSP_TIM6Init(0,20000);
	while(1)
	{
		printf("=================================================\r\n");
		printf("任务名\t\t任务状态\t优先级\t剩余栈\t任务序号\r\n");
		vTaskList((char *)&pcWriteBuffer);
		printf("%s\r\n", pcWriteBuffer);
	
		printf("\r\n任务名       运行计数         使用率\r\n");
		vTaskGetRunTimeStats((char *)&pcWriteBuffer);
		printf("%s\r\n", pcWriteBuffer);

		vTaskDelay(100);
	}
}
/*-----------------------------------FILE OF END------------------------------*/
