#include "BSP_USART.h"

/******************************************************************************/
uint8_t Usart1Buffer[20];
uint8_t Usart2Buffer[26];
uint8_t Usart3Buffer[26];
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
	
	USART1_RXDMA_Config((uint32_t)Usart1Buffer,20);
	
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	/* ʹ�ܴ��ڿ����ж� */
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}
/******************************************************************************/

void BSP_USART2_Init(uint32_t BaudRate)
{
	USART_InitTypeDef   USART_InitStructure;
	BSP_USART2_GPIOInit();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitStructure.USART_BaudRate           = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);

	USART2_RXDMA_Config((uint32_t)Usart2Buffer,26);

	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
	/* ʹ�ܴ��ڿ����ж� */
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}
/******************************************************************************/

void BSP_USART3_Init(uint32_t BaudRate)
{
	USART_InitTypeDef   USART_InitStructure;
	BSP_USART3_GPIOInit();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	USART_InitStructure.USART_BaudRate           = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART3, &USART_InitStructure);

	USART3_RXDMA_Config((uint32_t)Usart3Buffer,26);

	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
	/* ʹ�ܴ��ڿ����ж� */
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART3, ENABLE);
}
/******************************************************************************/

void USART_sendChar(USART_TypeDef* USARTx, char ch)
{
	/* ����һ���ֽ����ݵ����� */
	USART_SendData(USARTx, (uint8_t) ch);
	/* �ȴ�������� */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
}



#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
	USART2->DR = (u8) ch;      
	return ch;
}
#endif 


