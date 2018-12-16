#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H
#include "stm32f4xx.h"

/******************************************************************************/
#define LED_R_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define LED_R_PIN                 GPIO_Pin_4
#define LED_R_GPIO_PORT           GPIOB

#define LED_G_GPIO_CLK            RCC_AHB1Periph_GPIOB
#define LED_G_PIN                 GPIO_Pin_5
#define LED_G_GPIO_PORT           GPIOB

#define LED0_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED0_PIN                  GPIO_Pin_9
#define LED0_GPIO_PORT            GPIOE

#define LED1_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED1_PIN                  GPIO_Pin_10
#define LED1_GPIO_PORT            GPIOE

#define LED2_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED2_PIN                  GPIO_Pin_11
#define LED2_GPIO_PORT            GPIOE

#define LED3_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED3_PIN                  GPIO_Pin_12
#define LED3_GPIO_PORT            GPIOE

#define LED4_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED4_PIN                  GPIO_Pin_13
#define LED4_GPIO_PORT            GPIOE

#define LED5_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED5_PIN                  GPIO_Pin_14
#define LED5_GPIO_PORT            GPIOE

#define LED6_GPIO_CLK             RCC_AHB1Periph_GPIOE
#define LED6_PIN                  GPIO_Pin_15
#define LED6_GPIO_PORT            GPIOE

/********USART1_Pin_define*****************************************************/
#define USART1_TX_GPIO_CLK      RCC_AHB1Periph_GPIOB
#define USART1_TX_GPIO_PORT     GPIOB
#define USART1_TX_Pin          	GPIO_Pin_6
#define USART1_TX_PINSOURCE			GPIO_PinSource6

#define USART1_RX_GPIO_CLK      RCC_AHB1Periph_GPIOB
#define USART1_RX_GPIO_PORT     GPIOB
#define USART1_RX_Pin           GPIO_Pin_7
#define USART1_RX_PINSOURCE			GPIO_PinSource7
/********USART1_Pin_define_END********/

/********USART2_Pin_define*****************************************************/
#define USART2_TX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART2_TX_GPIO_PORT      GPIOD
#define USART2_TX_Pin          	 GPIO_Pin_5
#define USART2_TX_PINSOURCE			 GPIO_PinSource5

#define USART2_RX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART2_RX_GPIO_PORT      GPIOD
#define USART2_RX_Pin            GPIO_Pin_6
#define USART2_RX_PINSOURCE			 GPIO_PinSource6
/********USART2_Pin_define_END********/

/********USART3_Pin_define*****************************************************/
#define USART3_TX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART3_TX_GPIO_PORT      GPIOD
#define USART3_TX_Pin          	 GPIO_Pin_8
#define USART3_TX_PINSOURCE			 GPIO_PinSource8

#define USART3_RX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART3_RX_GPIO_PORT      GPIOD
#define USART3_RX_Pin            GPIO_Pin_9
#define USART3_RX_PINSOURCE			 GPIO_PinSource9
/********USART3_Pin_define_END********/

/********UART4_Pin_define*****************************************************/
#define UART4_TX_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define UART4_TX_GPIO_PORT        GPIOA
#define UART4_TX_Pin          	 	GPIO_Pin_0
#define UART4_TX_PINSOURCE			  GPIO_PinSource0

#define UART4_RX_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define UART4_RX_GPIO_PORT        GPIOA
#define UART4_RX_Pin           		GPIO_Pin_1
#define UART4_RX_PINSOURCE			  GPIO_PinSource1
/********UART4_Pin_define_END********/
/********USART6_Pin_define*****************************************************/
#define USART6_TX_GPIO_CLK        RCC_AHB1Periph_GPIOG
#define USART6_TX_GPIO_PORT       GPIOG
#define USART6_TX_Pin          	 	GPIO_Pin_14
#define USART6_TX_PINSOURCE			  GPIO_PinSource14

#define USART6_RX_GPIO_CLK        RCC_AHB1Periph_GPIOG
#define USART6_RX_GPIO_PORT       GPIOG
#define USART6_RX_Pin           	GPIO_Pin_9
#define USART6_RX_PINSOURCE			  GPIO_PinSource9
/********USART6_Pin_define_END********/

/********CAN1_Pin_define*****************************************************/
#define CAN1_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOD
#define CAN1_RX_GPIO_PORT           GPIOD
#define CAN1_RX_Pin           		  GPIO_Pin_0
#define CAN1_RX_PINSOURCE		      	GPIO_PinSource0

#define CAN1_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOD
#define CAN1_TX_GPIO_PORT           GPIOD
#define CAN1_TX_Pin          	     	GPIO_Pin_1
#define CAN1_TX_PINSOURCE		      	GPIO_PinSource1

/********CAN1_Pin_define*****************************************************/
#define CAN2_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOB
#define CAN2_RX_GPIO_PORT           GPIOB
#define CAN2_RX_Pin           	  	GPIO_Pin_12
#define CAN2_RX_PINSOURCE			      GPIO_PinSource12

#define CAN2_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOB
#define CAN2_TX_GPIO_PORT           GPIOB
#define CAN2_TX_Pin          	 	    GPIO_Pin_13
#define CAN2_TX_PINSOURCE		      	GPIO_PinSource13


/******************************************************************************/
void BSP_LED_GPIOInit(void);
void BSP_USART1_GPIOInit(void);
void BSP_USART2_GPIOInit(void);
void BSP_USART3_GPIOInit(void);
void BSP_UART4_GPIOInit(void);
void BSP_UART6_GPIOInit(void);

void BSP_CAN1_GPIOInit(void);
void BSP_CAN2_GPIOInit(void);
/******************************************************************************/
#endif

