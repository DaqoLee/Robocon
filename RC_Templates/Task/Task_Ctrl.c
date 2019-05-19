/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Task_Ctrl.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-02-20               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Task_Ctrl.h" 
#include "Chassis.h"
#include "Joint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "DR16.h"
#include "Servo.h"
#include "RoboModule.h"
#include "Gyro.h"
/*-------------------------- D E F I N E S -----------------------------------*/

static TaskHandle_t xHandleCtrlChassis = NULL;
static TaskHandle_t xHandleCtrlGimbal = NULL;
static TaskHandle_t xHandleCtrlJoint = NULL;

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static void vTaskCtrlChassis(void *pvParameters);
static void vTaskCtrlGimbal(void *pvParameters);
static void vTaskCtrlJoint(void *pvParameters);

/*------------------G L O B A L - F U N C T I O N S --------------------------*/
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:18
	* @brief   控制任务创建函数
	* @param   void
	* @retval  void
	*/
void ControlTaskCreate(void)
{
	xTaskCreate(vTaskCtrlChassis,            /* 任务函数  */   
						  "vTaskCtrlChassis",          /* 任务名    */ 
						  256,       			             /* 任务栈大小*/
						  NULL,                        /* 任务参数  */
					    2,       			               /* 任务优先级*/
						  &xHandleCtrlChassis);        /* 任务句柄  */ 
	xTaskCreate(vTaskCtrlGimbal,            
					    "vTaskCtrlGimbal",          
				    	128,       			   
				    	NULL,                 
					    2,       			   
					    &xHandleCtrlGimbal);
	xTaskCreate(vTaskCtrlJoint,            
					    "vTaskCtrlJoint",          
				    	1000,       			   
				    	NULL,                 
					    2,       			   
					    &xHandleCtrlJoint);
}

/*---------------------L O C A L - F U N C T I O N S--------------------------*/
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:18
	* @brief   底盘控制任务
	* @param   void
	* @retval  void
	*/
static void vTaskCtrlChassis(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
	
	RoboModule_Init();/*RoboModule驱动初始化*/
  while(1)
	{
		
		Chassis_Ctrl();
		
	  vTaskDelayUntil(&CurrentControlTick, 10 / portTICK_RATE_MS);/*5ms延时*/
	}
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:18
	* @brief   云台控制任务
	* @param   void
	* @retval  void
	*/
static void vTaskCtrlGimbal(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
  while(1)
	{
	
	  vTaskDelayUntil(&CurrentControlTick, 5 / portTICK_RATE_MS);/*5ms延时*/
	}
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:18
	* @brief   关节控制任务
	* @param   void
	* @retval  void
	*/
static void vTaskCtrlJoint(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
	static uint8_t flag=0;
	vTaskDelay(500);
	GY955.targetYaw = GY955.Yaw;
	GY955.targetPitch = GY955.Pitch;
	GY955.targetRoll = GY955.Roll;
//	DXL1_setSyncMsg(USART_6,SPEED,2,0x01,600,0x02,600);

	vTaskDelay(100);
	
//			DXL1_setSyncMsg(USART_6,0x04,1,0x0B,0x01);
	DXL1_setSyncMsg(USART_6,SPEED,2,0x0D,100,0x0E,100);
	vTaskDelay(100);
//	DXL1_setSyncMsg(USART_6,0x06,1,0x08,1024);
//		vTaskDelay(100);
//	DXL1_setSyncMsg(USART_6,0x08,1,0x08,3072);
	Joint_RobotArmCtrl(890,2068);
  while(1)
	{
//		DXL1_setBulkReadMsg(USART_6,1,0x01,0x1E);
//		vTaskDelay(5);
//		DXL1_setBulkReadMsg(USART_6,1,0x02,0x1E);
//		vTaskDelay(5);
//		DXL1_setBulkReadMsg(USART_6,1,0x03,0x1E);
//		
//	flag++;
//	if(flag==8)
//	{
//	  
//		flag=0;
//	}
//	else
//	{
//	
//	}
//////		
////	
//	 DXL1_setBulkReadMsg(USART_6,1,flag,0x28);
		
//		 DXL1_setPingMsg(USART_6,0xFE);
//		 
//		 for(uint8_t i=1;i<13;i++)
//		 {
//		   if(DigitalServo.MX_64[i].Error==0x20)
//			 {
//				 DXL1_setRebootMsg(USART_6,i);
//				 vTaskDelay(5);
//			 }
//		 }

  
	#if 1
		Joint.Vspin = PID_Calc(&Joint.PID_Spin,GY955.Yaw,GY955.targetYaw);
//		

//    if(DR16.switch_left == 2)
//		{
//		  Joint_RobotArmCtrl(1900,1024);
//		}
//		else
//		{
//		  Joint_RobotArmCtrl(890,2068);
//		}
		if(DR16.switch_right == 3)
		{
			
			Joint_NewTrotMotionModel(-DR16.ch3/2,DR16.ch2/2,DR16.ch1/2,0.06f);
//			Joint_TrotMotionModel(-DR16.ch1/2,DR16.ch2/2,-Joint.Vspin);
		}
		else if(DR16.switch_right == 2)
		{
//			DXL1_setSyncMsg(USART_6,SPEED,12,0x01,100,0x02,100,0x03,100,
//																	0x04,100,0x05,100,0x06,100,
//																	0x07,100,0x08,100,0x09,100,
//																	0x0A,100,0x0B,100,0x0C,100);
			Joint_StateMachine();
//			Joint_TextPassSandDune(0);
			
//			Joint_NewWalkMotionModel(-DR16.ch3/2,DR16.ch2/2,DR16.ch1/2);
			//Joint_TrotMotionModel(-DR16.ch1/2,DR16.ch2/2,-DR16.ch3/2);
		}	
		else if(DR16.switch_right == 1)
    {
		  Joint_NewTrotMotionModel(-DR16.ch3/2,DR16.ch2/2,Joint.Vspin,0.06f);
		}
#endif
//		Joint_TrotMotionModelx(-DR16.ch1/2,DR16.ch2/2,-DR16.ch3/2);
//		Joint_WalkMotionModel(-DR16.ch1/2,DR16.ch2/2,-DR16.ch3/2);
//		Joint_WalkMotionModel(DR16.ch1,DR16.ch2/2,DR16.ch3);
 //   Joint_WalkMotionModel(DR16.ch1,0,DR16.ch3);
		
		vTaskDelay(10);
		
	 // vTaskDelayUntil(&CurrentControlTick, 10 / portTICK_RATE_MS);/*5ms延时*/
	}
}
/*-----------------------------------FILE OF END------------------------------*/

