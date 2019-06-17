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
#include "Joint.h"
#include "delay.h"
/*-------------------------- D E F I N E S -----------------------------------*/

TaskHandle_t StartTaskHandler=NULL;

static TaskHandle_t TaskLEDHandler=NULL;
static TaskHandle_t TaskTestHandler=NULL;
//static TaskHandle_t TaskMonitorHandler=NULL;

volatile uint32_t ulHighFrequencyTimerTicks = 0UL;
/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static void vTaskLED(void *pvParameters);
static void vTaskTest(void *pvParameters);
//static void vTaskMonitor(void *pvParameters);

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
	taskENTER_CRITICAL();/*�����ٽ���*/
	/*------------------BSP��ʼ��------------------*/

  BSP_USART1_Init(100000); /*DR16���ջ�*/
  BSP_USART2_Init(115200);  /*SMS���*/
	BSP_USART3_Init(115200);  /*GY955������*/
	BSP_USART6_Init(1000000);  /*DXL���*/
	BSP_UART7_Init(115200);   /*����ͷ*/
	BSP_UART8_Init(57600);   /*������*/
	
	DMA_USART1RxConfig((uint32_t)DR16.buff,20);
	DMA_USART2RxConfig((uint32_t)Posture.buff,28);
	DMA_USART3RxConfig((uint32_t)GY955.buff,20);
	DMA_USART6RxConfig((uint32_t)DigitalServo.DxlBuff,20);
	DMA_UART8RxConfig((uint32_t)Ultrasonic.buff,20);
	DMA_UART7RxConfig((uint32_t)Camera.buff,12);

	BSP_CAN1_Init();
	//BSP_I2C2_Init();
	BSP_NVIC_Init();
	/*---------------Devices��ʼ��----------------*/
  delay_init();
  LED_Init();
	KEY_Init();
	DR16_Init();
	Gyro_Init();
	Motor_Init();
	OLED_Init();
	Photoelectric_Init();
  /*---------------Apps��ʼ��----------------*/

	Filter_Init();
	Joint_Init();
	Chassis_Init();
	/*-----------------Task����-------------------*/
	
	CanTaskCreate();   /* ����CAN������� */
	UsartTaskCreate(); /* ����USART������� */
  TestTaskCreate();  /* ��������������� */

	vTaskDelay(1000);  /*��ʱ�ȴ�ģ���ȶ�*/
	ControlTaskCreate();/* ������������ */
	/*-------------------------------------------*/
	
	vTaskDelete(StartTaskHandler);/*ɾ����ʼ����*/ 
  taskEXIT_CRITICAL(); /*�˳��ٽ���*/
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
	xTaskCreate(vTaskLED,         /* ������  */   
						"vTaskLED",         /* ������    */ 
						32,       			     /* ����ջ��С*/
						NULL,                /* �������  */
						1,       			   		 /* �������ȼ�*/
						&TaskLEDHandler);   /* ������  */ 
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
	//	LED_ON(LED0);
		for(uint8_t i=0;i<7;i++)
		{
				LED_ON(i);
				vTaskDelay(30); 
		}
		for(uint8_t i=0; i<7;i++)
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
  static	uint8_t keyFlg=1,timFlg=0,str[15],str1[15],str2[15];
	
//	float x=0.0f;//1000
//	int8_t t=0;
//	OLED_ShowCHinese(0,4,0);//��
//	OLED_ShowCHinese(18,4,1);//��
//	OLED_ShowCHinese(36,4,2);//԰
//	OLED_ShowCHinese(54,4,3);//��
//	OLED_ShowCHinese(72,4,4);//��
//	OLED_ShowCHinese(90,4,5);//��
//	OLED_ShowCHinese(108,4,6);//��
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

//     PhotoelectricScan();/*��翪��ɨ��*/

//		 if (!PhoFlg.LF || !PhoFlg.LH || !PhoFlg.RF || !PhoFlg.RH)
//		 {
//			LED_ON(LED_R);
//		 }
//		 else
//		 {
//			LED_OFF(LED_R);
//		 }

	//	OLED_Clear();

		
		//OLED_ShowString(0,3,"1.3' OLED TEST");
//		 for(uint8_t i=0;i<4;i++)
//		 {
//		 //  if(DigitalServo.MX_64[i].Error==0x20)
//			 {
//	//			 DXL1_setRebootMsg(USART_6,i);
//				 OLED_ShowNum(103,2*i,DigitalServo.MX_64[i+1].Error,3,16);
//				 vTaskDelay(5);
//			 }
//		 }	
     KeyScan();
		 if(!KeyStatus)
		 {
			 timFlg++;
		 }
		 else if(timFlg>1 && timFlg<10)
		 {
		   if(keyFlg)
			 {
			   Speed+=100;
			 }
			 else
       {
			   Speed-=100;
			 }
			 timFlg=0;
		 }
		 else if( timFlg>10)
		 {
			 vTaskDelay(200);
		   keyFlg=!keyFlg; 
			 timFlg=0;
		 }
		 
		 sprintf(str,  "realX = %5d",(int)Posture.realX_Coords);
		 sprintf(str1, "realY = %5d",(int)Posture.realY_Coords);
		 
		 sprintf(str2, "realZ = %5d",(int)(Posture.realZ_Angle*10));
//		 OLED_ShowNum(10,4,Speed,4,16);
		 
//		  OLED_ShowNum(10,6,GY955.Roll+10,3,16);
//		 OLED_ShowNum(64,4,Camera.Offset,3,16);
//		 OLED_ShowNum(103,4,Camera.Flag,3,16);
//		t++;
//		if(t>'~')t=' ';
//		  OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ 	
			
		
		OLED_ShowString(10,0,str);
		OLED_ShowString(10,2,str1);
		OLED_ShowString(10,4,str2);
		OLED_ShowString(32,6,RFIDBuf);
		vTaskDelay(50);
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
		printf("������\t\t����״̬\t���ȼ�\tʣ��ջ\t�������\r\n");
		vTaskList((char *)&pcWriteBuffer);
		printf("%s\r\n", pcWriteBuffer);
	
		printf("\r\n������\t\t���м���\t\tʹ����\r\n");
		vTaskGetRunTimeStats((char *)&pcWriteBuffer);
		printf("%s\r\n", pcWriteBuffer);

		vTaskDelay(100);
	}
}
/*-----------------------------------FILE OF END------------------------------*/
