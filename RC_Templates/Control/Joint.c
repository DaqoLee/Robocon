#include "Joint.h"
#include "Motor.h"
#include "DR16.h"

/******************************************************************************/

/******************************************************************************/


void Thigh_M6020Ctrl(void)
{
	Motor.M6020[1].targetAngle+=0.01*DR16.ch1;
	
	for(uint8_t i=0;i<4;i++)
	{
		Motor.M6020[i].targetCurrent=PID_Calc(&Motor.M6020[i].OutPID, \
		                                       Motor.M6020[i].realAngle, 
	                                         Motor.M6020[i].targetAngle);
	}
	Motor.pM6020SetCur(CAN_1);
}

/******************************************************************************/

