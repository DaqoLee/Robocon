#include "Task_CanSend.h"
#include "LED.h"
#include "Motor.h"
/******************************************************************************/
xQueueHandle  QueueCanSend;
TaskHandle_t xHandleCan1Receive = NULL;
TaskHandle_t xHandleCanSend = NULL;
float ZGyroModuleAngle=0.0f;
/******************************************************************************/
void vTaskCanSend(void *Parameters)
{
	CanSend_t CANSendData;
	
	while(1)
	{
		xQueueReceive(QueueCanSend, &CANSendData, portMAX_DELAY);
			
		if(CANSendData.CANx == 1)
		{     
			do/*CAN¹ÊÕÏÖØÆô*/
			{
				if(CAN1->ESR)
				{
					CAN1->MCR |= 0x02;
					CAN1->MCR &= 0xFD;
				}
			}while(!(CAN1->TSR & 0x1C000000));
			
			CAN_Transmit(CAN1, &(CANSendData.SendCanTxMsg));
		}
/******************************************************************************/
		else
		{
			do/*CAN¹ÊÕÏÖØÆô*/
			{	
				if(CAN2->ESR)
				{
					CAN2->MCR |= 0x02;
					CAN2->MCR &= 0xFD;
				}
			}while(!(CAN2->TSR & 0x1C000000));
			
			CAN_Transmit(CAN2, &(CANSendData.SendCanTxMsg));
		} 
	}
}
/******************************************************************************/


void vTaskCan1Receive(void *pvParameters)
{
	CanRxMsg rxMessage;
  while(1)
	{
	  xQueueReceive(xCan1RxQueue, &rxMessage,portMAX_DELAY);
	  M3508_DataDecode(rxMessage);
		M6020_DataDecode(rxMessage);
	  CAN1_DataDecoding(rxMessage);
    LED_TOGGLE(LED_R);

	}
}

/******************************************************************************/
static void CAN1_DataDecoding(CanRxMsg rxMessage)
{
	switch(rxMessage.StdId)
	{
		case 0x201:
			break;
		case 0x401:
			   ZGyroModuleAngle= -0.01f*((int32_t)(rxMessage.Data[0]<<24)|\
		                               (int32_t)(rxMessage.Data[1]<<16)|\
	                                 (int32_t)(rxMessage.Data[2]<<8) |\
	                       	         (int32_t)(rxMessage.Data[3])); 
			break;
		
		default:
			break;
	}
}



