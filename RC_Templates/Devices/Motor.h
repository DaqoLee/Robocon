/*
 *******************************************************************************
 * @file    Motor.h
 * @author  Daqo Lee
 * @version V1.1
 * @date    2019/1/1
 * @brief   
 *
 *******************************************************************************
 * @attention
 *
 *******************************************************************************
 */

#ifndef __MOTOR_H_
#define __MOTOR_H_
#include "stm32f4xx.h"
#include "pid.h"
/******************************************************************************/

typedef enum
{
	CAN_1   =1,
	CAN_2   =2
}CANx_e;

typedef enum
{
  LF =1,
	RF,
	RB,
	LB
	}M6020x_e;

typedef struct
{
	#define M3508_ID_START	0x201
  #define M3508_ID_END	  0x204
	
	uint16_t realAngle;			/*实际角度*/
	 int16_t realSpeed;			/*实际速度*/
	 int16_t realCurrent;		/*实际电流*/
	 uint8_t temperture;		/*实际温度*/
	
   int16_t targetCurrent;	/*目标电流*/
	 int16_t targetSpeed;		/*目标速度*/
	uint16_t targetAngle;		/*目标角度*/

}M3508_t;


typedef struct
{
	#define M2006_ID_START	0x201
  #define M2006_ID_END	  0x204
	
	uint16_t realAngle;			/*实际角度*/
	int16_t  realSpeed;			/*实际速度*/
	int16_t  realCurrent;		/*实际电流*/
	uint8_t  temperture;		/*实际温度*/
	
   int16_t targetCurrent;	/*目标电流*/
	 int16_t targetSpeed;		/*目标速度*/
	uint16_t targetAngle;		/*目标角度*/

}M2006_t;


typedef struct
{
	#define M6623_ID_START	0x205
  #define M6623_ID_END	  0x206

	#define M6020_MEDIAN   4000
	#define M6020_RANGE    3000

//	#define M6020_MEDIAN(n)  (M6020_MEDIAN_##n)
//	#define M6020_RANGE(n)   (M6020_RANGE_##(M6020x_e)n)

	uint16_t realAngle;			
	 int16_t realCurrent;		 
	 uint8_t temperture;		
	
   int16_t targetCurrent;	
	uint16_t targetAngle;		

}M6623_t;

typedef struct
{
	
	#define M6020_ID_START	0x205
  #define M6020_ID_END	  0x208
	
	uint16_t realAngle;			
	 int16_t realSpeed;			
	 int16_t realCurrent;	
	 uint8_t temperture;		
	
   int16_t targetCurrent;	
	uint16_t targetSpeed;		
	uint16_t targetAngle;		
	
     pid_t OutPID;				/*外环PID*/
	   pid_t InPID;					/*内环PID*/
	
	
}M6020_t;

typedef struct
{
	M3508_t M3508[4];
  M6623_t M6623[2];
  M6020_t M6020[4];
  M2006_t M2006[4];
	
  void (*p_M6020setCur)	(CANx_e CANx);
	void (*p_M3508setCur)	(CANx_e CANx);
	void (*p_M2006setCur)	(CANx_e CANx);
	
	void (*p_M6020setTarAngle)(float Ratio ,uint8_t Motor_ID, int16_t DR16_chx);
	
	void (*p_M6020getMsg) (CanRxMsg RxMessage);
	void (*p_M3508getMsg) (CanRxMsg RxMessage);
	void (*p_M2006getMsg) (CanRxMsg RxMessage);
	void (*p_M6623getMsg) (CanRxMsg RxMessage);
	
}Motor_t;
/******************************************************************************/


extern Motor_t Motor;

void MotorParamInit(void);

/******************************************************************************/
#endif


 

