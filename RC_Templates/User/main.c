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
  /* ������ʼ���� */
	xTaskCreate(vTaskStart,           /* ������  */        
					  	"vTaskStart",         /* ������    */      
						  512,       			      /* ����ջ��С*/  
						  NULL,                 /* �������  */    
					  	1,       			        /* �������ȼ�*/
					  	&StartTaskHandler);   /* ������  */ 
	
  /* �������ȣ���ʼִ������ */
	vTaskStartScheduler();            
}


/******************************************************************************/

