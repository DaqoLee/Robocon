#include "Task_Ctrl.h"
#include "Joint.h"
#include "FreeRTOS.h"
#include "task.h"

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
uint8_t Txt1[3]={0x1E,0x0C,0x0A};
uint8_t Txt2[3]={0x1E,0x0C,0x0F };
	//uint8_t Txt[8]={0x19,0x00,0x01};
	portTickType CurrentControlTick = 0;
  while(1)
	{
		Thigh_M6020Ctrl();
	  Dynamixel1_setMassage(0x01, 5, 0x03, Txt1);
		vTaskDelay(5);
		 Dynamixel1_setMassage(0x02, 5, 0x03, Txt1);
		vTaskDelay(300);
		Dynamixel1_setMassage(0x01, 5, 0x03, Txt2);
		vTaskDelay(5);
		 Dynamixel1_setMassage(0x02, 5, 0x03, Txt2);
		vTaskDelay(300);
	  vTaskDelayUntil(&CurrentControlTick, 5 / portTICK_RATE_MS);/*5ms延时*/
	}
}

/******************************************************************************/
