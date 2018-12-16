#include "Key.h"
/******************************************************************************/
uint8_t KeyStatus=0;
/******************************************************************************/
void KEY_Init(void)
{
	BSP_KEY_GPIOInit();
}

void KeyScan(void)
{
	KeyStatus=GPIO_ReadInputDataBit (KEY_GPIO_PORT,KEY_PIN);
}

