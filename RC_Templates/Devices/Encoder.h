/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : Encoder.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-30         
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



#ifndef __ENCODER_H_
#define __ENCODER_H_
#include "stm32f4xx.h"

#pragma anon_unions
typedef struct
{																					
	union
	{
		uint8_t DataBuff[24];
		struct
		{
			float Z_Angle;																		
			float X_Angle;
			float Y_Angle;
			float X_Position;
			float Y_position;
			float Omega;
		};
	
	}; 
}Posture_t;	
#endif


 

