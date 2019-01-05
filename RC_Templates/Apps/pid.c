#include "pid.h"

void absLimit(float *a, float ABS_MAX)
{
	if(*a > ABS_MAX)
			*a = ABS_MAX;
	if(*a < -ABS_MAX)
			*a = -ABS_MAX;
}

/******************************************************************************/
/*参数初始化*/
static void pidParamInit(
    pid_t *pid, 
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,
    float 	kp, 
    float 	ki, 
    float 	kd)
{
	
	pid->integralLimit = intergral_limit;
	pid->maxOutput = maxout;
	pid->pidMode = mode;
	
	pid->P = kp;
	pid->I = ki;
	pid->D = kd;
    	
}


static void pidReset(pid_t	*pid, float kp, float ki, float kd)
{
    pid->P = kp;
    pid->I = ki;
    pid->D = kd;
}

/******************************************************************************/
float PID_Calc(pid_t* pid, float get, float set)
{
		
    pid->get[NOW] = get;
    pid->set[NOW] = set;
    pid->err[NOW] = set - get;	//set - measure
    if (pid->maxErr != 0 && ABS(pid->err[NOW]) >  pid->maxErr  )
		  return 0;
  	if (pid->deadband != 0 && ABS(pid->err[NOW]) < pid->deadband)
		  return 0;
    
    if(pid->pidMode == POSITION_PID) //位置式P
    {	
      
      pid->Pout = pid->P * pid->err[NOW];
      pid->Iout += pid->I * pid->err[NOW];
      pid->Dout = pid->D * (pid->err[NOW] - pid->err[LAST] );
		 
      absLimit(&(pid->Iout), pid->integralLimit);

	  pid->posOut = pid->Pout + pid->Iout + pid->Dout;
			
      absLimit(&(pid->posOut), pid->maxOutput);
      pid->lastPosOut = pid->posOut;	//update last time 
    }
    else if(pid->pidMode == DELTA_PID)//增量式P
    {
	  pid->Pout = pid->P * (pid->err[NOW] - pid->err[LAST]);
	  pid->Iout = pid->I * pid->err[NOW];
	  pid->Dout = pid->D * (pid->err[NOW] - 2*pid->err[LAST] + pid->err[LLAST]);
			
	  absLimit(&(pid->Iout), pid->integralLimit);
	  pid->deltaU = pid->Pout + pid->Iout + pid->Dout;
	
	  pid->deltaOut = pid->lastDeltaOut + pid->deltaU;
	  absLimit(&(pid->deltaOut), pid->maxOutput);
	  pid->lastDeltaOut = pid->deltaOut;	//update last time
    }
    
    pid->err[LLAST] = pid->err[LAST];
    pid->err[LAST] = pid->err[NOW];
	
    pid->get[LLAST] = pid->get[LAST];
    pid->get[LAST] = pid->get[NOW];
	
    pid->set[LLAST] = pid->set[LAST];
    pid->set[LAST] = pid->set[NOW];
    return pid->pidMode==POSITION_PID ? pid->posOut : pid->deltaOut;
}

void PID_StructInit(
    pid_t* pid,
    uint32_t mode,
    uint32_t maxout,
    uint32_t intergral_limit,
    
    float 	kp, 
    float 	ki, 
    float 	kd)
{
	/*init function pointer*/
	pid->f_ParamInit = pidParamInit;
	pid->f_PID_Reset = pidReset;
	/*init pid param */
	pid->f_ParamInit(pid, mode, maxout, intergral_limit, kp, ki, kd);
	
}

/******************************************************************************/

