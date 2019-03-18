/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Joint.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-01-09               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Joint.h"
#include "Motor.h"
#include "Servo.h"
#include "DR16.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Curve.h"
#include "Filter.h" 
/*-------------------------- D E F I N E S -----------------------------------*/
float LH=0,RH=0,LFx=0,RFx=0;

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static int16_t Joint_getThighTarAng(int16_t TarAng ,float Phase,float Temp);
static int16_t Joint_getCrusTarAng(int16_t TarAng ,float Phase,float Temp);
/*------------------G L O B A L - F U N C T I O N S --------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-08 14:49
	* @brief   关节电机控制
	* @param   void
	* @retval  void
	*/
void Thigh_M6020Ctrl(void)
{
	Motor.p_M6020setTarAngle(0,-DR16.ch1);
	Motor.p_M6020setTarAngle(1,-DR16.ch1);
	Motor.p_M6020setTarAngle(2,-DR16.ch1);
	Motor.p_M6020setTarAngle(3,-DR16.ch1);
	
	for(uint8_t i=0;i<4;i++)
	{
		Motor.M6020[i].targetCurrent=PID_Calc(&Motor.M6020[i].OutPID, \
	         Motor.M6020[i].realAngle, Motor.M6020[i].targetAngle);
	}
	Motor.p_M6020setCur(CAN_1);  
}



/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   关节运动模型
	* @param   void
	* @retval  void
	*/
void Joint_MotionModel(int16_t Vx, int16_t Vy, int16_t Omega)
{	
	static float temp=0;
	if(Vx == 0 && Vy == 0 && Omega == 0)
		temp=0;
	else
	  temp=temp>2*PI?0:temp+0.04f;

	DXL1_setSyncMsg(USART_6,POSITION,12,
	                0x01,2648 + Joint_getThighTarAng(Vy,0,temp), /*LH*/               
						      0x02,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
									0x03,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
									0x04,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x05,2648 + Joint_getThighTarAng(Vy,0,temp), /*RF*/ 
									0x06,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
									0x07,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*LF*/ 
									0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x09,2648 + Joint_getThighTarAng(Omega + Vx,0,temp),
									0x0A,2648 + Joint_getThighTarAng(Omega + Vx,1.0f,temp),
									0x0B,2648 + Joint_getThighTarAng(Omega - Vx,0,temp),
									0x0C,2648 + Joint_getThighTarAng(Omega - Vx,1.0f,temp));
							 
//	vTaskDelay(5);	
	
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   关节运动模型
	* @param   void
	* @retval  void
	*/
void Joint_ThrMotionModel(int16_t Vx, int16_t Vy, int16_t Omega)
{	
	static float temp=0,tempLH=0,tempRH=0,tempRF=0,tempLF=0;
	if(Vx == 0 && Vy == 0 && Omega == 0)
	{
    temp=0;
	}
	else
	{
		temp=temp>4*PI?0:temp+0.04f;

		tempLH=tempLH>2*PI?0:tempLH;
		tempRH=tempRH>2*PI?0:tempRH;
		tempLF=tempLF>2*PI?0:tempLF;
		tempRF=tempRF>2*PI?0:tempRF;
	}
	  
	if(temp<0.5*PI)
	{
		tempLH+=0.04f;
		tempLF+=0.04f;
		tempRH+=0.04f;
		tempRF+=0.04f;

	}	
  else if((temp > 0.5*PI) && (temp < 1.5*PI))
	{
		tempRF+=0.04f;

	}
	else if((temp > 1.5*PI) && (temp < 2.5*PI))
	{
		tempRH+=0.04f;

	}
	else if((temp > 2.5*PI) && (temp < 3*PI))
	{
		tempLH+=0.04f;
		tempLF+=0.04f;
		tempRH+=0.04f;
		tempRF+=0.04f;

	}
	else if((temp > 3*PI) && (temp < 3.5*PI))
	{
		tempLF+=0.04f;

	}
	else if((temp > 3.5*PI) && (temp < 4*PI))
	{
		tempLH+=0.04f;

	}

  LFx=Joint_getThighTarAng(Vy,0.5f,tempLF);
	RFx=Joint_getThighTarAng(Vy,1.0f,tempRF);
	LH=Joint_getThighTarAng(Vy,0.5f,tempLH);
	RH=Joint_getThighTarAng(Vy,1.0f,tempRH);

//	DXL1_setSyncMsg(USART_6,POSITION,12,
//								0x01,2648 + Joint_getThighTarAng(Vy,0.5f,tempLH), /*LH*/               
//								0x02,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,tempLH),
//								
//								0x03,2648 + Joint_getThighTarAng(Vy,1.0f,tempRH), /*RH*/ 
//								0x04,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,tempRH),
//								
//								0x05,2648 + Joint_getThighTarAng(Vy,1.0f,tempRF), /*RF*/ 
//								0x06,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,tempRF),
//								
//								0x07,2648 + Joint_getThighTarAng(Vy,0.5f,tempLF), /*LF*/ 
//								0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,tempLF),
//								
//								0x09,2648 + Joint_getThighTarAng(Omega + Vx,0,temp),
//								0x0A,2648 + Joint_getThighTarAng(Omega + Vx,-0.5f,temp),
//								0x0B,2648 + Joint_getThighTarAng(Omega - Vx,0,temp),
//								0x0C,2648 + Joint_getThighTarAng(Omega - Vx,-0.5f,temp));
//	vTaskDelay(5);	
	
}


// /*------------------------------80 Chars Limit--------------------------------*/
// 	/**
// 	* @Data    2019-01-09 11:33
// 	* @brief   关节运动模型
// 	* @param   void
// 	* @retval  void
// 	*/
// void Joint_ThrMotionModel(int16_t Vx, int16_t Vy, int16_t Omega)
// {	
// 	static float temp=0,tempLH=0,tempRH=0,tempRF=0,tempLF=0;
// 	if(Vx == 0 && Vy == 0 && Omega == 0)
// 		temp=0;
// 	else
// 	  temp=temp>4*PI?0:temp+0.04f;
	
	
// 	if(temp<0.5*PI)
// 	{
// 		tempLH+=0.04f;
// 		tempLF+=0.04f;
// 		tempRH+=0.04f;
// 		tempRF+=0.04f;
		
// 		DXL1_setSyncMsg(USART_6,POSITION,12,
// 										0x01,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LH*/               
// 										0x02,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x03,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
// 										0x04,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x05,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RF*/ 
// 										0x06,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x07,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LF*/ 
// 										0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x09,2648 + Joint_getThighTarAng(Omega + Vx,0,temp),
// 										0x0A,2648 + Joint_getThighTarAng(Omega + Vx,-0.5f,temp),
// 										0x0B,2648 + Joint_getThighTarAng(Omega - Vx,0,temp),
// 										0x0C,2648 + Joint_getThighTarAng(Omega - Vx,-0.5f,temp));
// 	}	
//   else if((temp > 0.5*PI) && (temp < 1.5*PI))
// 	{
// 		tempRF+=0.04f;
		
// 		DXL1_setSyncMsg(USART_6,POSITION,12,
// 										0x01,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LH*/               
// 										0x02,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x03,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
// 										0x04,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x05,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RF*/ 
// 										0x06,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x07,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LF*/ 
// 										0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x09,2648 + Joint_getThighTarAng(Omega + Vx,0,temp),
// 										0x0A,2648 + Joint_getThighTarAng(Omega + Vx,-0.5f,temp),
// 										0x0B,2648 + Joint_getThighTarAng(Omega - Vx,0,temp),
// 										0x0C,2648 + Joint_getThighTarAng(Omega - Vx,-0.5f,temp));
// 	}
// 	else if((temp > 1.5*PI) && (temp < 2.5*PI))
// 	{
// 		tempRH+=0.04f;
		
// 		DXL1_setSyncMsg(USART_6,POSITION,12,
// 										0x01,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LH*/               
// 										0x02,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x03,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
// 										0x04,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x05,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RF*/ 
// 										0x06,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x07,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LF*/ 
// 										0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x09,2648 + Joint_getThighTarAng(Omega + Vx,0,temp),
// 										0x0A,2648 + Joint_getThighTarAng(Omega + Vx,-0.5f,temp),
// 										0x0B,2648 + Joint_getThighTarAng(Omega - Vx,0,temp),
// 										0x0C,2648 + Joint_getThighTarAng(Omega - Vx,-0.5f,temp));
// 	}
// 	else if((temp > 2.5*PI) && (temp < 3*PI))
// 	{
// 		tempLH+=0.04f;
// 		tempLF+=0.04f;
// 		tempRH+=0.04f;
// 		tempRF+=0.04f;
		
// 		DXL1_setSyncMsg(USART_6,POSITION,12,
// 										0x01,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LH*/               
// 										0x02,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x03,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
// 										0x04,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x05,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RF*/ 
// 										0x06,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x07,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LF*/ 
// 										0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x09,2648 + Joint_getThighTarAng(Omega + Vx,0,temp),
// 										0x0A,2648 + Joint_getThighTarAng(Omega + Vx,-0.5f,temp),
// 										0x0B,2648 + Joint_getThighTarAng(Omega - Vx,0,temp),
// 										0x0C,2648 + Joint_getThighTarAng(Omega - Vx,-0.5f,temp));
// 	}
// 	else if((temp > 3*PI) && (temp < 3.5*PI))
// 	{
// 		tempLF+=0.04f;

// 		DXL1_setSyncMsg(USART_6,POSITION,12,
// 										0x01,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LH*/               
// 										0x02,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x03,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
// 										0x04,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x05,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RF*/ 
// 										0x06,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x07,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LF*/ 
// 										0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x09,2648 + Joint_getThighTarAng(Omega + Vx,0,temp),
// 										0x0A,2648 + Joint_getThighTarAng(Omega + Vx,-0.5f,temp),
// 										0x0B,2648 + Joint_getThighTarAng(Omega - Vx,0,temp),
// 										0x0C,2648 + Joint_getThighTarAng(Omega - Vx,-0.5f,temp));
// 	}
// 	else if((temp > 3.5*PI) && (temp < 4*PI))
// 	{
// 		tempLH+=0.04f;

// 		DXL1_setSyncMsg(USART_6,POSITION,12,
// 										0x01,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LH*/               
// 										0x02,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x03,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
// 										0x04,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x05,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*RF*/ 
// 										0x06,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.1f,temp),
										
// 										0x07,2648 + Joint_getThighTarAng(Vy,0.5f,temp), /*LF*/ 
// 										0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.75f,temp),
										
// 										0x09,2648 + Joint_getThighTarAng(Omega + Vx,0,temp),
// 										0x0A,2648 + Joint_getThighTarAng(Omega + Vx,-0.5f,temp),
// 										0x0B,2648 + Joint_getThighTarAng(Omega - Vx,0,temp),
// 										0x0C,2648 + Joint_getThighTarAng(Omega - Vx,-0.5f,temp));
// 	}
// //	vTaskDelay(5);	
	
// }

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-03-06 15:31
	* @brief   关节控制状态机
	* @param   void
	* @retval  void
	*/
	void Joint_StateMachine(void)
	{
		static uint8_t temp=0;

		switch (temp)
		{
			case 1:/*状态1 对角步态往沙丘*/
				Joint_MotionModel(DR16.ch1,DR16.ch2,DR16.ch3);
				break;
			case 2:/*状态2 三角步态过沙丘*/
        Joint_ThrMotionModel(DR16.ch1,200,DR16.ch3);
				break;
			case 3:/*状态3 对角步态往草地*/
				Joint_MotionModel(DR16.ch1,DR16.ch2,DR16.ch3);
				break;
			case 4:/*状态4 三角步态过草地*/
				Joint_ThrMotionModel(DR16.ch1,200,DR16.ch3);
				break;
			case 5:/*状态5 转弯等待上坡信号*/
				Joint_ThrMotionModel(DR16.ch1,200,DR16.ch3);
				break;
			case 6:/*状态6 对角步态上坡*/
				Joint_MotionModel(DR16.ch1,DR16.ch2,DR16.ch3);
				break;		
			case 7:/*状态7 举起令牌*/
				Joint_MotionModel(0,0,0);
			  Joint_RobotArm(2600,2600);
				break;
			default:

				break;
		}

	}


/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-03-06 15:31
	* @brief   机械臂控制
	* @param   UpperarmTarang:上臂目标值、ForearmTarang ：前臂目标值
	* @retval  void
	*/
void Joint_RobotArm(uint16_t UpperarmTarang,uint16_t ForearmTarang)
{
	DXL1_setSyncMsg(USART_6,POSITION,2,0x0E,UpperarmTarang,0x0F,ForearmTarang);
}
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-03-06 15:31
	* @brief   单条腿控制 
	* @param   void
	* @retval  void
	*/
void Joint_Legs(int16_t Vx, int16_t Vy, uint16_t Delay)
{
	static float temp=0;

	temp=temp>2*PI?0:temp+0.01f;
	DXL1_setSyncMsg(USART_6,POSITION,3,
									0x01,2648 + Joint_getThighTarAng(Vy,0,temp), /*LH*/               
									0x02,2648 + Joint_getCrusTarAng(Vy + Vx ,-0.1f,temp),
									0x09,2648 + Joint_getThighTarAng(Vx,0,temp));
	vTaskDelay(Delay);
}
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   关节运动测试
	* @param   void
	* @retval  void
	*/
void Joint_MotionTest(void)
{
	DXL1_setSyncMsg(USART_6,POSITION,4,0x01,2648,0x03,2648,0x05,2648,0x07,2648);
	vTaskDelay(80);
	DXL1_setSyncMsg(USART_6,POSITION,4,0x02,2648,0x04,2648,0x06,2648,0x08,2648);
	vTaskDelay(220);

	DXL1_setSyncMsg(USART_6,POSITION,4,0x01,2750,0x03,2648,0x05,2648,0x07,2648);
	vTaskDelay(5);
	DXL1_setSyncMsg(USART_6,POSITION,4,0x02,2750,0x04,2648,0x06,2648,0x08,2648);  
	vTaskDelay(220);

}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 12:34
	* @brief   
	* @param   void
	* @retval  void
	*/
void Thigh_Forward(void)
{
	Motor.M6020[0].targetAngle=M6020_MEDIAN(0)+1024;
	Motor.M6020[1].targetAngle=M6020_MEDIAN(1)-1024;
	Motor.M6020[2].targetAngle=M6020_MEDIAN(2)+1024;
	Motor.M6020[3].targetAngle=M6020_MEDIAN(3)-1024;
	Motor.p_M6020setCur(CAN_1);

}


/*---------------------L O C A L - F U N C T I O N S--------------------------*/
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   大腿控制
	* @param   TarAng 目标角度， Phase相位 ，Temp 倍率
	* @retval  滤波后的角度
	*/

static int16_t Joint_getThighTarAng(int16_t TarAng ,float Phase,float Temp)
{
//	if(TarAng>0)
//	  return (Filter.p_ABS(Curve_Sin(TarAng,2,Phase,0,Temp)));
//	else
//		return -(Filter.p_ABS(Curve_Sin(TarAng,2,Phase,0,Temp)));
//	
//		if(TarAng>0)
	  return ((Curve_Sin(TarAng,2,Phase,0,Temp)));
//	else
//		return -((Curve_Sin(TarAng,2,Phase,0,Temp)));
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   小腿控制
	* @param   TarAng 目标角度， Phase相位 ，Temp 倍率
	* @retval  滤波后的角度
	*/
static int16_t Joint_getCrusTarAng(int16_t TarAng ,float Phase,float Temp)
{
//		return (Filter.p_Limit(Curve_Sin(Filter.p_ABS(TarAng),2,Phase,0,Temp),\
//			Filter.p_ABS(TarAng),0));	
	
		return Curve_Sin(Filter.p_ABS(TarAng),2,Phase,0,Temp);
}


/*-----------------------------------FILE OF END------------------------------*/






