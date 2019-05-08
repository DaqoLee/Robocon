/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|--FileName    : Camera.c                                              
|--Version     : v1.0                                                          
|--Author      : Daqo Lee                                                     
|--Date        : 2019-03-17             
|--Libsupports : STM32F4xx_DFP ( 2.9.0)
|--Description :                                                     
|-----------------------------declaration of end-----------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Camera.h" 
  
/*-------------------------- D E F I N E S -----------------------------------*/

Camera_t Camera;

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/



/*------------------G L O B A L - F U N C T I O N S --------------------------*/

void Camera_getMassage(uint8_t *CameraBuff)
{
  for(uint8_t i=0;i<15;i++)
	{
		if(CameraBuff[i]=='$')
		{
		  if(CameraBuff[i+4] == ',' && CameraBuff[i+8] == ',')
			{
				if(CameraBuff[i+1]=='0')
				{
					Camera.Angle =  ((CameraBuff[i+2] - '0') * 10
							           + (CameraBuff[i+3] - '0'))*-1;
				}
				else
        {
					Camera.Angle = (CameraBuff[i+2] - '0') * 10
					               + (CameraBuff[i+3] - '0');
				}


				Camera.Offset =
			  	(CameraBuff[i+5] - '0') * 100
			  +	(CameraBuff[i+6] - '0') * 10
        + (CameraBuff[i+7] - '0');

				Camera.Flag = CameraBuff[i+9] - '0';
			}
			else
			{
				
			}
			
		}
	}
}

/*---------------------L O C A L - F U N C T I O N S--------------------------*/



/*-----------------------------------file of end------------------------------*/


