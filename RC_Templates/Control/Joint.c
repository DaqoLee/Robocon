#include "Joint.h"
#include "Motor.h"
/******************************************************************************/

/******************************************************************************/


void Thigh_M6020Ctrl(void)
{
	for(uint8_t i=0;i<4;i++)
	{
		M6020[i].targetCurrent=PID_Calc(&M6020[i].OutPID,M6020[i].realAngle, 
	                                                 M6020[i].targetAngle);
	}
	M6020[0].funSetCurrent(CAN_1);
	M6020_setCurrent(CAN_1);
}

/******************************************************************************/

