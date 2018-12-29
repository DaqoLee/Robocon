#include "Chassis.h"
/******************************************************************************/
#define MECANUM   1  /*麦克纳姆轮*/
#define THROMNI		0  /*三轮全向*/
#define FOROMNI		0  /*四轮全向*/

#define PI        3.141592653589
/******************************************************************************/
const float Radian=PI/6;
	
/******************************************************************************/

void ChassisMotionModel(float Vx, float Vy, float Omega, int16_t *Speed)								
{
#if   MECANUM == 1
  Speed[0] = -Vx - Vy + Omega;
  Speed[1] = -Vx + Vy + Omega;
  Speed[2] =  Vx + Vy + Omega;
  Speed[3] =  Vx - Vy + Omega;
#elif	THROMNI == 1
	Speed[0] = -Vx + Omega;
  Speed[1] =  Vx*sin(Radian) - Vycos(Radian) + Omega;
  Speed[2] =  Vx*sin(Radian) + Vycos(Radian) + Omega;
#elif FOROMNI == 1
	Speed[0] = -Vx - Vy + Omega;
  Speed[1] = -Vx + Vy + Omega;
  Speed[2] =  Vx + Vy + Omega;
  Speed[3] =  Vx - Vy + Omega;
	
#endif

}

/******************************************************************************/

