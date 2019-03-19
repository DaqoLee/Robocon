/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Chassis.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-02-20               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Chassis.h"
#include "RoboModule.h"
#include  "math.h"
#include "FreeRTOS.h"
#include "task.h"
#include "DR16.h"
/*-------------------------- D E F I N E S -----------------------------------*/
#define MECANUM   0  /*麦克纳姆轮*/
#define THROMNI		1  /*三轮全向*/
#define FOROMNI		0  /*四轮全向*/

#define PI        3.141592653589

const float Radian=PI/6;
/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/



/*------------------G L O B A L - F U N C T I O N S --------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
  /**
  * @Data    2019-02-20 16:59
  * @brief  底盘运动模型分解
  * @param  [in] Vx     X 轴方向速度
  *         [in] Vy     Y 轴方向速度
  *         [in] Omega  自旋速度
  *         [in] *Speed 速度分解缓存 
  * @retval None
  */
void Chassis_MotionModel(float Vx, float Vy, float Omega, int16_t *Speed)								
{
#if   MECANUM == 1
  Speed[0] = -Vx - Vy + Omega;
  Speed[1] = -Vx + Vy + Omega;
  Speed[2] =  Vx + Vy + Omega;
  Speed[3] =  Vx - Vy + Omega;
#elif	THROMNI == 1
	Speed[0] = -Vx + Omega;
  Speed[1] =  Vx*sin(Radian) - Vy*cos(Radian) + Omega;
  Speed[2] =  Vx*sin(Radian) + Vy*cos(Radian) + Omega;
#elif FOROMNI == 1
	Speed[0] = -Vx - Vy + Omega;
  Speed[1] = -Vx + Vy + Omega;
  Speed[2] =  Vx + Vy + Omega;
  Speed[3] =  Vx - Vy + Omega;
	
#endif

}

/*---------------------L O C A L - F U N C T I O N S--------------------------*/

/**
  * @Data    2019-03-19 10:56
  * @brief   底盘参数初始化
  * @param   void
  * @retval  void
  */
  void Chassis_Init(void)
  {
    RoboModule_DRV_Reset(0,1);
    RoboModule_DRV_Reset(0,2);
    RoboModule_DRV_Reset(0,3);

    vTaskDelay(1000);
    RoboModule_DRV_Mode_Choice(0,1,Velocity_Mode);
    RoboModule_DRV_Mode_Choice(0,2,Velocity_Mode);
    RoboModule_DRV_Mode_Choice(0,3,Velocity_Mode);
  }
/**
  * @Data    2019-03-19 11:08
  * @brief   
  * @param   void
  * @retval  void
  */
  void Chassis_Ctrl(void)
  {
    int16_t velBuff[3];

    Chassis_MotionModel(DR16.ch1,DR16.ch2,DR16.ch3,velBuff);
    RoboModule_DRV_Velocity_Mode(0,1,1000,velBuff[0]);
    RoboModule_DRV_Velocity_Mode(0,2,1000,velBuff[1]);
    RoboModule_DRV_Velocity_Mode(0,3,1000,velBuff[2]);
  }
/*-----------------------------------FILE OF END------------------------------*/

