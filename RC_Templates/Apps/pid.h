/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : pid.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-27         
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



#ifndef __PID_H_
#define __PID_H_
#include "stm32f4xx.h"


#define ABS(x)		((x>0)? (x): (-x)) 
enum{
    LLAST	= 0,
    LAST 	= 1,
    NOW 	= 2,
    
    POSITION_PID,
    DELTA_PID,
};
typedef struct __pid_t
{
	float P;
	float I;
	float D;
	
	float set[3];				//�?标�?,包含NOW�? LAST�? LLAST上上�?
	float get[3];				//测量�?
	float err[3];				//�?�?
	float erc[3];
	
	float Pout;							//p输出
	float Iout;							//i输出
	float Dout;							//d输出
	
	float posOut;						//�?次位�?式输�?
	float lastPosOut;				  //上�?�输�?
	float deltaU;						//�?次�?�量�?
	float deltaOut;					//�?次�?�量式输�? = last_delta_out + delta_u
	float lastDeltaOut;
    
	float maxErr;
	float deadband;				//err < deadband return
	uint32_t pidMode;
	uint32_t maxOutput;				//输出限幅
	uint32_t integralLimit;		//�?分限�?
    
	void (*f_ParamInit)(struct __pid_t *pid,  //PID参数初�?�化
									uint32_t pid_mode,
									uint32_t maxOutput,
									uint32_t integralLimit,
									float p,
									float i,
									float d);
	void (*f_PID_Reset)(struct __pid_t *pid, float p, float i, float d);

}pid_t;

void PID_StructInit(
    pid_t* pid,
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,
    
    float 	kp, 
    float 	ki, 
    float 	kd);
    
float PID_Calc(pid_t* pid, float fdb, float ref);
	
#endif


 

