#include "BSP_I2C.h"


void BSP_I2C2_Init(void)
{

  I2C_InitTypeDef   I2C_InitStructure;
  BSP_I2C2_GPIOInit();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
	I2C_DeInit(I2C2);//使用I2C2
	I2C_InitStructure.I2C_Mode                = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle           = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1         = 0x30;//主机的I2C地址,随便写的
	I2C_InitStructure.I2C_Ack                 = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed          = 400000;//400K

	I2C_Cmd(I2C2, ENABLE);
	I2C_Init(I2C2, &I2C_InitStructure);
}


void I2C_WriteByte(uint8_t addr,uint8_t data)
{
  while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(I2C2, ENABLE);//开启I2C2
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

	I2C_Send7bitAddress(I2C2, 0x78, I2C_Direction_Transmitter);  //器件地址 -- 默认0x78
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C2, addr);//寄存器地址
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C2, data);//发送数据
	while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_GenerateSTOP(I2C2, ENABLE);//关闭I2C2总线
}
