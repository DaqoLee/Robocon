/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Curve.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-03-03               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/

#include "Curve.h"
#include "Encoder.h"
#include <math.h>
/*-------------------------- D E F I N E S -----------------------------------*/



/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/



/*------------------G L O B A L - F U N C T I O N S --------------------------*/





/*------------------------------80 Chars Limit--------------------------------*/
  /**
  * @Data    2019-03-03 13:05
  * @brief   
  * @param   void
  * @retval  void
  */
void Curve_Straight(void)
{
	static float xCoords=1120.0f,yCoords=0.0f;
	
	yCoords=Posture.realY_Coords+\
	        sqrt(LEN*LEN-(pow(Posture.realX_Coords-xCoords,2)));
	
	Posture.targetX_Coords=xCoords;
	Posture.targetY_Coords=yCoords;
	
}


/*------------------------------80 Chars Limit--------------------------------*/
  /**
  * @Data    2019-03-03 13:05
  * @brief   
  * @param   void
  * @retval  void
  */
float Curve_Bezier(uint8_t *x,uint8_t n,float t)
{
  for(;n>0;n--)
	{
		for(uint8_t i=0;i<n;i++)
		{
			x[i]=((1-t)*x[i]+t*x[i+1]);
		}

	}
  return x[0];
}

float Curve_Sin(float A,float w,float fi,float b,float pi)
{
  return (A*sin(w*pi+fi*PI)+b);
}

/*---------------------L O C A L - F U N C T I O N S--------------------------*/



/*-----------------------------------FILE OF END------------------------------*/



