/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : Task_CanSend.h   
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



#ifndef __TASK__CAN_SEND_H_
#define __TASK__CAN_SEND_H_
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "BSP_CAN.h"


void vTaskCanSend(void *Parameters);
void vTaskCan1Receive(void *pvParameters);


extern TaskHandle_t xHandleCan1Receive ;
extern TaskHandle_t xHandleCanSend ;
static void CAN1_DataDecoding(CanRxMsg rxMessage);
#endif


 

