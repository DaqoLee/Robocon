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
  BSP_LED_GPIOInit();
	GPIO_WriteBit(LED0_GPIO_PORT,LED0_PIN|LED1_PIN|LED2_PIN|LED3_PIN\
                              |LED4_PIN|LED5_PIN|LED6_PIN,Bit_SET);

	GPIO_WriteBit(LED_R_GPIO_PORT,LED_R_PIN|LED_G_PIN,Bit_SET);
															 
}



