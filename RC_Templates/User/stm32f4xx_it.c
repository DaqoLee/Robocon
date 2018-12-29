#include "stm32f4xx_it.h"
#include <stdio.h>
#include "Task_Usart.h"
#include "Task_can.h"
#include "BSP_USART.h"
#include "BSP_CAN.h"
/*
*********************************************************************************************************
*	Cortex-M3 内核异常中断服务程序
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*	函 数 名: NMI_Handler
*	功能说明: 不可屏蔽中断服务程序。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void NMI_Handler(void)
{
}

/*
*********************************************************************************************************
*	函 数 名: HardFault_Handler
*	功能说明: 硬件故障中断服务程序。其他异常处理被关闭，而又发生了异常，则触发。
*			  执行异常处理时，发生了异常，则触发。复位时默认使能。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void HardFault_Handler(void)
{
//#if 1
//  const char *pError = ERR_INFO;
//  uint8_t i;

//  for (i = 0; i < sizeof(ERR_INFO); i++)
//  {
//     USART1->DR = pError[i];
//     /* 等待发送结束 */
//     while ((USART1->SR & USART_FLAG_TC) == (uint16_t)RESET);
//  }
//#endif

//  /* 当硬件失效异常发生时进入死循环 */
//  while (1)
//  {
//  }
}

/*
*********************************************************************************************************
*	函 数 名: MemManage_Handler
*	功能说明: 内存管理异常中断服务程序。违反MPU设定的存储器访问规则时触发。 复位时默认未使能
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void MemManage_Handler(void)
{
  /* 当内存管理异常发生时进入死循环 */
  while (1)
  {
  }
}

/*
*********************************************************************************************************
*	函 数 名: BusFault_Handler
*	功能说明: 总线访问异常中断服务程序。取指令、数据读写、堆栈操作出现异常。 复位时默认未使能
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BusFault_Handler(void)
{
  /* 当总线异常时进入死循环 */
  while (1)
  {
  }
}

/*
*********************************************************************************************************
*	函 数 名: UsageFault_Handler
*	功能说明: 用法错误中断服务程序。执行未定义指令、非对齐操作、除零时触发。 复位时默认未使能
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void UsageFault_Handler(void)
{
  /* 当用法异常时进入死循环 */
  while (1)
  {
  }
}

/*
*********************************************************************************************************
*	函 数 名: DebugMon_Handler
*	功能说明: 调试监视器中断服务程序。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void DebugMon_Handler(void)
{
}

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
/******************************************************************************/
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg rxMessage;	
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0))
	{
		CAN_Receive(CAN1, CAN_FIFO0, &rxMessage);
		xQueueSendFromISR(xCan1RxQueue, &rxMessage, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		
  	CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
	}
}



/******************************************************************************/
void CAN2_RX0_IRQHandler(void)
{
	CanRxMsg rxMessage;	
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if(CAN_GetITStatus(CAN2, CAN_IT_FMP0))
	{
		CAN_Receive(CAN2, CAN_FIFO0, &rxMessage);
		xQueueSendFromISR(xCan2RxQueue, &rxMessage, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		
    CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
	}
	
}

/******************************************************************************/

