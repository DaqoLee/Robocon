#include "BSP_USART.h"

/******************************************************************************/
uint8_t Usart1Buffer[20];
uint8_t Usart2Buffer[26];
uint8_t Usart3Buffer[26];
/******************************************************************************/
void BSP_USART1_Init(uint32_t BaudRate)
{
	USART_InitTypeDef   USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	RCC_AHB1PeriphClockCmd(USART1_TX_GPIO_CLK | USART1_RX_GPIO_CLK,ENABLE);
			/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;  
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(USART1_TX_GPIO_PORT, USART1_TX_PINSOURCE, GPIO_AF_USART1);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(USART1_RX_GPIO_PORT, USART1_RX_PINSOURCE, GPIO_AF_USART1);

	USART_InitStructure.USART_BaudRate           = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	USART1_RXDMA_Config((uint32_t)Usart1Buffer,20);
	
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	/* 使能串口空闲中断 */
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}
/******************************************************************************/

void BSP_USART2_Init(uint32_t BaudRate)
{
	USART_InitTypeDef   USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(USART2_TX_GPIO_CLK | USART2_RX_GPIO_CLK,ENABLE);
			/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;  
	GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;
	GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(USART2_TX_GPIO_PORT, USART2_TX_PINSOURCE, GPIO_AF_USART2);
	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(USART2_RX_GPIO_PORT, USART2_RX_PINSOURCE, GPIO_AF_USART2);

	USART_InitStructure.USART_BaudRate           = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);

	USART2_RXDMA_Config((uint32_t)Usart2Buffer,26);

	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
	/* 使能串口空闲中断 */
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}
/******************************************************************************/

void BSP_USART3_Init(uint32_t BaudRate)
{
	USART_InitTypeDef   USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(USART3_TX_GPIO_CLK | USART3_RX_GPIO_CLK,ENABLE);
			/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = USART3_TX_Pin;  
	GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = USART3_RX_Pin;
	GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(USART3_TX_GPIO_PORT, USART3_TX_PINSOURCE, GPIO_AF_USART3);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(USART3_RX_GPIO_PORT, USART3_RX_PINSOURCE, GPIO_AF_USART3);
	
	USART_InitStructure.USART_BaudRate           = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART3, &USART_InitStructure);

	USART3_RXDMA_Config((uint32_t)Usart3Buffer,26);

	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
	/* 使能串口空闲中断 */
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART3, ENABLE);
}
/******************************************************************************/

void USART_sendChar(USART_TypeDef* USARTx, char ch)
{
	/* 发送一个字节数据到串口 */
	USART_SendData(USARTx, (uint8_t) ch);
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
}



#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
	USART2->DR = (u8) ch;      
	return ch;
}
#endif 


