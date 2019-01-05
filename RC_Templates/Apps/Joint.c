#include "Joint.h"
#include "Motor.h"
#include "DR16.h"

/******************************************************************************/

/******************************************************************************/


void Thigh_M6020Ctrl(void)
{
	Motor.p_M6020setTarAngle(0.01,1,DR16.ch1);
	
	for(uint8_t i=0;i<4;i++)
	{
		Motor.M6020[i].targetCurrent=PID_Calc(&Motor.M6020[i].OutPID, \
		                                       Motor.M6020[i].realAngle, 
	                                         Motor.M6020[i].targetAngle);
	}
	Motor.p_M6020setCur(CAN_1);
}

/******************************************************************************/

