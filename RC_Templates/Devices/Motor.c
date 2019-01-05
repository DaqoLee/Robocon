/*
 *******************************************************************************
 * @file    Motor.c
 * @author  Daqo Lee
 * @version V1.1
 * @date    2019/1/1
 * @brief   电机报文解析与电流设定相关函数
 *
 *******************************************************************************
 * @attention
 *
 *******************************************************************************
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
static void M6020_setTargetAngle(float Ratio ,uint8_t Motor_ID, int16_t DR16_chx);
/******************************************************************************/
/*
 * @brief  电机参数初始化
 * @param	 None
 * @retval None
 */
void MotorParamInit(void)
{
	Motor.M6020[1].targetAngle = 4000;
	Motor.p_M6020setCur = M6020_setCurrent;
	Motor.p_M3508setCur = M3508_setCurrent;
	Motor.p_M2006setCur = M2006_setCurrent;
	
	Motor.p_M6020setTarAngle=M6020_setTargetAngle;
	
	Motor.p_M6020getMsg = M6020_getMessage;
	Motor.p_M3508getMsg = M3508_getMessage;
	Motor.p_M2006getMsg = M2006_getMessage;
	Motor.p_M6623getMsg = M6623_getMessage;

	PID_StructInit(&Motor.M6020[0].OutPID,POSITION_PID, \
	                                      20000, 500, 10.0f,  0.1f, 2.8f);
	PID_StructInit(&Motor.M6020[1].OutPID,POSITION_PID, \
	                                      25000, 5000, 10.0f, 1.0f, 5.0f);                             
}

/*
 * @brief 解析3508报文
 * @param	[in] RxMessage: CAN报文
 * @retval None
 */
static void M3508_getMessage(CanRxMsg RxMessage)
{
	uint8_t stdId = 0;
	if(RxMessage.StdId<M3508_ID_START||RxMessage.StdId>M3508_ID_END)
		return;
	stdId = RxMessage.StdId-M3508_ID_START;
	Motor.M3508[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 \
	                                        | RxMessage.Data[1]);
	Motor.M3508[stdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 \
	                                       | RxMessage.Data[3]);
	Motor.M3508[stdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 \
	                                         | RxMessage.Data[5]);
	Motor.M3508[stdId].temperture = RxMessage.Data[6];
}

/*
 * @brief 解析2006报文
 * @param	[in] RxMessage: CAN报文
 * @retval None
 */
static void M6623_getMessage(CanRxMsg RxMessage)
{
	uint8_t stdId = 0;
	if(RxMessage.StdId<M6623_ID_START||RxMessage.StdId>M6623_ID_END)
		return;
	stdId = RxMessage.StdId-M6623_ID_START;
	Motor.M6623[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 \
	                                        | RxMessage.Data[1]);
	Motor.M6623[stdId].realCurrent = (int16_t)(RxMessage.Data[2]<<8 \
	                                         | RxMessage.Data[3]);
	
}

/*
 * @brief 解析2006报文
 * @param	[in] RxMessage: CAN报文
 * @retval None
 */
static void M6020_getMessage(CanRxMsg RxMessage)
{
	uint8_t stdId = 0;
	if(RxMessage.StdId<M6623_ID_START||RxMessage.StdId>M6623_ID_END)
		return;
	stdId = RxMessage.StdId-M6623_ID_START;
	Motor.M6020[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 \
	                                        | RxMessage.Data[1]);
	Motor.M6020[stdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 \
	                                       | RxMessage.Data[3]);
	Motor.M6020[stdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 \
	                                        | RxMessage.Data[5]);
	Motor.M6020[stdId].temperture = (uint16_t)RxMessage.Data[6];
	
}

/*
 * @brief 解析2006报文
 * @param	[in] RxMessage: CAN报文
 * @retval None
 */
static void M2006_getMessage(CanRxMsg RxMessage)
{
	uint8_t stdId = 0;
	if(RxMessage.StdId<M3508_ID_START||RxMessage.StdId>M3508_ID_END)
		return;
	stdId = RxMessage.StdId-M3508_ID_START;
	Motor.M3508[stdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 \
	                                        | RxMessage.Data[1]);
	Motor.M3508[stdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 \
	                                       | RxMessage.Data[3]);
	Motor.M3508[stdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 \
	                                         | RxMessage.Data[5]);
	Motor.M3508[stdId].temperture = RxMessage.Data[6];
}

/*
 * @brief  设定6020电流
 * @param	[in] CANx: CAN1/CAN2
 * @retval None
 */
static void M6020_setCurrent(CANx_e CANx)
{
	static CanSend_t canSendData;
	
	canSendData.CANx = CANx;
	canSendData.SendCanTxMsg.DLC = 8;
	canSendData.SendCanTxMsg.IDE = CAN_ID_STD;
	canSendData.SendCanTxMsg.RTR = CAN_RTR_Data;
	canSendData.SendCanTxMsg.StdId = 0x1FF;
	canSendData.SendCanTxMsg.Data[0] = Motor.M6020[0].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[1] = Motor.M6020[0].targetCurrent ;
	canSendData.SendCanTxMsg.Data[2] = Motor.M6020[1].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[3] = Motor.M6020[1].targetCurrent ;
	
	xQueueSend(xCanSendQueue, &canSendData, 20);

}

/*
 * @brief  设定3508电流
 * @param	[in] CANx: CAN1/CAN2
 * @retval None
 */
static void M3508_setCurrent(CANx_e CANx)
{
	static CanSend_t canSendData;
	
	canSendData.CANx = CANx;
	canSendData.SendCanTxMsg.DLC = 8;
	canSendData.SendCanTxMsg.IDE = CAN_ID_STD;
	canSendData.SendCanTxMsg.RTR = CAN_RTR_Data;
	canSendData.SendCanTxMsg.StdId = 0x200;
	canSendData.SendCanTxMsg.Data[0] = Motor.M3508[0].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[1] = Motor.M3508[0].targetCurrent ;
	canSendData.SendCanTxMsg.Data[2] = Motor.M3508[1].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[3] = Motor.M3508[1].targetCurrent ;
	canSendData.SendCanTxMsg.Data[4] = Motor.M3508[2].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[5] = Motor.M3508[2].targetCurrent ;
	canSendData.SendCanTxMsg.Data[6] = Motor.M3508[3].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[7] = Motor.M3508[3].targetCurrent ;
	
	xQueueSend(xCanSendQueue, &canSendData, 20);
}

/*
 * @brief  设定2006电流
 * @param	[in] CANx: CAN1/CAN2
 * @retval None
 */
static void M2006_setCurrent(CANx_e CANx)
{
	static CanSend_t canSendData;
	
	canSendData.CANx = CANx;
	canSendData.SendCanTxMsg.DLC = 8;
	canSendData.SendCanTxMsg.IDE = CAN_ID_STD;
	canSendData.SendCanTxMsg.RTR = CAN_RTR_Data;
	canSendData.SendCanTxMsg.StdId = 0x200;
	
	canSendData.SendCanTxMsg.Data[0] = Motor.M2006[0].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[1] = Motor.M2006[0].targetCurrent ;
	canSendData.SendCanTxMsg.Data[2] = Motor.M2006[1].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[3] = Motor.M2006[1].targetCurrent ;
	canSendData.SendCanTxMsg.Data[4] = Motor.M2006[2].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[5] = Motor.M2006[2].targetCurrent ;
	canSendData.SendCanTxMsg.Data[6] = Motor.M2006[3].targetCurrent >> 8;
	canSendData.SendCanTxMsg.Data[7] = Motor.M2006[3].targetCurrent ;
	
	xQueueSend(xCanSendQueue, &canSendData, 20);
}

/*
 * @brief  设置6020目标角度
 * @param  [in] Ratio     遥控通道累加的倍率
 *         [in] Motor_ID  电机ID
 *         [in] DR16_chx  遥控通道
 * @retval None
 */
static void M6020_setTargetAngle(float Ratio ,uint8_t Motor_ID, int16_t DR16_chx)
{
  static int16_t targetAngle = 0;

	targetAngle = targetAngle > 8191 ? targetAngle - 8191 : targetAngle \
	                                                 + Ratio * DR16_chx;
	targetAngle = targetAngle < 0 ? 8191 + targetAngle : targetAngle \
	                                              + Ratio * DR16_chx;

	Motor.M6020[Motor_ID].targetAngle = targetAngle;

}


/*
 * @brief  设置6020角度幅值
 * @param  [in] Ratio     遥控通道累加的倍率
 *         [in] Motor_ID  电机ID
 *         [in] DR16_chx  遥控通道
 * @retval None
 */
static void M6020_setLimitAngle(void)
{
	const static uint16_t m6020Mini=(M6020_RANGE/2);
	const static uint16_t m6020Max=(8191-m6020Mini);



}
/******************************************************************************/

