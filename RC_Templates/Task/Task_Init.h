/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : Task_Init.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-16         
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



#ifndef __TASK__INIT_H_
#define __TASK__INIT_H_
#include "stm32f4xx.h"
#include "LED.h"
#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t StartTaskHandler;

void vTaskStart(void *pvParameters);


#endif


 

