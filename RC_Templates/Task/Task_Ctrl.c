#include "Task_Ctrl.h"
#include "FreeRTOS.h"
#include "task.h"
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
	xTaskCreate(vTaskCtrlChassis,            /* ������  */   
						  "vTaskCtrlChassis",          /* ������    */ 
						  128,       			             /* ����ջ��С*/
						  NULL,                        /* �������  */
					    2,       			               /* �������ȼ�*/
						  &xHandleCtrlChassis);        /* ������  */ 
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
  while(1)
	{
	  vTaskDelay(10);
	}
}

/******************************************************************************/


static void vTaskCtrlGimbal(void *pvParameters)
{
  while(1)
	{
	  vTaskDelay(10);
	}
}



/******************************************************************************/

static void vTaskCtrlJoint(void *pvParameters)
{
  while(1)
	{
	  vTaskDelay(10);
	}
}

/******************************************************************************/
