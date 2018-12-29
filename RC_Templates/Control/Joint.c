#include "Joint.h"
#include "Motor.h"
/******************************************************************************/

/******************************************************************************/


void Thigh_M6020Ctrl()
{
	M6020[0].targetCurrent=PID_Calc(&M6020[0].OutPID,M6020[0].realAngle, 
	                                                 M6020[0].targetAngle);
	M6020[1].targetCurrent=PID_Calc(&M6020[1].OutPID,M6020[1].realAngle, 
	                                                 M6020[1].targetAngle);
	M6020_setCurrent(CAN_1);
}

/******************************************************************************/

