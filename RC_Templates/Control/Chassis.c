#include "Chassis.h"
#include  "math.h"
/******************************************************************************/
#define MECANUM   0  /*�����ķ��*/
#define THROMNI		1  /*����ȫ��*/
#define FOROMNI		0  /*����ȫ��*/

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
  Speed[1] =  Vx*sin(Radian) - Vy*cos(Radian) + Omega;
  Speed[2] =  Vx*sin(Radian) + Vy*cos(Radian) + Omega;
#elif FOROMNI == 1
	Speed[0] = -Vx - Vy + Omega;
  Speed[1] = -Vx + Vy + Omega;
  Speed[2] =  Vx + Vy + Omega;
  Speed[3] =  Vx - Vy + Omega;
	
#endif

}

/******************************************************************************/

