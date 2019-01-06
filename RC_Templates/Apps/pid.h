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
	
	float set[3];				//ç›?æ ‡å€?,åŒ…å«NOWï¼? LASTï¼? LLASTä¸Šä¸Šæ¬?
	float get[3];				//æµ‹é‡å€?
	float err[3];				//è¯?å·?
	float erc[3];
	
	float Pout;							//pè¾“å‡º
	float Iout;							//iè¾“å‡º
	float Dout;							//dè¾“å‡º
	
	float posOut;						//æœ?æ¬¡ä½ç½?å¼è¾“å‡?
	float lastPosOut;				  //ä¸Šæ?¡è¾“å‡?
	float deltaU;						//æœ?æ¬¡å?é‡å€?
	float deltaOut;					//æœ?æ¬¡å?é‡å¼è¾“å‡? = last_delta_out + delta_u
	float lastDeltaOut;
    
	float maxErr;
	float deadband;				//err < deadband return
	uint32_t pidMode;
	uint32_t maxOutput;				//è¾“å‡ºé™å¹…
	uint32_t integralLimit;		//ç§?åˆ†é™å¹?
    
	void (*f_ParamInit)(struct __pid_t *pid,  //PIDå‚æ•°åˆå?‹åŒ–
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


 

