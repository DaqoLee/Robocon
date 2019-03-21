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
#include "math.h"
#include "DR16.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Encoder.h"
#include "Curve.h"
/*-------------------------- D E F I N E S -----------------------------------*/
const float Radian=PI/6;

Chassis_t Chassis;
//const float Cure[]={
//0.566806, 0.632099, 0.694312, 0.753091, 0.808253, 
//0.859476, 0.906511, 0.949128, 0.987119, 1.020272, 
//1.048485, 1.071588, 1.089468, 1.102039, 1.109236, 
//1.111035, 1.107420, 1.098407, 1.084042, 1.064394, 
//1.039582, 1.009685, 0.974866, 0.935297, 0.891170, 
//0.842744, 0.790171, 0.733746, 0.673746, 0.610462, 
//0.544203, 0.475354, 0.404128, 0.330933, 0.256126, 
//0.180070, 0.103204, 0.025768, -0.051793, -0.129102, 
//-0.205782, -0.281459, -0.355700, -0.428273, -0.498759, 
//-0.566814, -0.632107, -0.694267, -0.753099, -0.808260, 
//-0.859483, -0.906517, -0.949133, -0.987092, -1.020276, 
//-1.048488, -1.071590, -1.089470, -1.102041, -1.109236, 
//-1.111035, -1.107419, -1.098406, -1.084040, -1.064410, 
//-1.039579, -1.009680, -0.974862, -0.935292, -0.891164, 
//-0.842738, -0.790164, -0.733739, -0.673738, -0.610454, 
//-0.544254, -0.475345, -0.404119, -0.330924, -0.256116, 
//-0.180060, -0.103194, -0.025758, 0.051803, 0.129112, 
//0.205792, 0.281468, 0.355709, 0.428282, 0.498768, 
//0.566823, 0.632115, 0.694274, 0.753106, 0.808267, 
//0.859489, 0.906522, 0.949138, 0.987097, 1.020280, 
//1.048492, 1.071593, 1.089472, 1.102042, 1.109237, 
//1.111035, 1.107418, 1.098404, 1.084038, 1.064407, 
//1.039575, 1.009676, 0.974857, 0.935287, 0.891158, 
//0.842731, 0.790157, 0.733731, 0.673730, 0.610446, 
//0.544245, 0.475336, 0.404110, 0.330915, 0.256107, 
//0.180050, 0.103184, 0.025748, -0.051813, -0.129122, 
//-0.205801, -0.281478, -0.355719, -0.428291, -0.498777, 
//-0.566831, -0.632124, -0.694282, -0.753113, -0.808274, 
//-0.859495, -0.906528, -0.949143, -0.987101, -1.020284, 
//-1.048495, -1.071596, -1.089474, -1.102043, -1.109237, 
//-1.111035, 
//};

const float Cure[]={
-0.497919, -0.427406, -0.354810, -0.280550, -0.204859, 
-0.128169, -0.050855, 0.026707, 0.104139, 0.180997, 
0.257040, 0.331830, 0.405003, 0.476203, 0.545022, 
0.611247, 0.674493, 0.734451, 0.790831, 0.843356, 
0.891731, 0.935804, 0.975317, 1.010076, 1.039913, 
1.064663, 1.084248, 1.098548, 1.107496, 1.111045, 
1.109181, 1.101919, 1.089283, 1.071339, 1.048174, 
1.019900, 0.986687, 0.948639, 0.905967, 0.858881, 
0.807608, 0.752400, 0.693578, 0.631326, 0.565998, 
0.497911, 0.427397, 0.354865, 0.280541, 0.204849, 
0.128159, 0.050845, -0.026717, -0.104082, -0.181007, 
-0.257049, -0.331839, -0.405012, -0.476150, -0.545031, 
-0.611255, -0.674501, -0.734459, -0.790838, -0.843318, 
-0.891737, -0.935810, -0.975322, -1.010080, -1.039893, 
-1.064666, -1.084250, -1.098550, -1.107496, -1.111046, 
-1.109184, -1.101918, -1.089281, -1.071336, -1.048170, 
-1.019896, -0.986683, -0.948634, -0.905962, -0.858875, 
-0.807602, -0.752443, -0.693571, -0.631318, -0.565989, 
-0.497902, -0.427388, -0.354855, -0.280531, -0.204839, 
-0.128149, -0.050835, 0.026727, 0.104091, 0.181016, 
0.257059, 0.331849, 0.405022, 0.476159, 0.545039, 
0.611263, 0.674508, 0.734466, 0.790845, 0.843325, 
0.891743, 0.935815, 0.975326, 1.010085, 1.039896, 
1.064668, 1.084252, 1.098551, 1.107497, 1.111046, 
1.109184, 1.101917, 1.089279, 1.071334, 1.048167, 
1.019892, 0.986678, 0.948629, 0.905956, 0.858868, 
0.807595, 0.752436, 0.693563, 0.631310, 0.565981, 
0.497893, 0.427379, 0.354846, 0.280521, 0.204830, 
0.128140, 0.050825, -0.026669, -0.104101, -0.181026, 
-0.257069, -0.331858, -0.405031, -0.476168, -0.545048, 
-0.611272, -0.674516, -0.734474, -0.790852, -0.843331, 
-0.891749, -0.935820, -0.975331, -1.010089, -1.039900, 
-1.064671, -1.084254, -1.098553, -1.107498, -1.111046
};
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
		
    PID_StructInit(&Chassis.PID_X, POSITION_PID, 3000, 500, 2, 0, 0);
    PID_StructInit(&Chassis.PID_Y, POSITION_PID, 3000, 500, 2, 0, 0);
    PID_StructInit(&Chassis.PID_Spin, POSITION_PID, 3000, 500, -50, 0, 0);
		
    Posture.targetZ_Angle=0;
		
  }
/**
  * @Data    2019-03-19 11:08
  * @brief   
  * @param   void
  * @retval  void
  */
  void Chassis_Ctrl(void)
  {
    static uint16_t temp = 0,temp1=0;
    int16_t velBuff[3];
		Posture.targetZ_Angle=0;
#if 0
    Posture.targetX_Coords=DR16.ch1;
		Posture.targetY_Coords=DR16.ch2;

//		
    Chassis.Vx=PID_Calc(&Chassis.PID_X,
                        Posture.realX_Coords,Posture.targetX_Coords);
    Chassis.Vy=PID_Calc(&Chassis.PID_Y,
                        Posture.realY_Coords,Posture.targetY_Coords);
    Chassis.Vspin=PID_Calc(&Chassis.PID_Spin,
                        Posture.realZ_Angle,Posture.targetZ_Angle);
//		
#endif	
#if 0
//		if(temp<160&&DR16.switch_right==3)
//		{
//			Chassis.Vy=-1500;
//			Chassis.Vx=-Chassis.Vy*Cure[temp];
//			Chassis.Vspin=PID_Calc(&Chassis.PID_Spin,
//											 Posture.realZ_Angle,Posture.targetZ_Angle);
//		if(++temp1>3)
//		{
//			temp1=0;
//			temp++;
//		}
//		}
//		else
//		{
//			Chassis.Vx=-10*DR16.ch3;
//      Chassis.Vy=-10*(DR16.ch2+DR16.ch4);
//			Chassis.Vspin=10*DR16.ch1;
//		//	Chassis.Vspin=PID_Calc(&Chassis.PID_Spin,
//      //       Posture.realZ_Angle,Posture.targetZ_Angle);
//		}
#endif

#if 1 /*全场定位跑曲线*/

		if(temp<160&&DR16.switch_right==3)
		{
		  Chassis.Vy=-1500;
		
			if((30*(temp+1))+Posture.realY_Coords<10)
			{
				Chassis.Vx=-Chassis.Vy*Cure[temp];
				temp++;
			}
			Chassis.Vspin=PID_Calc(&Chassis.PID_Spin,
      Posture.realZ_Angle,Posture.targetZ_Angle);
		}
		else
		{
			Chassis.Vx=-10*DR16.ch3;
      Chassis.Vy=-10*(DR16.ch2+DR16.ch4);
			Chassis.Vspin=PID_Calc(&Chassis.PID_Spin,
      Posture.realZ_Angle,Posture.targetZ_Angle);
		}
    
#endif	
    Chassis_MotionModel(Chassis.Vx,Chassis.Vy,Chassis.Vspin,velBuff);

//  Chassis_MotionModel(-10*DR16.ch3,-10*(DR16.ch2+DR16.ch4),10*DR16.ch1,velBuff);
		
		
    RoboModule_DRV_Velocity_Mode(0,1,3000,velBuff[0]);
    RoboModule_DRV_Velocity_Mode(0,2,3000,velBuff[1]);
    RoboModule_DRV_Velocity_Mode(0,3,3000,velBuff[2]);
  }
/*-----------------------------------FILE OF END------------------------------*/

