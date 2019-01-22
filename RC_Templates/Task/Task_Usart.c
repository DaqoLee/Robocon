#include "Task_Usart.h"
#include "BSP_USART.h"
#include "DR16.h"
#include "LED.h"
#include "Encoder.h"
/******************************************************************************/
static TaskHandle_t xHandleUsart1Receive = NULL;
static TaskHandle_t xHandleUsart2Receive = NULL;
static TaskHandle_t xHandleUsart3Receive = NULL;
static TaskHandle_t xHandleUsartsend     = NULL;

QueueHandle_t xUsart1RxQueue = NULL;
QueueHandle_t xUsart2RxQueue = NULL;
QueueHandle_t xUsart3RxQueue = NULL;
QueueHandle_t xusartTxQueue = NULL;
/******************************************************************************/
static void vTaskUsart1Receive(void *pvParameters);
static void vTaskUsart2Receive(void *pvParameters);
static void vTaskUsart3Receive(void *pvParameters);
static void vTaskUsartSend(void *pvParameters);
/******************************************************************************/

void UsartTaskCreate(void)
{
	xUsart1RxQueue = xQueueCreate(20,20*sizeof(uint8_t));
	xUsart2RxQueue = xQueueCreate(20,20*sizeof(uint8_t));
	xUsart3RxQueue = xQueueCreate(20,20*sizeof(uint8_t));
	xusartTxQueue  = xQueueCreate(20,sizeof(USARTSend_t));

	
	xTaskCreate(vTaskUsart1Receive,             /* 任务函数  */
						  "vTaskUsart1Receive",           /* 任务名    */
						  128,       			                /* 任务栈大小*/
					  	NULL,                           /* 任务参数  */
					  	3,       			                  /* 任务优先级*/
					  	&xHandleUsart1Receive);         /* 任务句柄  */ 
	
	xTaskCreate(vTaskUsart2Receive,            
					  	"vTaskUsart2Receive",          
						  128,       			   
						  NULL,                 
						  3,       			   
					  	&xHandleUsart2Receive);	
	
	xTaskCreate(vTaskUsart3Receive,            
					  	"vTaskUsart3Receive",          
						  128,       			   
						  NULL,                 
						  3,       			   
					  	&xHandleUsart3Receive);

	xTaskCreate(vTaskUsartSend,            
					  	"vTaskUsartSend",          
						  128,       			   
						  NULL,                 
						  3,       			   
					  	&xHandleUsartsend);
}



/******************************************************************************/
static void vTaskUsart1Receive(void *pvParameters)
{
  uint8_t usart1RxBuffer[20];
  while(1)
	{
	  xQueueReceive(xUsart1RxQueue, &usart1RxBuffer,portMAX_DELAY);
		DR16.p_DR16getMsg(usart1RxBuffer);
		LED_TOGGLE(LED_G);
	}

}


/******************************************************************************/


static void vTaskUsart2Receive(void *pvParameters)
{
  uint8_t usart2RxBuffer[24];
  while(1)
	{
	  xQueueReceive(xUsart2RxQueue, &usart2RxBuffer,portMAX_DELAY);
		Posture_getMessage(usart2RxBuffer);
	}

}
/******************************************************************************/

static void vTaskUsart3Receive(void *pvParameters)
{
  uint8_t usart3RxBuffer[20];
  while(1)
	{
	  xQueueReceive(xUsart3RxQueue, &usart3RxBuffer,portMAX_DELAY);

	}

}
/******************************************************************************/

static void vTaskUsartSend(void *pvParameters)
{
	USARTSend_t usartSend;
  while(1)
	{
	  xQueueReceive(xusartTxQueue, &usartSend,portMAX_DELAY);
		if(usartSend.USART_x==USART_1)
		{

		}
		else if(usartSend.USART_x==USART_2)
		{
			for(uint8_t i=0;i<9;i++)
			{
				USART_sendChar(USART2,usartSend.pUSARTSendBuff[i]);
			}			
		}
		else if(usartSend.USART_x==USART_3)
		{
			for(uint8_t i=0;i<13;i++)
			{
				USART_sendChar(USART3,usartSend.pUSARTSendBuff[i]);
			}			
		}
	}

}


void vPrintString(const char *pcString)
{
    taskENTER_CRITICAL();
    {
        printf("%s", pcString);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
}
/******************************************************************************/

