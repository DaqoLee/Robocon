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
	
	float set[3];				
	float get[3];				
	float err[3];			
	float erc[3];
	
	float Pout;						
	float Iout;						
	float Dout;						
	
	float posOut;						
	float lastPosOut;				  
	float deltaU;						
	float deltaOut;					
	float lastDeltaOut;
    
	float maxErr;
	float deadband;				

	uint16_t maxInput;
	uint16_t errRange;
	uint32_t pidMode;
	uint32_t maxOutput;				
	uint32_t integralLimit;		
    
	void (*f_ParamInit)(struct __pid_t *pid,  
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


 

