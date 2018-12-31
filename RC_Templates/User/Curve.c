#include "Curve.h"
#include "Encoder.h"
#include "math.h"

#define LEN  1000


/******************************************************************************/
 /*
  * @brief None
  * @param None
  * @retval None
  */
void Curve_Straight(void)
{
	static float xCoords=1120.0f,yCoords=0.0f;
	
	yCoords=Posture.realY_Coords+\
	        sqrt(LEN*LEN-(pow(Posture.realX_Coords-xCoords,2)));
	
	Posture.targetX_Coords=xCoords;
	Posture.targetY_Coords=yCoords;
	
}
/******************************************************************************/
 /*
  * @brief None
  * @param None
  * @retval None
  */
void Curve_Circle(float r,float a, float b)
{
	static float Len=0.0f,k=0.0f;
  Len=sqrt(pow((Posture.realX_Coords-a),2)-pow((Posture.realY_Coords-b),2));
	if(Len>r)
	{
	  k=(Posture.realY_Coords-b)/(Posture.realX_Coords-a);
	}
	else
	{
	
	}
}


/******************************************************************************/

