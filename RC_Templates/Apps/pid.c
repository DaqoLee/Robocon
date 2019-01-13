#include "pid.h"

void absLimit(float *a, float ABS_MAX)
{
	if(*a > ABS_MAX)
			*a = ABS_MAX;
	if(*a < -ABS_MAX)
			*a = -ABS_MAX;
}

/******************************************************************************/
/*������ʼ��*/
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

/*------------------------------80 Chars Limit--------------------------------*/
  /**
  * @Data    2019-01-13 19:13
  * @brief   
  * @param   void
  * @retval  void
  */
static void LinearQuantization(pid_t* pid, float get, float set ,float *p_Value)
{
  pid->err[NOW] = set - get;	//set - measure
  pid->erc[NOW] = pid->err[NOW] - pid->err[LAST];


  p_Value[0]=6.0f*pid->err[NOW]/pid->errRange;
  p_Value[1]=3.0f*pid->erc[NOW]/pid->errRange;

  pid->err[LAST] = pid-> err[NOW];
  pid->erc[LAST] = pid-> err[NOW];
}

/*------------------------------80 Chars Limit--------------------------------*/
  /**
  * @Data    2019-01-13 19:13
  * @brief   
  * @param   void
  * @retval  void
  */
static void CalcMembership(pid_t* pid, float get, float set ,float *p_Value)
{
  
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
    
    if(pid->pidMode == POSITION_PID) //λ��ʽP
    {	
      if(pid->err[NOW] < 0)
        pid->err[NOW] = ABS(pid->err[NOW]) > ABS(pid->maxInput - ABS(pid->err[NOW])) \
        ? pid->maxInput - ABS(pid->err[NOW]):pid->err[NOW];
      else if(pid->err[NOW]>0)
        pid->err[NOW] = ABS(pid->err[NOW])>ABS(pid->maxInput - ABS(pid->err[NOW])) \
        ? ABS(pid->err[NOW]) - pid->maxInput:pid->err[NOW];
      
      pid->Pout = pid->P * pid->err[NOW];
      pid->Iout += pid->I * pid->err[NOW];
      pid->Dout = pid->D * (pid->err[NOW] - pid->err[LAST] );
		 
      absLimit(&(pid->Iout), pid->integralLimit);

	  pid->posOut = pid->Pout + pid->Iout + pid->Dout;
			
      absLimit(&(pid->posOut), pid->maxOutput);
      pid->lastPosOut = pid->posOut;	//update last time 
    }
    else if(pid->pidMode == DELTA_PID)//����ʽP
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

