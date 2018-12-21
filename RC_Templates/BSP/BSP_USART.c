#include "BSP_USART.h"

/******************************************************************************/
QueueHandle_t xUsart1RxQueue = NULL;
static uint8_t Usart1Buffer[20];
/******************************************************************************/
void BSP_USART1_Init(uint32_t BaudRate)
{
	USART_InitTypeDef   USART_InitStructure;
	BSP_USART1_GPIOInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitStructure.USART_BaudRate           = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	xUsart1RxQueue=xQueueCreate(50,sizeof(Usart1Buffer));
	
	USART1_RXDMA_Config((uint32_t)Usart1Buffer,20);
	
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	/* 使能串口空闲中断 */
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}
/******************************************************************************/


/**
  * @brief  USART1中断服务函数，DR遥控器
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		/*关闭DMA*/
		DMA_Cmd(USART1_RX_DMA_STREAM, DISABLE);
		/*获取DMAbuff剩余大小，是否匹配*/
		if (DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM) == 2)
		{
			xQueueSendFromISR(xUsart1RxQueue,&Usart1Buffer,&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
		
		/*打开DMA*/
		DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);
		/*清除空闲中断标志位*/
		(void)USART1->DR;
		(void)USART1->SR;

	}
}


