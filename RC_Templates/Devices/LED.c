/**
  ************************************* Copyright ****************************** 
  *
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *                              
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *    
  * FileName   : LED.c   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-11         
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
#include "LED.h"

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    LED_Init
  * @brief  
  * @param   None
  * @retval
  * @author  Daqo Lee 
  * @Data    2018-12-11
  * 1. ...
  * <modify staff>:
  * <data>        :
  * <description> :
  * 2. ...
 **/
/* -------------------------------- end -------------------------------- */

void LED_Init(void)
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
	GPIO_WriteBit(LED0_GPIO_PORT,LED0_PIN|LED1_PIN|LED2_PIN|LED3_PIN\
                              |LED4_PIN|LED5_PIN|LED6_PIN,Bit_SET);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
  GPIO_InitStructure.GPIO_Pin =LED_R_PIN|LED_G_PIN;
  GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStructure);
	GPIO_WriteBit(LED_R_GPIO_PORT,LED_R_PIN|LED_G_PIN,Bit_SET);
															 

}



