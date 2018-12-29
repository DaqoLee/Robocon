/**
  ************************************* Copyright ****************************** 
  *
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *                              
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *    
  * FileName   : main.c   
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

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Task_Init.h"

/******************************************************************************/


int main(void)
{	
  /* 创建开始任务 */
	xTaskCreate(vTaskStart,           /* 任务函数  */        
					  	"vTaskStart",         /* 任务名    */      
						  512,       			      /* 任务栈大小*/  
						  NULL,                 /* 任务参数  */    
					  	1,       			        /* 任务优先级*/
					  	&StartTaskHandler);   /* 任务句柄  */ 
	
  /* 启动调度，开始执行任务 */
	vTaskStartScheduler();            
}


/******************************************************************************/

