#include "Chassis.h"
#include  "math.h"
/******************************************************************************/
#define MECANUM   0  /*麦克纳姆轮*/
#define THROMNI		1  /*三轮全向*/
#define FOROMNI		0  /*四轮全向*/

#define PI        3.141592653589
/******************************************************************************/
const float Radian=PI/6;
	
/******************************************************************************/

/*
 * @brief  底盘运动模型分解
 * @param  [in] Vx     X 轴方向速度
 *         [in] Vy     Y 轴方向速度
 *         [in] Omega  自旋速度
 *         [in] *Speed 速度分解缓存 
 * @retval None
 */
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

