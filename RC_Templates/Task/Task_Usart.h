/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : Task_Usart.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-14         
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



#ifndef __TASK__USART_H_
#define __TASK__USART_H_
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
/******************************************************************************/

extern QueueHandle_t xUsart1RxQueue;
extern QueueHandle_t xUsart2RxQueue;
extern QueueHandle_t xUsart3RxQueue;

void UsartTaskCreate(void);
/******************************************************************************/
#endif


 

