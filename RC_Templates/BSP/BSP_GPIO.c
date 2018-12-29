#include "BSP_GPIO.h"

/******************************************************************************/
void BSP_LED_GPIOInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(LED_R_GPIO_CLK|LED0_GPIO_CLK, ENABLE);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
  GPIO_InitStructure.GPIO_Pin =LED0_PIN|LED1_PIN|LED2_PIN|LED3_PIN\
                              |LED4_PIN|LED5_PIN|LED6_PIN;
  GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);

	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
  GPIO_InitStructure.GPIO_Pin =LED_R_PIN|LED_G_PIN;
  GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStructure);

}
/******************************************************************************/
void BSP_KEY_GPIOInit(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_AHB1PeriphClockCmd(KEY_GPIO_CLK, ENABLE); 		
	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_InitStructure.GPIO_Pin   = KEY_PIN;	 
	
	GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);	

}
/******************************************************************************/
void BSP_USART1_GPIOInit(void)
{
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
}

/******************************************************************************/
void BSP_USART2_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
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
}

/******************************************************************************/
void BSP_USART3_GPIOInit(void)
{
	
}

/******************************************************************************/
void BSP_UART4_GPIOInit(void)
{
	
}
/******************************************************************************/
void BSP_UART6_GPIOInit(void)
{
	
}

/******************************************************************************/
void BSP_CAN1_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(CAN1_RX_GPIO_CLK | CAN1_TX_GPIO_CLK, ENABLE);
		/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = CAN1_TX_Pin;  
	GPIO_Init(CAN1_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = CAN1_RX_Pin;
	GPIO_Init(CAN1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(CAN1_TX_GPIO_PORT, CAN1_TX_PINSOURCE, GPIO_AF_CAN1);
	GPIO_PinAFConfig(CAN1_RX_GPIO_PORT, CAN1_RX_PINSOURCE, GPIO_AF_CAN1);
}

/******************************************************************************/
void BSP_CAN2_GPIOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(CAN2_RX_GPIO_CLK | CAN2_TX_GPIO_CLK, ENABLE);
		/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = CAN2_TX_Pin;  
	GPIO_Init(CAN2_TX_GPIO_PORT, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = CAN2_RX_Pin;
	GPIO_Init(CAN2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(CAN2_TX_GPIO_PORT, CAN2_TX_PINSOURCE, GPIO_AF_CAN2);
	GPIO_PinAFConfig(CAN2_RX_GPIO_PORT, CAN2_RX_PINSOURCE, GPIO_AF_CAN2);
}
/******************************************************************************/
void BSP_I2C2_GPIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	RCC_APB1PeriphClockCmd(I2C2_SDA_GPIO_CLK|I2C2_SCL_GPIO_CLK,ENABLE);
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;    /*I2C必须开漏输出*/
	
	GPIO_InitStructure.GPIO_Pin   =  I2C2_SCL_Pin|I2C2_SDA_Pin ;
	GPIO_Init(I2C2_SCL_GPIO_PORT, &GPIO_InitStructure);
	
//	GPIO_PinAFConfig(I2C2_SDA_GPIO_PORT, I2C2_SDA_PINSOURCE, GPIO_AF_I2C2);
//	GPIO_PinAFConfig(I2C2_SCL_GPIO_PORT, I2C2_SCL_PINSOURCE, GPIO_AF_I2C2);
}

/******************************************************************************/

