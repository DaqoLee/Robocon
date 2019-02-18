#include "Task_Ctrl.h"
#include "Joint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "DR16.h"
#include "Servo.h"
/******************************************************************************/
static void vTaskCtrlChassis(void *pvParameters);
static void vTaskCtrlGimbal(void *pvParameters);
static void vTaskCtrlJoint(void *pvParameters);
/******************************************************************************/
static TaskHandle_t xHandleCtrlChassis = NULL;
static TaskHandle_t xHandleCtrlGimbal = NULL;
static TaskHandle_t xHandleCtrlJoint = NULL;
/******************************************************************************/
void ControlTaskCreate(void)
{
	xTaskCreate(vTaskCtrlChassis,            /* 任务函数  */   
						  "vTaskCtrlChassis",          /* 任务名    */ 
						  128,       			             /* 任务栈大小*/
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
				    	128,       			   
				    	NULL,                 
					    2,       			   
					    &xHandleCtrlJoint);
}
/******************************************************************************/
static void vTaskCtrlChassis(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
  while(1)
	{
	  vTaskDelayUntil(&CurrentControlTick, 5 / portTICK_RATE_MS);/*5ms延时*/
	}
}

/******************************************************************************/


static void vTaskCtrlGimbal(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
  while(1)
	{
		
		
	  vTaskDelayUntil(&CurrentControlTick, 5 / portTICK_RATE_MS);/*5ms延时*/
	}
}



/******************************************************************************/
	
static void vTaskCtrlJoint(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
	vTaskDelay(500);
	Dynamixel1_setSyncMsg(SPEED,2,0x01,600,0x02,600);
	vTaskDelay(5);
	Dynamixel1_setSyncMsg(ACC,2,0x01,50,0x02,50);
  while(1)
	{
//		Thigh_M6020Ctrl();
//		Joint_MotionModel(DR16.ch1,DR16.ch2,DR16.ch3);
	  // Dynamixel1_setSyncTarAng(4,0x01,2548,0x03,2548,0x05,2548,0x07,2548);
		// vTaskDelay(80);
		// Dynamixel1_setSyncTarAng(4,0x02,2548,0x04,2548,0x06,2548,0x08,2548);
		// vTaskDelay(220);
		
	  // Dynamixel1_setSyncTarAng(4,0x01,2700,0x03,2700,0x05,2700,0x07,2700);
		// vTaskDelay(5);
		// Dynamixel1_setSyncTarAng(4,0x02,2700,0x04,2648,0x06,2648,0x08,2648);  
		// vTaskDelay(220);
	  Dynamixel1_setSyncMsg(POSITION,4,0x01,2548,0x03,2548,0x05,2548,0x07,2548);
		vTaskDelay(80);
		Dynamixel1_setSyncMsg(POSITION,4,0x02,2548,0x04,2548,0x06,2548,0x08,2548);
		vTaskDelay(220);
		
	  Dynamixel1_setSyncMsg(POSITION,4,0x01,2700,0x03,2700,0x05,2700,0x07,2700);
		vTaskDelay(5);
		Dynamixel1_setSyncMsg(POSITION,4,0x02,2700,0x04,2648,0x06,2648,0x08,2648);  
		vTaskDelay(220);		
	  vTaskDelayUntil(&CurrentControlTick, 5 / portTICK_RATE_MS);/*5ms延时*/
	}
}

/******************************************************************************/
