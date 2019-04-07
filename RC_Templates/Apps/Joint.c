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
#include "Gyro.h"
#include "Photoelectric.h"
/*-------------------------- D E F I N E S -----------------------------------*/
static float LH=0,RH=0,LFx=0,RFx=0;
Joint_t Joint;
/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static int16_t Joint_getThighTarAng(int16_t TarAng ,float Phase,float Temp);
static int16_t Joint_getCrusTarAng(int16_t TarAng ,float Phase,float Temp);
static void Joint_PassSandDune(void);
static void Joint_PassSandDunex(void);
/*------------------G L O B A L - F U N C T I O N S --------------------------*/
	/**
	* @Data    2019-01-08 14:49
	* @brief   关节初始化
	* @param   void
	* @retval  void
	*/
void Joint_Init(void)
{
	Joint.PID_Spin.maxInput=360;
	
	DigitalServo.MX_64[0].MiddleAngle = 2600;
	DigitalServo.MX_64[1].MiddleAngle = 2548;
	DigitalServo.MX_64[2].MiddleAngle = 2748;
	DigitalServo.MX_64[3].MiddleAngle = 2548;
	DigitalServo.MX_64[4].MiddleAngle = 2600;
	DigitalServo.MX_64[5].MiddleAngle = 2400;
	DigitalServo.MX_64[6].MiddleAngle = 2600;
	DigitalServo.MX_64[7].MiddleAngle = 2648;
	DigitalServo.MX_64[8].MiddleAngle = 2324;
	DigitalServo.MX_64[9].MiddleAngle = 1766;
	DigitalServo.MX_64[10].MiddleAngle = 2324;
	DigitalServo.MX_64[11].MiddleAngle = 1766;
	
	
	PID_StructInit(&Joint.PID_X, POSITION_PID, 800, 500, 2, 0, 0);
	PID_StructInit(&Joint.PID_Y, POSITION_PID, 800, 500, 2, 0, 0);
	PID_StructInit(&Joint.PID_Z, POSITION_PID, 500, 100, 0, 0, 0);
	PID_StructInit(&Joint.PID_Spin, POSITION_PID, 50, 100, 10, 0, 0);
}
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
	* @brief   对角步态关节运动模型
	* @param   void
	* @retval  void
	*/
void Joint_TrotMotionModel(int16_t Vx, int16_t Vy, int16_t Omega)
{	
	static float temp=0;
	static uint16_t  Tex=0;
	
	if(Vx == 0 && Vy == 0 && Omega == 0)
		temp=0;
	else
	  temp=temp>2*PI?0:temp+0.06f;
	
	//Tex=DR16.switch_left==1?450:0;
	Joint.Vz = PID_Calc(&Joint.PID_Z,GY955.Roll,GY955.targetRoll);
	DXL1_setSyncMsg(USART_6,POSITION,12,
	                0x01,2600 - Tex +0 *Joint.Vz - Joint_getThighTarAng(Vy,0,temp), /*LH*/               
						      0x02,2548 + Tex - Joint.Vz + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
									0x03,2748 + 0*Joint.Vz  - Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
									0x04,2548 - Joint.Vz  + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x05,2600 - 0*Joint.Vz + Joint_getThighTarAng(Vy,0,temp), /*RF*/ 
									0x06,2400 +Joint.Vz + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
									0x07,2600 - 0*Joint.Vz + Joint_getThighTarAng(Vy,1.0f,temp), /*LF*/ 
									0x08,2648 + Joint.Vz + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x09,2324 + Joint_getThighTarAng(Omega + Vx,0,temp),
									0x0A,1766 + Joint_getThighTarAng(Omega + Vx,1.0f,temp),
									0x0B,2324 + Joint_getThighTarAng(Omega - Vx,0,temp),
									0x0C,1766 + Joint_getThighTarAng(Omega - Vx,1.0f,temp));
							 
//	vTaskDelay(5);	
	
}
///*------------------------------80 Chars Limit--------------------------------*/
//	/**
//	* @Data    2019-01-09 11:33
//	* @brief   对角步态关节运动模型
//	* @param   void
//	* @retval  void
//	*/
//void Joint_TrotMotionModel(int16_t Vx, int16_t Vy, int16_t Omega)
//{	
//	static float temp=0;
//	static uint16_t  Tex=0;
//	
//	if(Vx == 0 && Vy == 0 && Omega == 0)
//		temp=0;
//	else
//	  temp=temp>2*PI?0:temp+0.04f;
//	
//	//Tex=DR16.switch_left==1?450:0;
//	Joint.Vz = PID_Calc(&Joint.PID_Z,GY955.Roll,GY955.targetRoll);
//	DXL1_setSyncMsg(USART_6,POSITION,12,
//	                0x01,2400 - Tex +0 *Joint.Vz - Joint_getThighTarAng(Vy,0,temp), /*LH*/               
//						      0x02,2748 + Tex - Joint.Vz + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
//									
//									0x03,2548 + 0*Joint.Vz  - Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
//									0x04,2748 - Joint.Vz  + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
//									
//                  0x05,2400 - 0*Joint.Vz + Joint_getThighTarAng(Vy,0,temp), /*RF*/ 
//									0x06,2600 +Joint.Vz + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
//									
//									0x07,2400 - 0*Joint.Vz + Joint_getThighTarAng(Vy,1.0f,temp), /*LF*/ 
//									0x08,2848 + Joint.Vz + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
//									
//                  0x09,2374 + Joint_getThighTarAng(Omega + Vx,0,temp),
//									0x0A,1716 + Joint_getThighTarAng(Omega + Vx,1.0f,temp),
//									0x0B,2374 + Joint_getThighTarAng(Omega - Vx,0,temp),
//									0x0C,1716 + Joint_getThighTarAng(Omega - Vx,1.0f,temp));
//							 
////	vTaskDelay(5);	
//	
//}
	/**
	* @Data    2019-01-09 11:33
	* @brief   过沙丘
	* @param   void
	* @retval  void
	*/
static void Joint_PassSandDune(void)
{
		static uint16_t  Tex=450;
		//Tex=DR16.switch_left==1?450:0;
    
	  DXL1_setSyncMsg(USART_6,ACC,12,0x01,100,0x02,100,0x03,100,
	                                  0x04,100,0x05,100,0x06,100,
                                    0x07,100,0x08,100,0x09,100,
	                                  0x0A,100,0x0B,100,0x0C,100);
  	vTaskDelay(5);
		DXL1_setSyncMsg(USART_6,POSITION,2,
	                0x01,2400 - Tex , /*LH*/               
						      0x02,2648 + Tex );
	  vTaskDelay(300);
	  DXL1_setSyncMsg(USART_6,POSITION,2,
	                0x01,2400  , /*LH*/               
						      0x02,2648 );
	  vTaskDelay(300);
		DXL1_setSyncMsg(USART_6,POSITION,2,
	                0x03,2548 - Tex , /*LH*/               
						      0x04,2648 + Tex );
	  vTaskDelay(300);
	  DXL1_setSyncMsg(USART_6,POSITION,2,
	                0x03,2548 , /*LH*/               
						      0x04,2448 );
		  vTaskDelay(5);
			DXL1_setSyncMsg(USART_6,ACC,12,0x01,0,0x02,100,0x03,0,
																  	 0x04,0,0x05,100,0x06,0,
																		 0x07,0,0x08,100,0x09,0,
																		 0x0A,0,0x0B,100,0x0C,0);
			vTaskDelay(5);
}

	/**
	* @Data    2019-01-09 11:33
	* @brief   过沙丘
	* @param   void
	* @retval  void
	*/
static void Joint_PassSandDunex(void)
{
		static uint16_t  Tex=450;
		//Tex=DR16.switch_left==1?450:0;
    
	  DXL1_setSyncMsg(USART_6,ACC,12,0x01,100,0x02,100,0x03,100,
	                                  0x04,100,0x05,100,0x06,100,
                                    0x07,100,0x08,100,0x09,100,
	                                  0x0A,100,0x0B,100,0x0C,100);
  	vTaskDelay(5);

		DXL1_setSyncMsg(USART_6,POSITION,2,
	                0x05,2400 - Tex , /*LH*/               
						      0x06,2700 + Tex );
	  vTaskDelay(300);
	  DXL1_setSyncMsg(USART_6,POSITION,1,
	                0x05,2550 );
		vTaskDelay(300);
	 DXL1_setSyncMsg(USART_6,POSITION,1,/*LH*/               
						      0x06,2400 );
	  vTaskDelay(300);
		DXL1_setSyncMsg(USART_6,POSITION,2,
	                0x07,2400 - Tex , /*LH*/               
						      0x08,2948 + Tex );
	  vTaskDelay(300);
	  DXL1_setSyncMsg(USART_6,POSITION,1,
	                0x07,2550 );
			vTaskDelay(300);					
		DXL1_setSyncMsg(USART_6,POSITION,1,               
							0x08,2648 );
		  vTaskDelay(5);
		DXL1_setSyncMsg(USART_6,ACC,12,0x01,0,0x02,100,0x03,0,
																	 0x04,0,0x05,100,0x06,0,
																	 0x07,0,0x08,100,0x09,0,
																	 0x0A,0,0x0B,100,0x0C,0);
		vTaskDelay(5);
}

	/**
	* @Data    2019-01-09 11:33
	* @brief   对角步态关节运动模型
	* @param   void
	* @retval  void
	*/
void Joint_TrotMotionModelx(int16_t Vx, int16_t Vy, int16_t Omega)
{	
	static float temp=0;
	if(Vx == 0 && Vy == 0 && Omega == 0 )
		temp=0;
	else
	  temp=temp>2*PI?0:temp+0.02f;
	
	DXL1_setSyncMsg(USART_6,POSITION,12,
	                0x09,2048 - Joint_getThighTarAng(Vy,0,temp), /*LH*/               
						      0x02,2548 + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
									0x03,2748 - Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
									0x04,2548 + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x0B,2048 + Joint_getThighTarAng(Vy,0,temp), /*RF*/ 
									0x06,2400 + Joint_getCrusTarAng(Vy + Vx + Omega,0.5f,temp),
									
									0x07,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*LF*/ 
									0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x01,2600 + Joint_getThighTarAng(Omega + Vx,0,temp),
									0x0A,2048 + Joint_getThighTarAng(Omega + Vx,1.0f,temp),
									0x05,2648 + Joint_getThighTarAng(Omega - Vx,0,temp),
									0x0C,2048 + Joint_getThighTarAng(Omega - Vx,1.0f,temp));
							 
//	vTaskDelay(5);	
	
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-09 11:33
	* @brief   三角步态关节运动模型
	* @param   void
	* @retval  void
	*/
void Joint_WalkMotionModel(int16_t Vx, int16_t Vy, int16_t Omega)
{	
	static float temp=0;

	if(Vx == 0 && Vy == 0 && Omega == 0)
		temp=0;
	else
	  temp=temp>2*PI?0:temp+0.08f;

	RFx=Joint_getThighTarAng(Vy,0.0f,temp);
  LH=Joint_getThighTarAng(Vy,-0.5f,temp);
	LFx=Joint_getThighTarAng(Vy,-1.0f,temp);
	RH=Joint_getThighTarAng(Vy,-1.5f,temp);
	
	DXL1_setSyncMsg(USART_6,POSITION,12,
	                0x01,2400 - Joint_getThighTarAng(Vy,-0.5f,temp), /*LF左前*/               
						      0x02,2748 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.25f,temp),
									
									0x03,2548 - Joint_getThighTarAng(Vy,-1.5f,temp), /*RH*/ 
									0x04,2748 + Joint_getCrusTarAng(Vy + Vx + Omega,-1.25f,temp),
									
                  0x05,2400 + Joint_getThighTarAng(Vy,-1.0,temp), /*RH*/ 
									0x06,2600 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.75f,temp),
									
									0x07,2400 + Joint_getThighTarAng(Vy,0.0f,temp), /*LF*/ 
									0x08,2848 + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
                  0x09,2324 + Joint_getThighTarAng(Omega + Vx,0,temp),
									0x0A,1766 + Joint_getThighTarAng(Omega + Vx,1.0f,temp),
									0x0B,2324 + Joint_getThighTarAng(Omega - Vx,0,temp),
									0x0C,1766 + Joint_getThighTarAng(Omega - Vx,1.0f,temp));
}


/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-03-06 15:31
	* @brief   关节控制状态机
	* @param   void
	* @retval  void
	*/
	void Joint_StateMachine(void)
	{
		static uint8_t temp=1;
		PhotoelectricScan();/*光电开关扫描*/
		if(DR16.switch_left == 1)
		{
			if(!PhoFlg.RF&& !PhoFlg.LF)
			{
				temp=2;
			}
			else if(!PhoFlg.RH&& !PhoFlg.LH)
			{
				temp=3;
			}
		}
//		if(DR16.switch_left == 2)
//		{
//			temp=1;
//		}

		switch (temp)
		{
			case 1:/*状态1 对角步态往沙丘*/
				Joint_TrotMotionModel(-DR16.ch1/2,DR16.ch2/2,-DR16.ch3/2);
				break;
			case 2:/*状态2 三角步态过沙丘*/
				Joint_PassSandDune();
			  temp=1;
      //  Joint_WalkMotionModel(DR16.ch1,200,DR16.ch3);
				break;
			case 3:/*状态3 对角步态往草地*/
				Joint_PassSandDunex();
		  	temp=1;
				break;
			case 4:/*状态4 三角步态过草地*/
				Joint_WalkMotionModel(DR16.ch1,200,DR16.ch3);
				break;
			case 5:/*状态5 转弯等待上坡信号*/
				Joint_WalkMotionModel(DR16.ch1,200,DR16.ch3);
				break;
			case 6:/*状态6 对角步态上坡*/
				Joint_TrotMotionModel(DR16.ch1,DR16.ch2,DR16.ch3);
				break;		
			case 7:/*状态7 举起令牌*/
				Joint_TrotMotionModel(0,0,0);
			  Joint_RobotArmCtrl(2600,2600);
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
void Joint_RobotArmCtrl(uint16_t UpperarmTarang,uint16_t ForearmTarang)
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
//	TarAng*=2;
	  TarAng=TarAng>200?200:TarAng;
		TarAng=TarAng<-200?-200:TarAng;
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
	TarAng*=2;
	TarAng=TarAng>600?600:TarAng;
	TarAng=TarAng<-600?-600:TarAng;
//	if(Curve_Sin(Filter.p_ABS(TarAng),2,Phase,0,Temp)>0)
		return Curve_Sin(Filter.p_ABS(TarAng),2,Phase,0,Temp);
//	else
//		return 0;
}


/*-----------------------------------FILE OF END------------------------------*/






