/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : Joint.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-29         
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



#ifndef __JOINT_H_
#define __JOINT_H_
#include "stm32f4xx.h"

/******************************************************************************/


void Thigh_M6020Ctrl(void);
void Joint_MotionModel(int16_t Vx, int16_t Vy, int16_t Omega);

#endif


 

