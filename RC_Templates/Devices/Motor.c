/**
  ************************************* Copyright ****************************** 
  *
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *                              
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *    
  * FileName   : Motor.c   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-21         
  * Description: 电机   
  * Function List:  
  	1. ....
  	   <version>: 		
  <modify staff>:
  		  <data>:
   <description>:  
  	2. ...
  ******************************************************************************
 */


#include "Motor.h"
#include "Task_CanSend.h"
/******************************************************************************/
M3508_t M3508[4];
M6623_t M6623[2];
M6020_t M6020[2];
M2006_t M2006;
/******************************************************************************/

void MotorParamInit(void)
{
	M6020[0].targetCurrent=1000;
	M6020[1].targetAngle=4000;
	PID_StructInit(&M6020[0].OutPID,POSITION_PID, 20000, 500, 10.0f,	1.0f, 2.8f);
	PID_StructInit(&M6020[1].OutPID,POSITION_PID, 20000, 500, 10.0f,	1.0f, 2.8f);                             
}


/******************************************************************************/
void M3508_DataDecode(CanRxMsg RxMessage)
{
	uint8_t stdId=0;
	if(RxMessage.StdId<M3508_ID_START||RxMessage.StdId>M3508_ID_END)
		return;
	stdId=RxMessage.StdId-M3508_ID_START;
	M3508[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	M3508[stdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	M3508[stdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
	M3508[stdId].temperture = RxMessage.Data[6];
}

/******************************************************************************/

void M6623_DataDecode(CanRxMsg RxMessage)
{
	uint8_t stdId=0;
	if(RxMessage.StdId<M6623_ID_START||RxMessage.StdId>M6623_ID_END)
		return;
	stdId=RxMessage.StdId-M6623_ID_START;
	M6623[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	M6623[stdId].realCurrent = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	
}

/******************************************************************************/

void M6020_DataDecode(CanRxMsg RxMessage)
{
	uint8_t stdId=0;
	if(RxMessage.StdId<M6623_ID_START||RxMessage.StdId>M6623_ID_END)
		return;
	stdId=RxMessage.StdId-M6623_ID_START;
	M6020[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	M6020[stdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	M6020[stdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
	M6020[stdId].temperture=(uint16_t)RxMessage.Data[6];
	
}

/******************************************************************************/

void M2006_DataDecode(CanRxMsg RxMessage)
{
	uint8_t stdId=0;
	if(RxMessage.StdId<M3508_ID_START||RxMessage.StdId>M3508_ID_END)
		return;
	stdId=RxMessage.StdId-M3508_ID_START;
	M3508[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	M3508[stdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	M3508[stdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
	M3508[stdId].temperture = RxMessage.Data[6];
}

/******************************************************************************/
void setM6020Current(void)
{
	static CanSend_t CANSendData;
	
	M6020[1].targetCurrent=PID_Calc(&M6020[1].OutPID,M6020[1].realAngle, 
	                                                 M6020[1].targetAngle);
	
	CANSendData.CANx=1;
	CANSendData.SendCanTxMsg.DLC   =   8;
	CANSendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
	CANSendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
	CANSendData.SendCanTxMsg.StdId =  0x1FF;
	CANSendData.SendCanTxMsg.Data[0]=M6020[0].targetCurrent >> 8;
	CANSendData.SendCanTxMsg.Data[1]=M6020[0].targetCurrent ;
	CANSendData.SendCanTxMsg.Data[2]=M6020[1].targetCurrent >> 8;
	CANSendData.SendCanTxMsg.Data[3]=M6020[1].targetCurrent ;
	
	xQueueSend(xCanSendQueue, &CANSendData, 20);
}

/******************************************************************************/

