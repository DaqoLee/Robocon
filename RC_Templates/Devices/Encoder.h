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
			float realZ_Angle;																		
			float realX_Angle;
			float realY_Angle;
			float realX_Coords;
			float realY_Coords;
			float realOmega;
		};
		float targetZ_Angle;																		
		float targetX_Angle;
		float targetY_Angle;
		float targetX_Coords;
		float targetY_Coords;
		float targetOmega;
	}; 
	
}Posture_t;	


extern Posture_t Posture;
void Posture_getMessage(uint8_t *EncoderBuf);
#endif


 

