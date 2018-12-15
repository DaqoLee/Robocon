#include "Task_Usart.h"
#include "BSP_USART.h"
#include "DR16.h"
#include "LED.h"
/******************************************************************************/
TaskHandle_t xHandleUsart1Receive = NULL;

/******************************************************************************/








/******************************************************************************/
void vTaskUsart1Receive(void *pvParameters)
{
  uint8_t usart1RxBuffer[20];
  while(1)
	{
	  xQueueReceive(xUsart1RxQueue, &usart1RxBuffer,portMAX_DELAY);
		DR16_DataDecode(usart1RxBuffer);
		LED_TOGGLE(LED_G);
	}

}


/******************************************************************************/


void vTaskUsart2Receive(void *pvParameters)
{
  uint8_t usart2RxBuffer[20];
  while(1)
	{
	  xQueueReceive(xUsart1RxQueue, &usart2RxBuffer,portMAX_DELAY);
		DR16_DataDecode(usart2RxBuffer);
		LED_TOGGLE(LED_G);
	}

}
/******************************************************************************/

