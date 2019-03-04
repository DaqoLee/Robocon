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

float Y1=0,Y2=0;

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/



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

	Y1=Filter.p_ABS(Curve_Sin(Vy,2,0,0));
	Y2=Filter.p_Limit(Curve_Sin(Vy,4,-1,0),Vy,0);
//	static float X=0;
//	DXL1_setSyncMsg(USART_6,POSITION,4,0x02,2648,0x04,2648,0x06,2648,0x08,2648);
//	vTaskDelay(50);
//	DXL1_setSyncMsg(USART_6,POSITION,8,0x01,2648,0x03,2648,0x05,2648,0x07,2648,
//                                     0x09,2648,0x0A,2648,0x0B,2648,0x0C,2648);

//	vTaskDelay(420);
//	
//	DXL1_setSyncMsg(USART_6,POSITION,8,0x01,2648 + Vy,
//	                                   0x03,2648 + Vy,
//																	   0x05,2648 - Vy,
//																	   0x07,2648 - Vy,
//                                     0x09,2648 + Vx + Omega,
//	                                   0x0A,2648 + Vx + Omega,
//																	   0x0B,2648 - Vx + Omega,
//																	   0x0C,2648 - Vx + Omega);																 
//	vTaskDelay(5);
//	DXL1_setSyncMsg(USART_6,POSITION,4,	                         
//	                0x02,2648 + LIMIT(ABS(Vy) + ABS(Vx) + ABS(Omega),400),
//	                0x04,2648 + LIMIT(ABS(Vy) + ABS(Vx) + ABS(Omega),400),
//									0x06,2648 + LIMIT(ABS(Vy) + ABS(Vx) + ABS(Omega),400),
//									0x08,2648 + LIMIT(ABS(Vy) + ABS(Vx) + ABS(Omega),400));  
//	vTaskDelay(420);	 
//	DXL1_setSyncMsg(USART_2,POSITION,8,0x01,2548 + (int16_t)ABS(Y1),
//	                                   0x02,2548 + (int16_t)Y2,
//																		 0x05,2548,
//																		 0x07,2548 - Vy,
//                                     0x09,2548,
//																		 0x0A,2548 + Vx + Omega,
//																		 0x0B,2548, 
//																		 0x0C,2548 - Vx + Omega);
//	Y1=Vy*sin((X/180)*PI);
//	Y2=250*sin((X/90)*PI);
//	Y2=Y2>0?Y2:0;
//	X=X>=360?0:X+5;
//																		 
//	vTaskDelay(25);
//	
//	
	DXL1_setSyncMsg(USART_2,POSITION,8,
	                0x01,2548 + (int16_t)Filter.p_ABS(Curve_Sin(Vy,2,0,0)),                
						      0x02,2500 + (int16_t)Filter.p_Limit(Curve_Sin(Vy,4,0,0),Vy,0),
									0x05,2548,
									0x07,2548 - Vy,
                  0x09,2548,
									0x0A,2548 + Vx + Omega,
									0x0B,2548, 
									0x0C,2548 - Vx + Omega);
							 
	vTaskDelay(35);	
	

	DXL1_setSyncMsg(USART_2,POSITION,12,
	                0x01,2548 + (int16_t)Filter.p_ABS(Curve_Sin(Vy,2,0,0)),                
						      0x02,2500 + (int16_t)Filter.p_Limit(Curve_Sin(Vy,4,0,0),Vy,0),
									0x03,2548 + (int16_t)Filter.p_ABS(Curve_Sin(Vy,2,2,0)),
									0x04,2548 + (int16_t)Filter.p_Limit(Curve_Sin(Vy,4,2,0),Vy,0),
                  0x05,2548 + (int16_t)Filter.p_ABS(Curve_Sin(Vy,2,0,0)),
									0x06,2548 + (int16_t)Filter.p_Limit(Curve_Sin(Vy,4,0,0),Vy,0),
									0x07,2548 + (int16_t)Filter.p_ABS(Curve_Sin(Vy,2,0,0)),
									0x08,2548 + (int16_t)Filter.p_Limit(Curve_Sin(Vy,4,0,0),Vy,0),
                  0x09,2548 + (int16_t)Filter.p_ABS(Curve_Sin(Vy,2,0,0)),
									0x0A,2548 + (int16_t)Filter.p_ABS(Curve_Sin(Vy,2,0,0)),
									0x0B,2548 + (int16_t)Filter.p_ABS(Curve_Sin(Vy,2,0,0)), 
									0x0C,2548 + (int16_t)Filter.p_ABS(Curve_Sin(Vy,2,0,0)));
							 
	vTaskDelay(35);	

//	DXL1_setSyncMsg(USART_6,POSITION,4,0x02,2748,
//	                                   0x04,2648 + LIMIT(ABS(Vy) + ABS(Vx) + ABS(Omega),400),
//																		 0x06,2648,
//																		 0x08,2648 + LIMIT(ABS(Vy) + ABS(Vx) + ABS(Omega),400));

//	vTaskDelay(220);
//		DXL1_setSyncMsg(USART_6,POSITION,4,	                         
//	                0x02,2748 + LIMIT(ABS(Vy) + ABS(Vx) + ABS(Omega),400),
//	                0x04,2748 ,
//									0x06,2748 + LIMIT(ABS(Vy) + ABS(Vx) + ABS(Omega),400),
//									0x08,2748);  
//	vTaskDelay(5);
//	DXL1_setSyncMsg(USART_6,POSITION,8,0x01,2548 + Vy,
//	                                   0x03,2548 ,
//																	   0x05,2548 - Vy,
//																	   0x07,2548 ,
//                                     0x09,2548 + Vx + Omega,
//	                                   0x0A,2548,
//																	   0x0B,2548 - Vx + Omega,
//																	   0x0C,2548);																 
//	vTaskDelay(5);
//	DXL1_setSyncMsg(USART_6,POSITION,2,	                          
//									0x02,2748 + Vy,
//									0x08,2748 + Vy);  
//	vTaskDelay(220);	


//	DXL1_setSyncMsg(USART_6,POSITION,8,0x01,2648,0x03,2648,0x05,2648,0x07,2648,
//                                     0x09,2648,0x0A,2648,0x0B,2648,0x0C,2648);

//	vTaskDelay(50);
//	DXL1_setSyncMsg(USART_6,POSITION,4,0x02,2648,0x04,2648,0x06,2648,0x08,2648);
//	vTaskDelay(420);
//	
//	DXL1_setSyncMsg(USART_6,POSITION,8,0x01,2648 + Vy,
//	                                   0x03,2648 + Vy,
//																	   0x05,2648 - Vy,
//																	   0x07,2648 - Vy,
//                                     0x09,2648 + Vx + Omega,
//	                                   0x0A,2648 + Vx + Omega,
//																	   0x0B,2648 - Vx + Omega,
//																	   0x0C,2648 - Vx + Omega);																 
//	vTaskDelay(5);
//	DXL1_setSyncMsg(USART_6,POSITION,4,	                         
//	                0x02,2648 + Vy,
//	                0x04,2648 + Vy,
//									0x06,2648 + Vy,
//									0x08,2648 + Vy);   
//	vTaskDelay(420);		
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
//	uint8_t Data[2]={0x24,0x02};
	
//	DXL1_setSyncTarAng(USART_6,4,0x01,2648,0x03,2648,0x05,2648,0x07,2648);
//	vTaskDelay(80);
//	DXL1_setSyncTarAng(USART_6,4,0x02,2648,0x04,2648,0x06,2648,0x08,2648);
//	vTaskDelay(220);

//	DXL1_setSyncTarAng(USART_6,4,0x01,2648,0x03,2648,0x05,2648,0x07,2648);
//	vTaskDelay(5);
//	DXL1_setSyncTarAng(USART_6,4,0x02,2648,0x04,2648,0x06,2648,0x08,2648);  
//	vTaskDelay(220);
		
	DXL1_setSyncMsg(USART_6,POSITION,4,0x01,2648,0x03,2648,0x05,2648,0x07,2648);
	vTaskDelay(80);
	DXL1_setSyncMsg(USART_6,POSITION,4,0x02,2648,0x04,2648,0x06,2648,0x08,2648);
	vTaskDelay(220);

	DXL1_setSyncMsg(USART_6,POSITION,4,0x01,2750,0x03,2648,0x05,2648,0x07,2648);
	vTaskDelay(5);
	DXL1_setSyncMsg(USART_6,POSITION,4,0x02,2750,0x04,2648,0x06,2648,0x08,2648);  
	vTaskDelay(220);
	
//	 DXL1_setSyncMsg(USART_6,POSITION,2,0x01,2048,0x02,2648);
//	 vTaskDelay(500);
//	 DXL1_setSyncMsg(USART_6,POSITION,2,0x01,2048,0x02,1548);
//	 vTaskDelay(500);
//	 DXL1_setMassage(USART_6,0x01,4,2,Data);

//	 USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
//	 USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
//	 vTaskDelay(10);
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



/*-----------------------------------FILE OF END------------------------------*/






