#include "BSP_CAN.h"
/******************************************************************************/
QueueHandle_t xCan1RxQueue = NULL;
QueueHandle_t xCan2RxQueue = NULL;

/******************************************************************************/
/**
  * @brief  CAN初始化
  * @param  void
  * @retval void
  */
void BSP_CAN1_Init(void)
{

	CAN_InitTypeDef     CAN_InitStructure;
	CAN_FilterInitTypeDef   CAN_FilterInitStructure;
	
	BSP_CAN1_GPIOInit();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
/************************CAN模式配置*******************************************/
	CAN_InitStructure.CAN_ABOM      =   ENABLE;          /*自动离线管理*/
	CAN_InitStructure.CAN_AWUM      =   DISABLE;         /*使用自动唤醒模式*/  
	CAN_InitStructure.CAN_NART      =   DISABLE;         /*报文自动重传*/
	CAN_InitStructure.CAN_TTCM      =   DISABLE;				 /*时间触发通信模式*/
	CAN_InitStructure.CAN_TXFP      =   DISABLE;				 /*优先级取决于标示符*/
	CAN_InitStructure.CAN_RFLM      =   DISABLE;			   /*溢出覆盖原有报文 */	
	CAN_InitStructure.CAN_Mode      =   CAN_Mode_Normal; /*工作模式*/
	
  /* ss=1 bs1=3 bs2=5 位时间宽度为(1+3+5) 波特率即为时钟周期tq*(1+3+5)  */	
	CAN_InitStructure.CAN_SJW       =   CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1       =   CAN_BS1_3tq;     
	CAN_InitStructure.CAN_BS2       =   CAN_BS2_5tq;   
	
  /*波特率分频器  定义了时间单元的时间长度 45/(1+3+5)/5=1 Mbps*/
	CAN_InitStructure.CAN_Prescaler =   5;
	CAN_Init(CAN1, &CAN_InitStructure);

  xCan1RxQueue=xQueueCreate(10,sizeof(CanRxMsg));
	
/*********************CAN筛选器初始化******************************************/
	CAN_FilterInitStructure.CAN_FilterNumber        =   0;/*筛选器组0*/
	CAN_FilterInitStructure.CAN_FilterMode          =   CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale         =   CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=   CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation    =   ENABLE; /*使能筛选器*/
	
	/*不进行过滤*/
	CAN_FilterInitStructure.CAN_FilterIdHigh        =   0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow         =   0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh    =   0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow     =   0x0000;
	
	CAN_FilterInit(&CAN_FilterInitStructure);

	/* FIFO0 message pending interrupt */
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}
/******************************************************************************/

void CAN2_Init(void)
{
	CAN_InitTypeDef     CAN_InitStructure;
	CAN_FilterInitTypeDef   CAN_FilterInitStructure;
	
  BSP_CAN2_GPIOInit();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
/************************CAN模式配置*******************************************/	
	CAN_InitStructure.CAN_ABOM      =   ENABLE;          /*自动离线管理*/
	CAN_InitStructure.CAN_AWUM      =   DISABLE;         /*使用自动唤醒模式*/  
	CAN_InitStructure.CAN_NART      =   DISABLE;         /*报文自动重传*/
	CAN_InitStructure.CAN_TTCM      =   DISABLE;				 /*时间触发通信模式*/
	CAN_InitStructure.CAN_TXFP      =   DISABLE;				 /*优先级取决于标示符*/
	CAN_InitStructure.CAN_RFLM      =   DISABLE;			   /*溢出覆盖原有报文 */	
	CAN_InitStructure.CAN_Mode      =   CAN_Mode_Normal; /*工作模式*/
	
  /* ss=1 bs1=3 bs2=5 位时间宽度为(1+3+5) 波特率即为时钟周期tq*(1+3+5)  */	
	CAN_InitStructure.CAN_SJW       =   CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1       =   CAN_BS1_3tq;     
	CAN_InitStructure.CAN_BS2       =   CAN_BS2_5tq;   
	
  /*波特率分频器  定义了时间单元的时间长度 45/(1+3+5)/5=1 Mbps*/
	CAN_InitStructure.CAN_Prescaler =   5;
	CAN_Init(CAN2, &CAN_InitStructure);

  xCan2RxQueue=xQueueCreate(10,sizeof(CanRxMsg));
/*********************CAN筛选器初始化******************************************/
	CAN_FilterInitStructure.CAN_FilterNumber        =   14;/*筛选器组0*/
	CAN_FilterInitStructure.CAN_FilterMode          =   CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale         =   CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=   CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation    =   ENABLE; /*使能筛选器*/
	
	/*不进行过滤*/
	CAN_FilterInitStructure.CAN_FilterIdHigh        =   0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow         =   0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh    =   0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow     =   0x0000;
	
	CAN_FilterInit(&CAN_FilterInitStructure);
  /* FIFO0 message pending interrupt */
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);

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

