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
static void Joint_PassSandDune(uint8_t Temp);
/*------------------G L O B A L - F U N C T I O N S --------------------------*/
	/**
	* @Data    2019-01-08 14:49
	* @brief   �ؽڳ�ʼ��
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
	* @brief   �ؽڵ������
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
	* @brief   �Խǲ�̬�ؽ��˶�ģ��
	* @param   void
	* @retval  void
	*/
void Joint_TrotMotionModel(int16_t Vx, int16_t Vy, int16_t Omega)
{	
	static float temp=0;
	static int16_t  Err=0,ErrCr=100,Er=0;
	
	if(Vx == 0 && Vy == 0 && Omega == 0)
		temp=0;
	else
	  temp=temp>2*PI?0:temp+0.06f;
	
	//Tex=DR16.switch_left==1?450:0;
	Joint.Vz = PID_Calc(&Joint.PID_Z,GY955.Roll,GY955.targetRoll);
	DXL1_setSyncMsg(USART_6,POSITION,12,
	                0x01,DigitalServo.MX_64[0].MiddleAngle +Err + Joint.Vz - Joint_getThighTarAng(Vy,0,temp), /*LH*/               
						      0x02,DigitalServo.MX_64[1].MiddleAngle +ErrCr + Joint.Vz + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
									0x03,DigitalServo.MX_64[2].MiddleAngle +Err+ Joint.Vz  - Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
									0x04,DigitalServo.MX_64[3].MiddleAngle +ErrCr+ Joint.Vz  + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x05,DigitalServo.MX_64[4].MiddleAngle +Err- 0*Joint.Vz + Joint_getThighTarAng(Vy,0,temp), /*RF*/ 
									0x06,DigitalServo.MX_64[5].MiddleAngle +ErrCr+0*Joint.Vz + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
	
									0x07,DigitalServo.MX_64[6].MiddleAngle +Err- 0*Joint.Vz + Joint_getThighTarAng(Vy,1.0f,temp), /*LF*/ 
									0x08,DigitalServo.MX_64[7].MiddleAngle +ErrCr+0* Joint.Vz + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x09,2324+Er + Joint_getThighTarAng(Omega + Vx,0,temp),
									0x0A,1766-Er + Joint_getThighTarAng(Omega + Vx,1.0f,temp),
									0x0B,2324+Er + Joint_getThighTarAng(Omega - Vx,0,temp),
									0x0C,1766-Er + Joint_getThighTarAng(Omega - Vx,1.0f,temp));
							 
//	vTaskDelay(5);	
	
}
///*------------------------------80 Chars Limit--------------------------------*/
//	/**
//	* @Data    2019-01-09 11:33
//	* @brief   �Խǲ�̬�ؽ��˶�ģ��
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
	* @brief   ��ɳ��
	* @param   void
	* @retval  void
	*/
static void Joint_PassSandDune(uint8_t Temp)
{
	static uint16_t  Tex=600;
	//Tex=DR16.switch_left==1?450:0;

	DXL1_setSyncMsg(USART_6,ACC,12,0x01,100,0x02,100,0x03,100,
																	0x04,100,0x05,100,0x06,100,
																	0x07,100,0x08,100,0x09,100,
																	0x0A,100,0x0B,100,0x0C,100);
	vTaskDelay(5);
	
	switch (Temp)
	{
		case 1:
			for(uint16_t i=0;i<Tex;i+=10)
			{
				DXL1_setSyncMsg(USART_6,POSITION,2,
										0x01,2400 - i , /*LH*/               
										0x02,2648 + i );
				vTaskDelay(5);
			}
			for(uint16_t i=0;i<Tex;i+=10)
			{
				DXL1_setSyncMsg(USART_6,POSITION,2,
										0x01,2400 - Tex + i  , /*LH*/               
										0x02,2648 + Tex - i);
				vTaskDelay(5);
			}

	//		Joint.PID_Z.f_PID_Reset(&Joint.PID_Z,40,0,0);
//			break;
//			
//		case 2:
			
			for(uint16_t i=0;i<Tex;i+=10)
			{
				DXL1_setSyncMsg(USART_6,POSITION,2,
										0x03,2548 - i , /*LH*/               
										0x04,2648 + i );
			vTaskDelay(5);
			}
			for(uint16_t i=0;i<Tex;i+=10)
			{
				DXL1_setSyncMsg(USART_6,POSITION,2,
										0x03,2548 - Tex + i , /*LH*/               
										0x04,2648 + Tex - i);
				vTaskDelay(5);
			}
			
		  DigitalServo.MX_64[0].MiddleAngle=2400;
			DigitalServo.MX_64[2].MiddleAngle=2548;
			
		  DigitalServo.MX_64[1].MiddleAngle=2348;
			DigitalServo.MX_64[3].MiddleAngle=2348;
			vTaskDelay(5);
//			DigitalServo.MX_64[1].MiddleAngle=2400;
//			DigitalServo.MX_64[3].MiddleAngle=2348;
//			
//	    DigitalServo.MX_64[1].MiddleAngle=2500;
//			DigitalServo.MX_64[3].MiddleAngle=2448;
//			
//			DigitalServo.MX_64[5].MiddleAngle=2200;
//			DigitalServo.MX_64[7].MiddleAngle=2448;
			
//			vTaskDelay(200);
//			for(uint16_t i=0;i<300;i+=5)
//			{
//				DXL1_setSyncMsg(USART_6,POSITION,2,
//											0x05,DigitalServo.MX_64[4].MiddleAngle - i , /*LH*/               
//											0x06,DigitalServo.MX_64[5].MiddleAngle + i );
//				vTaskDelay(5);
//			}

//			for(uint16_t i=0;i<600;i+=10)
//			{
//				DXL1_setSyncMsg(USART_6,POSITION,1,
//											0x05,DigitalServo.MX_64[4].MiddleAngle + i );
//				vTaskDelay(5);
//			}
//			for(uint16_t i=0;i<600;i+=10)
//			{
//				DXL1_setSyncMsg(USART_6,POSITION,1,/*LH*/               
//											0x06,DigitalServo.MX_64[5].MiddleAngle - i );
//				vTaskDelay(5);
//			}
//			for(uint16_t i=0;i<300;i+=5)
//			{
//				DXL1_setSyncMsg(USART_6,POSITION,4,
//											0x02,DigitalServo.MX_64[1].MiddleAngle+Tex-i,
//											0x04,DigitalServo.MX_64[3].MiddleAngle+Tex-i,
//											0x05,DigitalServo.MX_64[4].MiddleAngle+300 - i , /*LH*/               
//											0x06,DigitalServo.MX_64[5].MiddleAngle-300 + i );
//				vTaskDelay(5);
//			}
//			
//			for(uint16_t i=0;i<300;i+=5)
//			{
//				DXL1_setSyncMsg(USART_6,POSITION,2,
//											0x07,DigitalServo.MX_64[6].MiddleAngle - i , /*LH*/               
//											0x08,DigitalServo.MX_64[7].MiddleAngle + i );
//				vTaskDelay(5);
//			}
//			for(uint16_t i=0;i<600;i+=10)
//			{
//				DXL1_setSyncMsg(USART_6,POSITION,1,
//										0x07,DigitalServo.MX_64[6].MiddleAngle + i );
//				vTaskDelay(5);
//			}
//			for(uint16_t i=0;i<600;i+=10)
//			{					
//				DXL1_setSyncMsg(USART_6,POSITION,1,               
//									0x08,DigitalServo.MX_64[7].MiddleAngle - i);
//					vTaskDelay(5);
//			}
//			
//			for(uint16_t i=0;i<300;i+=5)
//			{
//				DXL1_setSyncMsg(USART_6,POSITION,2,
//											0x07,DigitalServo.MX_64[6].MiddleAngle+300 - i , /*LH*/               
//											0x08,DigitalServo.MX_64[7].MiddleAngle-300 + i );
//				vTaskDelay(5);
//			}
//			
//	//		Joint.PID_Z.f_PID_Reset(&Joint.PID_Z,40,0,0);
//			
////		  DigitalServo.MX_64[1].MiddleAngle=2600;
////			DigitalServo.MX_64[3].MiddleAngle=2548;
////			
////			DigitalServo.MX_64[5].MiddleAngle=2200;
////			DigitalServo.MX_64[7].MiddleAngle=2124;
////			
////			DXL1_setSyncMsg(USART_6,POSITION,6,0x02,DigitalServo.MX_64[1].MiddleAngle,
////			                                   0x04,DigitalServo.MX_64[3].MiddleAngle,
////			                                   0x05,DigitalServo.MX_64[4].MiddleAngle,
////			                                   0x06,DigitalServo.MX_64[5].MiddleAngle,
////			                                   0x07,DigitalServo.MX_64[6].MiddleAngle,
////			                                   0x08,DigitalServo.MX_64[7].MiddleAngle);
//			vTaskDelay(100);
			break;
			
		case 3:
			
			Joint.PID_Z.f_PID_Reset(&Joint.PID_Z,0,0,0);
//		  DigitalServo.MX_64[0].MiddleAngle=2600;
//			DigitalServo.MX_64[2].MiddleAngle=2748;
//			
//		  DigitalServo.MX_64[1].MiddleAngle=2548;
//			DigitalServo.MX_64[3].MiddleAngle=2548;
			DXL1_setSyncMsg(USART_6,POSITION,8,
		          0x01, DigitalServo.MX_64[0].MiddleAngle,
							0x02, DigitalServo.MX_64[1].MiddleAngle,
							0x03, DigitalServo.MX_64[2].MiddleAngle,
							0x04, DigitalServo.MX_64[3].MiddleAngle,
							0x05,DigitalServo.MX_64[4].MiddleAngle+200, /*LH*/               
							0x06,DigitalServo.MX_64[5].MiddleAngle-200,
							0x07,DigitalServo.MX_64[6].MiddleAngle+200, /*LH*/               
							0x08,DigitalServo.MX_64[7].MiddleAngle-200);
			vTaskDelay(2000);
		
			for(uint16_t i=0;i<Tex;i+=20)
			{
				DXL1_setSyncMsg(USART_6,POSITION,2,
											0x05,DigitalServo.MX_64[4].MiddleAngle - i , /*LH*/               
											0x06,DigitalServo.MX_64[5].MiddleAngle + i );
				vTaskDelay(5);
			}

			for(uint16_t i=0;i<150;i+=10)
			{
				DXL1_setSyncMsg(USART_6,POSITION,1,
											0x05,DigitalServo.MX_64[4].MiddleAngle + Tex + i );
				vTaskDelay(5);
			}
			for(uint16_t i=0;i<700;i+=20)
			{
				DXL1_setSyncMsg(USART_6,POSITION,1,/*LH*/               
											0x06,DigitalServo.MX_64[5].MiddleAngle + Tex - i );
				vTaskDelay(5);
			}
//			break;
//			
//		case 4:
//			DXL1_setSyncMsg(USART_6,POSITION,2,
//							0x07,DigitalServo.MX_64[6].MiddleAngle, /*LH*/               
//							0x08,DigitalServo.MX_64[7].MiddleAngle);
//			vTaskDelay(200);
//			Joint.PID_Z.f_PID_Reset(&Joint.PID_Z,0,0,0);
			vTaskDelay(200);
			for(uint16_t i=0;i<Tex;i+=20)
			{
				DXL1_setSyncMsg(USART_6,POSITION,2,
											0x07,DigitalServo.MX_64[6].MiddleAngle - i , /*LH*/               
											0x08,DigitalServo.MX_64[7].MiddleAngle + i );
				vTaskDelay(5);
			}
			for(uint16_t i=0;i<150;i+=10)
			{
				DXL1_setSyncMsg(USART_6,POSITION,1,
										0x07,DigitalServo.MX_64[6].MiddleAngle + Tex + i );
				vTaskDelay(5);
			}
			for(uint16_t i=0;i<700;i+=20)
			{					
				DXL1_setSyncMsg(USART_6,POSITION,1,         				
									0x08,DigitalServo.MX_64[7].MiddleAngle + Tex - i);
					vTaskDelay(5);
			}
		  vTaskDelay(50);
			DigitalServo.MX_64[0].MiddleAngle=2600;
			DigitalServo.MX_64[2].MiddleAngle=2748;
			
		  DigitalServo.MX_64[1].MiddleAngle=2548;
			DigitalServo.MX_64[3].MiddleAngle=2548;
			DXL1_setSyncMsg(USART_6,POSITION,8,
		          0x01, DigitalServo.MX_64[0].MiddleAngle,
							0x02, DigitalServo.MX_64[1].MiddleAngle,
							0x03, DigitalServo.MX_64[2].MiddleAngle,
							0x04, DigitalServo.MX_64[3].MiddleAngle,
							0x05,DigitalServo.MX_64[4].MiddleAngle, /*LH*/               
							0x06,DigitalServo.MX_64[5].MiddleAngle,
							0x07,DigitalServo.MX_64[6].MiddleAngle, /*LH*/               
							0x08,DigitalServo.MX_64[7].MiddleAngle);
			break;
		default:
			break;
	
	}
	
//	if(Temp==1)
//	{
//		for(uint16_t i=0;i<Tex;i+=10)
//		{
//			DXL1_setSyncMsg(USART_6,POSITION,2,
//									0x01,2400 - i , /*LH*/               
//									0x02,2648 + i );
//			vTaskDelay(5);
//		}
//		for(uint16_t i=0;i<Tex;i+=10)
//		{
//			DXL1_setSyncMsg(USART_6,POSITION,2,
//									0x01,2400 - Tex + i  , /*LH*/               
//									0x02,2648 + Tex - 2*i);
//			vTaskDelay(5);
//		}

//	  DXL1_setSyncMsg(USART_6,POSITION,2,
//									0x01,DigitalServo.MX_64[0].MiddleAngle  , /*LH*/               
//									0x02,DigitalServo.MX_64[1].MiddleAngle );
//		vTaskDelay(100);
//		
//		for(uint16_t i=0;i<Tex;i+=10)
//		{
//			DXL1_setSyncMsg(USART_6,POSITION,2,
//									0x03,2548 - i , /*LH*/               
//									0x04,2648 + i );
//		vTaskDelay(5);
//		}
//		for(uint16_t i=0;i<Tex;i+=10)
//		{
//			DXL1_setSyncMsg(USART_6,POSITION,2,
//									0x03,2548 - Tex + i , /*LH*/               
//									0x04,2648 + Tex - 2*i);
//			vTaskDelay(5);
//		}
//		

//		DXL1_setSyncMsg(USART_6,POSITION,2,
//									0x03,DigitalServo.MX_64[2].MiddleAngle, /*LH*/               
//									0x04,DigitalServo.MX_64[3].MiddleAngle );
//		vTaskDelay(100);
//			
////		
////		for(uint16_t i=0;i<200;i+=20)
////		{
////			DXL1_setSyncMsg(USART_6,POSITION,2,
////										0x05,2400 - i , /*LH*/               
////										0x06,2700 + i );
////			vTaskDelay(5);
////		}
////		
////		for(uint16_t i=0;i<600;i+=20)
////		{
////			DXL1_setSyncMsg(USART_6,POSITION,1,
////										0x05,2400 - Tex + i );
////			vTaskDelay(5);
////		}
////		for(uint16_t i=0;i<600;i+=20)
////		{
////			DXL1_setSyncMsg(USART_6,POSITION,1,/*LH*/               
////										0x06,2700 + Tex - i );
////			vTaskDelay(5);
////		}
////		

////		for(uint16_t i=0;i<Tex;i+=20)
////		{
////			DXL1_setSyncMsg(USART_6,POSITION,2,
////										0x07,2400 - i , /*LH*/               
////										0x08,2948 + i );
////			vTaskDelay(5);
////		}
////		for(uint16_t i=0;i<600;i+=20)
////		{
////			DXL1_setSyncMsg(USART_6,POSITION,1,
////									0x07,2400 - Tex + i );
////			vTaskDelay(5);
////		}
////		for(uint16_t i=0;i<600;i+=20)
////		{					
////			DXL1_setSyncMsg(USART_6,POSITION,1,               
////								0x08,2948 + Tex - i);
////				vTaskDelay(5);
////		}
////		
////				for(uint16_t i=0;i<Tex;i+=10)
////		{
////			DXL1_setSyncMsg(USART_6,POSITION,2,
////									0x01,2400 - i , /*LH*/               
////									0x02,2648 + i );
////			vTaskDelay(5);
////		}
////		for(uint16_t i=0;i<Tex;i+=10)
////		{
////			DXL1_setSyncMsg(USART_6,POSITION,2,
////									0x01,2400 - Tex + i  , /*LH*/               
////									0x02,2648 + Tex - 2*i);
////			vTaskDelay(5);
////		}


////		for(uint16_t i=0;i<Tex;i+=10)
////		{
////			DXL1_setSyncMsg(USART_6,POSITION,2,
////									0x03,2548 - i , /*LH*/               
////									0x04,2648 + i );
////		vTaskDelay(5);
////		}
////		for(uint16_t i=0;i<Tex;i+=10)
////		{
////			DXL1_setSyncMsg(USART_6,POSITION,2,
////									0x03,2548 - Tex + i , /*LH*/               
////									0x04,2648 + Tex - 2*i);
////			vTaskDelay(5);
////		}
////		
////	
////    DigitalServo.MX_64[1].MiddleAngle=2400;
////		DigitalServo.MX_64[3].MiddleAngle=2348;
////		
////		DigitalServo.MX_64[5].MiddleAngle=2300;
////		DigitalServo.MX_64[7].MiddleAngle=2548;
////		
//		Joint.PID_Z.f_PID_Reset(&Joint.PID_Z,40,0,0);

//	}
//	else if(Temp==2)
//	{
//	
//	}
//  else if(Temp==2)
//	{
//	  Joint.PID_Z.f_PID_Reset(&Joint.PID_Z,0,0,0);
//		for(uint16_t i=0;i<Tex;i+=20)
//		{
//			DXL1_setSyncMsg(USART_6,POSITION,2,
//										0x05,2400 - i , /*LH*/               
//										0x06,2700 + i );
//			vTaskDelay(5);
//		}
//		
//		for(uint16_t i=0;i<700;i+=20)
//		{
//			DXL1_setSyncMsg(USART_6,POSITION,1,
//										0x05,2400 - Tex + i );
//			vTaskDelay(5);
//		}
//		for(uint16_t i=0;i<700;i+=20)
//		{
//			DXL1_setSyncMsg(USART_6,POSITION,1,/*LH*/               
//										0x06,2700 + Tex - i );
//			vTaskDelay(5);
//		}
////		Joint.PID_Z.f_PID_Reset(&Joint.PID_Z,0,0,0);
//	}
//	else if(Temp==3)
//	{
//		Joint.PID_Z.f_PID_Reset(&Joint.PID_Z,0,0,0);
//		for(uint16_t i=0;i<Tex;i+=20)
//		{
//			DXL1_setSyncMsg(USART_6,POSITION,2,
//										0x07,2400 - i , /*LH*/               
//										0x08,2948 + i );
//			vTaskDelay(5);
//		}
//		for(uint16_t i=0;i<700;i+=20)
//		{
//			DXL1_setSyncMsg(USART_6,POSITION,1,
//									0x07,2400 - Tex + i );
//			vTaskDelay(5);
//		}
//		for(uint16_t i=0;i<700;i+=20)
//		{					
//			DXL1_setSyncMsg(USART_6,POSITION,1,               
//								0x08,2948 + Tex - i);
//				vTaskDelay(5);
//		}
//		//Joint.PID_Z.f_PID_Reset(&Joint.PID_Z,0,0,0);
//	}
	
	DXL1_setSyncMsg(USART_6,ACC,12,0x01,0,0x02,100,0x03,0,
																 0x04,0,0x05,100,0x06,0,
																 0x07,0,0x08,100,0x09,0,
																 0x0A,0,0x0B,100,0x0C,0);
	vTaskDelay(5);
	

}

	/**
	* @Data    2019-01-09 11:33
	* @brief   �Խǲ�̬�ؽ��˶�ģ��
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
	* @brief   ���ǲ�̬�ؽ��˶�ģ��
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
	                0x01,2400 - Joint_getThighTarAng(Vy,-0.5f,temp), /*LF��ǰ*/               
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
	* @brief   �ؽڿ���״̬��
	* @param   void
	* @retval  void
	*/
	void Joint_StateMachine(void)
	{
		static uint8_t temp=1;
		PhotoelectricScan();/*��翪��ɨ��*/
		if(DR16.switch_left == 1)
		{
			if(!PhoFlg.RF&&!PhoFlg.LF)
			{
				temp=2;
			}
//			else if(!PhoFlg.LF)
//			{
//				temp=3;
//			}
			else if(!PhoFlg.LH&&!PhoFlg.RH)
			{
				temp=4;
			}
//			else if(!PhoFlg.RH)
//			{
//				temp=5;
//			}
			
		}
//		if(DR16.switch_left == 2)
//		{
//			temp=1;
//		}

		switch (temp)
		{
			case 1:/*״̬1 �Խǲ�̬��ɳ��*/
				Joint_TrotMotionModel(-DR16.ch1/2,50,-DR16.ch3/2);
				break;
			case 2:/*״̬2 ���ǲ�̬��ɳ��*/
				//for(uint8_t i=0;i<2;i++)
				Joint_PassSandDune(1);
			  temp=6;
      //  Joint_WalkMotionModel(DR16.ch1,200,DR16.ch3);
				break;
			case 3:/*״̬3 �Խǲ�̬���ݵ�*/
				Joint_PassSandDune(2);
        temp=6;
				break;
			case 4:/*״̬4 ���ǲ�̬���ݵ�*/
				Joint_PassSandDune(3);
		  	temp=6;
				break;
			case 5:/*״̬5 ת��ȴ������ź�*/
	      Joint_PassSandDune(4);
		  	temp=6;
				break;
			case 6:/*״̬6 �Խǲ�̬����*/
  			Joint_TrotMotionModel(-DR16.ch1/2,100,-DR16.ch3/2);
				break;		
			case 7:/*״̬7 ��������*/
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
	* @brief   ��е�ۿ���
	* @param   UpperarmTarang:�ϱ�Ŀ��ֵ��ForearmTarang ��ǰ��Ŀ��ֵ
	* @retval  void
	*/
void Joint_RobotArmCtrl(uint16_t UpperarmTarang,uint16_t ForearmTarang)
{
	DXL1_setSyncMsg(USART_6,POSITION,2,0x0E,UpperarmTarang,0x0F,ForearmTarang);
}
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-03-06 15:31
	* @brief   �����ȿ��� 
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
	* @brief   �ؽ��˶�����
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
	* @brief   ���ȿ���
	* @param   TarAng Ŀ��Ƕȣ� Phase��λ ��Temp ����
	* @retval  �˲���ĽǶ�
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
	* @brief   С�ȿ���
	* @param   TarAng Ŀ��Ƕȣ� Phase��λ ��Temp ����
	* @retval  �˲���ĽǶ�
	*/
static int16_t Joint_getCrusTarAng(int16_t TarAng ,float Phase,float Temp)
{
//		return (Filter.p_Limit(Curve_Sin(Filter.p_ABS(TarAng),2,Phase,0,Temp),\
//			Filter.p_ABS(TarAng),0));	
	TarAng*=3;
	TarAng=TarAng>600?600:TarAng;
	TarAng=TarAng<-600?-600:TarAng;
//	if(Curve_Sin(Filter.p_ABS(TarAng),2,Phase,0,Temp)>0)
		return Curve_Sin(Filter.p_ABS(TarAng),2,Phase,0,Temp);
//	else
//		return 0;
}


/*-----------------------------------FILE OF END------------------------------*/






