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
static float LH=0,RH=0,LFx=0,RFx=0;
/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static int16_t Joint_getThighTarAng(int16_t TarAng ,float Phase,float Temp);
static int16_t Joint_getCrusTarAng(int16_t TarAng ,float Phase,float Temp);
/*------------------G L O B A L - F U N C T I O N S --------------------------*/

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
	if(Vx == 0 && Vy == 0 && Omega == 0)
		temp=0;
	else
	  temp=temp>2*PI?0:temp+0.02f;
	
	DXL1_setSyncMsg(USART_6,POSITION,12,
	                0x01,2600 - Joint_getThighTarAng(Vy,0,temp), /*LH*/               
						      0x02,2548 + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
									0x03,2748 - Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
									0x04,2548 + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x05,2648 + Joint_getThighTarAng(Vy,0,temp), /*RF*/ 
									0x06,2400 + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
									0x07,2648 + Joint_getThighTarAng(Vy,1.0f,temp), /*LF*/ 
									0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x09,2324 + Joint_getThighTarAng(Omega + Vx,0,temp),
									0x0A,1766 + Joint_getThighTarAng(Omega + Vx,1.0f,temp),
									0x0B,2324 + Joint_getThighTarAng(Omega - Vx,0,temp),
									0x0C,1766 + Joint_getThighTarAng(Omega - Vx,1.0f,temp));
							 
//	vTaskDelay(5);	
	
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
	if(Vx == 0 && Vy == 0 && Omega == 0)
		temp=0;
	else
	  temp=temp>2*PI?0:temp+0.02f;
	
	DXL1_setSyncMsg(USART_6,POSITION,12,
	                0x09,2048 - Joint_getThighTarAng(Vy,0,temp), /*LH*/               
						      0x02,2548 + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
									0x03,2748 - Joint_getThighTarAng(Vy,1.0f,temp), /*RH*/ 
									0x04,2548 + Joint_getCrusTarAng(Vy + Vx + Omega,1.25f,temp),
									
                  0x0B,2048 + Joint_getThighTarAng(Vy,0,temp), /*RF*/ 
									0x06,2400 + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
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
	  temp=temp>2*PI?0:temp+0.03f;

	RFx=Joint_getThighTarAng(Vy,0.0f,temp);
  LH=Joint_getThighTarAng(Vy,-0.5f,temp);
	LFx=Joint_getThighTarAng(Vy,-1.0f,temp);
	RH=Joint_getThighTarAng(Vy,-1.5f,temp);
	
	DXL1_setSyncMsg(USART_6,POSITION,12,
	                0x01,2600 - Joint_getThighTarAng(Vy,-0.5f,temp), /*LH��ǰ*/               
						      0x02,2548 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.25f,temp),
									
									0x03,2748 - Joint_getThighTarAng(Vy,-1.5f,temp), /*RH*/ 
									0x04,2548 + Joint_getCrusTarAng(Vy + Vx + Omega,-1.25f,temp),
									
                  0x05,2648 + Joint_getThighTarAng(Vy,-1.0,temp), /*RF*/ 
									0x06,2400 + Joint_getCrusTarAng(Vy + Vx + Omega,-0.75f,temp),
									
									0x07,2648 + Joint_getThighTarAng(Vy,0.0f,temp), /*LF*/ 
									0x08,2648 + Joint_getCrusTarAng(Vy + Vx + Omega,0.25f,temp),
									
                  0x09,2334 + Joint_getThighTarAng(Omega + Vx,0,temp),
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
		static uint8_t temp=0;

		switch (temp)
		{
			case 1:/*״̬1 �Խǲ�̬��ɳ��*/
				Joint_TrotMotionModel(DR16.ch1,DR16.ch2,DR16.ch3);
				break;
			case 2:/*״̬2 ���ǲ�̬��ɳ��*/
        Joint_WalkMotionModel(DR16.ch1,200,DR16.ch3);
				break;
			case 3:/*״̬3 �Խǲ�̬���ݵ�*/
				Joint_TrotMotionModel(DR16.ch1,DR16.ch2,DR16.ch3);
				break;
			case 4:/*״̬4 ���ǲ�̬���ݵ�*/
				Joint_WalkMotionModel(DR16.ch1,200,DR16.ch3);
				break;
			case 5:/*״̬5 ת��ȴ������ź�*/
				Joint_WalkMotionModel(DR16.ch1,200,DR16.ch3);
				break;
			case 6:/*״̬6 �Խǲ�̬����*/
				Joint_TrotMotionModel(DR16.ch1,DR16.ch2,DR16.ch3);
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
	TarAng*=2;
	TarAng=TarAng>500?500:TarAng;
	TarAng=TarAng<-500?-500:TarAng;
//	if(Curve_Sin(Filter.p_ABS(TarAng),2,Phase,0,Temp)>0)
		return Curve_Sin(Filter.p_ABS(TarAng),2,Phase,0,Temp);
//	else
//		return 0;
}


/*-----------------------------------FILE OF END------------------------------*/






