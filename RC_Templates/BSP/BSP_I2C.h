/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : BSP_I2C.h   
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



#ifndef __BSP__I2C_H_
#define __BSP__I2C_H_
#include "stm32f4xx.h"
#include "BSP_GPIO.h"

void BSP_I2C2_Init(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);

#endif


 

