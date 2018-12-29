/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : BSP_CAN.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-12         
  * Description:    
  * Function List:  
  	1. ....
  	   <version>: 		
  <modify staff>:
  		  <data>:
   <description>:  
  	2. ...
  ******************************************************************************
 */



#ifndef __BSP_CAN_H_
#define __BSP_CAN_H_

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "BSP_GPIO.h"

/******************************************************************************/
typedef struct
{
  uint8_t     CANx;               /*1：CAN1  2：CAN2*/
  CanTxMsg    SendCanTxMsg;       /*要发送的数据*/
}CanSend_t;

/******************************************************************************/
#define CAN1_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOD
#define CAN1_RX_GPIO_PORT           GPIOD
#define CAN1_RX_Pin           		  GPIO_Pin_0
#define CAN1_RX_PINSOURCE		      	GPIO_PinSource0

#define CAN1_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOD
#define CAN1_TX_GPIO_PORT           GPIOD
#define CAN1_TX_Pin          	     	GPIO_Pin_1
#define CAN1_TX_PINSOURCE		      	GPIO_PinSource1


#define CAN2_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOB
#define CAN2_RX_GPIO_PORT           GPIOB
#define CAN2_RX_Pin           	  	GPIO_Pin_12
#define CAN2_RX_PINSOURCE			      GPIO_PinSource12

#define CAN2_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOB
#define CAN2_TX_GPIO_PORT           GPIOB
#define CAN2_TX_Pin          	 	    GPIO_Pin_13
#define CAN2_TX_PINSOURCE		      	GPIO_PinSource13
/******************************************************************************/


void BSP_CAN1_Init(void);
void BSP_CAN2_Init(void);
/******************************************************************************/
#endif


 

