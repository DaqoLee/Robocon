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
/*-------------------------- D E F I N E S -----------------------------------*/



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
	Dynamixel1_setSyncMsg(POSITION,4,0x01,2548,0x03,2548,0x05,2548,0x07,2548);
	vTaskDelay(5);
	Dynamixel1_setSyncMsg(POSITION,4,0x09,2548,0x0A,2548,0x0B,2548,0x0C,2548);
	vTaskDelay(80);
	Dynamixel1_setSyncMsg(POSITION,4,0x02,2548,0x04,2548,0x06,2548,0x08,2548);
	vTaskDelay(220);
	
	Dynamixel1_setSyncMsg(POSITION,4,0x01,2548 + Vy,
	                                 0x03,2548 + Vy,
																	 0x05,2548 - Vy,
																	 0x07,2548 - Vy);
  vTaskDelay(5);
	Dynamixel1_setSyncMsg(POSITION,4,0x09,2548 + Vx + Omega,
	                                 0x0A,2548 + Vx + Omega,
																	 0x0B,2548 - Vx + Omega,
																	 0x0C,2548 - Vx + Omega);																 
	vTaskDelay(5);
	Dynamixel1_setSyncMsg(POSITION,4,0x02,2548 + Vy + Vx + Omega,
	                                 0x04,2548 + Vy + Vx + Omega,
																	 0x06,2548 + Vy + Vx + Omega,
																	 0x08,2548 + Vy + Vx + Omega);   
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



/*-----------------------------------FILE OF END------------------------------*/






