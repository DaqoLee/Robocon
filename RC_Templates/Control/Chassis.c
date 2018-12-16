#include "Chassis.h"
/******************************************************************************/
 /*
  * @brief �����ķ���˶�ģ��
  * @param Vx X�᷽����ٶȣ�Vy Y�᷽����ٶȣ�Omega �����ٶȣ�*Speed����ת��
  * @retval None
  */
void MecanumCalculate(float Vx, float Vy, float Omega, int16_t *Speed)
{
	static float Buffer[4];
	static uint16_t MaxWheelSpeed=6600;
  float  Param, MaxSpeed;
  uint8_t index;
    
  Buffer[0] = -Vx - Vy + Omega;
  Buffer[1] = -Vx + Vy + Omega;
  Buffer[2] =  Vx + Vy + Omega;
  Buffer[3] =  Vx - Vy + Omega;
    
    //�޷�
	for(index = 0, MaxSpeed = 0; index < 4; index++)
	{
		if((Buffer[index] > 0 ? Buffer[index] : -Buffer[index]) > MaxSpeed)
		{
				MaxSpeed = (Buffer[index] > 0 ? Buffer[index] : -Buffer[index]);
		}
	}	

	if(MaxWheelSpeed < MaxSpeed)
	{
		Param = (float)MaxWheelSpeed / MaxSpeed;
		Speed[0] = Buffer[0] * Param;
		Speed[1] = Buffer[1] * Param;
		Speed[2] = Buffer[2] * Param;
		Speed[3] = Buffer[3] * Param; 
	}
	else
	{
		Speed[0] = Buffer[0];
		Speed[1] = Buffer[1];
		Speed[2] = Buffer[2];
		Speed[3] = Buffer[3];
	}
}

void Chassis_Algorithm_Model(float Vx, float Vy, float Omega, int16_t *Speed)								
{



}

