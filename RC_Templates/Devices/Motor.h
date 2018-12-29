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
#include "pid.h"
/******************************************************************************/
typedef struct
{
	uint16_t realAngle;			/*机械角度*/
	 int16_t realSpeed;			/*实际速度*/
	 int16_t realCurrent;		/*实际电流*/
	 uint8_t temperture;		/*电机温度*/
	
   int16_t targetCurrent;	/*目标电流*/
	 int16_t targetSpeed;		/*目标速度*/
	uint16_t targetAngle;		/*目标角度*/

}M3508_t;


typedef struct
{
	uint16_t realAngle;			/*机械角度*/
	int16_t  realSpeed;			/*实际速度*/
	int16_t  realCurrent;		/*实际电流*/
	uint8_t  temperture;		/*电机温度*/
	
   int16_t targetCurrent;	/*目标电流*/
	 int16_t targetSpeed;		/*目标速度*/
	uint16_t targetAngle;		/*目标角度*/

}M2006_t;


typedef struct
{
	uint16_t realAngle;			/*机械角度*/
	 int16_t realCurrent;		/*实际电流*/
	 uint8_t temperture;		/*电机温度*/
	
   int16_t targetCurrent;	/*目标电流*/
	uint16_t targetAngle;		/*目标角度*/

}M6623_t;


typedef struct
{
	uint16_t realAngle;			/*机械角度*/
	 int16_t realSpeed;			/*实际速度*/
	 int16_t realCurrent;		/*实际电流*/
	 uint8_t temperture;		/*电机温度*/
	
   int16_t targetCurrent;	/*目标电流*/
	uint16_t targetSpeed;		/*目标速度*/
	uint16_t targetAngle;		/*目标角度*/
	
     pid_t OutPID;				/*外环PID*/
	   pid_t InPID;					/*内环PID*/
}M6020_t;

typedef enum
{
	CAN_1   =1,
	CAN_2   =2
}CANx_e;
/******************************************************************************/

#define M3508_ID_START	0x201
#define M3508_ID_END	  0x204

#define M6623_ID_START	0x205
#define M6623_ID_END	  0x206

#define M6020_ID_START	0x205
#define M6020_ID_END	  0x208
/******************************************************************************/
void M3508_DataDecode(CanRxMsg RxMessage);
void M6020_DataDecode(CanRxMsg RxMessage);
void MotorParamInit(void);
void M6020_setCurrent(CANx_e CANx);


extern M3508_t M3508[4];
extern M6623_t M6623[2];
extern M6020_t M6020[2];
extern M2006_t M2006[4];
/******************************************************************************/
#endif


 

