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
#include "Task_Can.h"
/******************************************************************************/
Motor_t Motor;
/******************************************************************************/
static void M3508_getMessage(CanRxMsg RxMessage);
static void M2006_getMessage(CanRxMsg RxMessage);
static void M6020_getMessage(CanRxMsg RxMessage);
static void M6623_getMessage(CanRxMsg RxMessage);

static void M3508_setCurrent(CANx_e CANx);
static void M2006_setCurrent(CANx_e CANx);
static void M6020_setCurrent(CANx_e CANx);

/******************************************************************************/


void MotorParamInit(void)
{

	Motor.M6020[1].targetAngle=4000;
	
	Motor.pM6020SetCur=M6020_setCurrent;
	Motor.pM3508SetCur=M3508_setCurrent;
	Motor.pM2006SetCur=M2006_setCurrent;
	
	Motor.pM6020getMsg=M6020_getMessage;
	Motor.pM3508getMsg=M3508_getMessage;
	Motor.pM2006getMsg=M2006_getMessage;
	Motor.pM6623getMsg=M6623_getMessage;
	
	
	PID_StructInit(&Motor.M6020[0].OutPID,POSITION_PID, 20000, 500, 10.0f,  0.1f, 2.8f);
	PID_StructInit(&Motor.M6020[1].OutPID,POSITION_PID, 25000, 5000, 10.0f, 1.0f, 5.0f);                             
}


/******************************************************************************/
static void M3508_getMessage(CanRxMsg RxMessage)
{
	uint8_t stdId=0;
	if(RxMessage.StdId<M3508_ID_START||RxMessage.StdId>M3508_ID_END)
		return;
	stdId=RxMessage.StdId-M3508_ID_START;
	Motor.M3508[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	Motor.M3508[stdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	Motor.M3508[stdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
	Motor.M3508[stdId].temperture = RxMessage.Data[6];
}

/******************************************************************************/

static void M6623_getMessage(CanRxMsg RxMessage)
{
	uint8_t stdId=0;
	if(RxMessage.StdId<M6623_ID_START||RxMessage.StdId>M6623_ID_END)
		return;
	stdId=RxMessage.StdId-M6623_ID_START;
	Motor.M6623[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	Motor.M6623[stdId].realCurrent = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	
}

/******************************************************************************/

static void M6020_getMessage(CanRxMsg RxMessage)
{
	uint8_t stdId=0;
	if(RxMessage.StdId<M6623_ID_START||RxMessage.StdId>M6623_ID_END)
		return;
	stdId=RxMessage.StdId-M6623_ID_START;
	Motor.M6020[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	Motor.M6020[stdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	Motor.M6020[stdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
	Motor.M6020[stdId].temperture=(uint16_t)RxMessage.Data[6];
	
}

/******************************************************************************/

static void M2006_getMessage(CanRxMsg RxMessage)
{
	uint8_t stdId=0;
	if(RxMessage.StdId<M3508_ID_START||RxMessage.StdId>M3508_ID_END)
		return;
	stdId=RxMessage.StdId-M3508_ID_START;
	Motor.M3508[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	Motor.M3508[stdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	Motor.M3508[stdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);
	Motor.M3508[stdId].temperture = RxMessage.Data[6];
}

/******************************************************************************/
static void M6020_setCurrent(CANx_e CANx)
{
	static CanSend_t canSendData;
	
	canSendData.CANx=CANx;
	canSendData.SendCanTxMsg.DLC   =   8;
	canSendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
	canSendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
	canSendData.SendCanTxMsg.StdId =  0x1FF;
	canSendData.SendCanTxMsg.Data[0]=Motor.M6020[0].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[1]=Motor.M6020[0].targetCurrent ;
	canSendData.SendCanTxMsg.Data[2]=Motor.M6020[1].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[3]=Motor.M6020[1].targetCurrent ;
	
	xQueueSend(xCanSendQueue, &canSendData, 20);

}

/******************************************************************************/

static void M3508_setCurrent(CANx_e CANx)
{
	static CanSend_t canSendData;
	
	canSendData.CANx=CANx;
	canSendData.SendCanTxMsg.DLC   =   8;
	canSendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
	canSendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
	canSendData.SendCanTxMsg.StdId =  0x200;
	canSendData.SendCanTxMsg.Data[0]=Motor.M3508[0].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[1]=Motor.M3508[0].targetCurrent ;
	canSendData.SendCanTxMsg.Data[2]=Motor.M3508[1].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[3]=Motor.M3508[1].targetCurrent ;
	canSendData.SendCanTxMsg.Data[4]=Motor.M3508[2].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[5]=Motor.M3508[2].targetCurrent ;
	canSendData.SendCanTxMsg.Data[6]=Motor.M3508[3].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[7]=Motor.M3508[3].targetCurrent ;
	
	xQueueSend(xCanSendQueue, &canSendData, 20);
}

/******************************************************************************/

static void M2006_setCurrent(CANx_e CANx)
{
	static CanSend_t canSendData;
	
	canSendData.CANx=CANx;
	canSendData.SendCanTxMsg.DLC   =   8;
	canSendData.SendCanTxMsg.IDE   =   CAN_ID_STD;
	canSendData.SendCanTxMsg.RTR   =   CAN_RTR_Data;
	canSendData.SendCanTxMsg.StdId =  0x200;
	
	canSendData.SendCanTxMsg.Data[0]=Motor.M2006[0].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[1]=Motor.M2006[0].targetCurrent ;
	canSendData.SendCanTxMsg.Data[2]=Motor.M2006[1].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[3]=Motor.M2006[1].targetCurrent ;
	canSendData.SendCanTxMsg.Data[4]=Motor.M2006[2].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[5]=Motor.M2006[2].targetCurrent ;
	canSendData.SendCanTxMsg.Data[6]=Motor.M2006[3].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[7]=Motor.M2006[3].targetCurrent ;
	
	xQueueSend(xCanSendQueue, &canSendData, 20);
}



