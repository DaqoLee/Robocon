#include "stm32f4xx_it.h"
#include <stdio.h>
#include "Task_Usart.h"
#include "Task_can.h"
#include "BSP_USART.h"
#include "BSP_CAN.h"
/*
*********************************************************************************************************
*	Cortex-M3 �ں��쳣�жϷ������
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*	�� �� ��: NMI_Handler
*	����˵��: ���������жϷ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void NMI_Handler(void)
{
}

/*
*********************************************************************************************************
*	�� �� ��: HardFault_Handler
*	����˵��: Ӳ�������жϷ�����������쳣�����رգ����ַ������쳣���򴥷���
*			  ִ���쳣����ʱ���������쳣���򴥷�����λʱĬ��ʹ�ܡ�
*	��    ��: ��
*	�� �� ֵ: ��
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
//     /* �ȴ����ͽ��� */
//     while ((USART1->SR & USART_FLAG_TC) == (uint16_t)RESET);
//  }
//#endif

//  /* ��Ӳ��ʧЧ�쳣����ʱ������ѭ�� */
//  while (1)
//  {
//  }
}

/*
*********************************************************************************************************
*	�� �� ��: MemManage_Handler
*	����˵��: �ڴ�����쳣�жϷ������Υ��MPU�趨�Ĵ洢�����ʹ���ʱ������ ��λʱĬ��δʹ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void MemManage_Handler(void)
{
  /* ���ڴ�����쳣����ʱ������ѭ�� */
  while (1)
  {
  }
}

/*
*********************************************************************************************************
*	�� �� ��: BusFault_Handler
*	����˵��: ���߷����쳣�жϷ������ȡָ����ݶ�д����ջ���������쳣�� ��λʱĬ��δʹ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BusFault_Handler(void)
{
  /* �������쳣ʱ������ѭ�� */
  while (1)
  {
  }
}

/*
*********************************************************************************************************
*	�� �� ��: UsageFault_Handler
*	����˵��: �÷������жϷ������ִ��δ����ָ��Ƕ������������ʱ������ ��λʱĬ��δʹ��
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void UsageFault_Handler(void)
{
  /* ���÷��쳣ʱ������ѭ�� */
  while (1)
  {
  }
}

/*
*********************************************************************************************************
*	�� �� ��: DebugMon_Handler
*	����˵��: ���Լ������жϷ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void DebugMon_Handler(void)
{
}

/**
  * @brief  USART1�жϷ�������DRң����
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		/*�ر�DMA*/
		DMA_Cmd(USART1_RX_DMA_STREAM, DISABLE);
		/*��ȡDMAbuffʣ���С���Ƿ�ƥ��*/
		if (DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM) == 2)
		{
			xQueueSendFromISR(xUsart1RxQueue,&Usart1Buffer,&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
		
		/*��DMA*/
		DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);
		/*��������жϱ�־λ*/
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

