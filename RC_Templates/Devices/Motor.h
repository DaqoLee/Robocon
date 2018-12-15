/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : Motor.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-14         
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



#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "stm32f4xx.h"
/******************************************************************************/
typedef struct
{
	uint16_t realAngle;			//读回来的机械角度
	 int16_t realSpeed;			//读回来的速度
	 int16_t realCurrent;		//读回来的实际电流
	 uint8_t temperture;			//读回来的电机温度
	
   int16_t targetCurrent;			//目标电流
	 int16_t targetSpeed;			//目标速度
	uint16_t targetAngle;			//目标角度

}M3508_t;


typedef struct
{
	uint16_t realAngle;			//读回来的机械角度
	 int16_t realSpeed;			//读回来的速度
	 int16_t realCurrent;		//读回来的实际电流
	 uint8_t temperture;			//读回来的电机温度
	
   int16_t targetCurrent;			//目标电流
	 int16_t targetSpeed;			//目标速度
	uint16_t targetAngle;			//目标角度

}M2006_t;


typedef struct
{
	uint16_t realAngle;			//读回来的机械角度
	 int16_t realCurrent;		//读回来的实际电流
	 uint8_t temperture;			//读回来的电机温度
	
   int16_t targetCurrent;			//目标电流
	uint16_t targetAngle;			//目标角度

}M6623_t;


typedef struct
{
	uint16_t realAngle;			//读回来的机械角度
	 int16_t realCurrent;		//读回来的实际电流
	 uint8_t temperture;			//读回来的电机温度
	
   int16_t targetCurrent;			//目标电流
	uint16_t targetAngle;			//目标角度

}M6020_t;
/******************************************************************************/

#define M3508_ID_START	0x201
#define M3508_ID_END	  0x204

#define M6623_ID_START	0x205
#define M6623_ID_END	  0x206

/******************************************************************************/
void M3508_DataDecode(CanRxMsg RxMessage);

/******************************************************************************/
#endif


 

