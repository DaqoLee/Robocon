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



#ifndef __TASK__CAN_H_
#define __TASK__CAN_H_
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "BSP_CAN.h"
/******************************************************************************/
extern QueueHandle_t xCanSendQueue;
extern QueueHandle_t xCan1RxQueue ;
extern QueueHandle_t xCan2RxQueue ;
/******************************************************************************/
void CanTaskCreate(void);
/******************************************************************************/
#endif


 

