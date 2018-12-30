#include "DR16.h"
/******************************************************************************/
DR16_t DR16;

static void DR16_getMessage(uint8_t *DR16Buffer);
/******************************************************************************/
void DR16_Init(void)
{
	DR16.ch1=0;
	DR16.ch2=0;
	DR16.ch3=0;
	DR16.ch4=0;
	DR16.keyBoard.key_code=0;
	
	DR16.switch_left = 0;
	DR16.switch_right =0 ;
	
	DR16.mouse.x = 0;	
	DR16.mouse.y = 0;
	DR16.mouse.z =0;
	
	DR16.mouse.press_left 	= 0;	
	DR16.mouse.press_right 	=0;
	
	DR16.pDR16getMsg=DR16_getMessage;
}
/******************************************************************************/
/**
  * @brief  DBUSÊý¾Ý½âÂë
  * @param  void
  * @retval void
  */	
static void DR16_getMessage(uint8_t *DR16Buffer)
{
	DR16.ch1 = (DR16Buffer[0] | DR16Buffer[1]<<8) & 0x07FF;
	DR16.ch1 -= 1024;
	DR16.ch2 = (DR16Buffer[1]>>3 | DR16Buffer[2]<<5 ) & 0x07FF;
	DR16.ch2 -= 1024;
	DR16.ch3 = (DR16Buffer[2]>>6 | DR16Buffer[3]<<2 | DR16Buffer[4]<<10) & 0x07FF;
	DR16.ch3 -= 1024;
	DR16.ch4 = (DR16Buffer[4]>>1 | DR16Buffer[5]<<7) & 0x07FF;		
	DR16.ch4 -= 1024;
	
	DR16.switch_left = ( (DR16Buffer[5] >> 4)& 0x000C ) >> 2;
	DR16.switch_right =  (DR16Buffer[5] >> 4)& 0x0003 ;
	
	DR16.mouse.x = DR16Buffer[6] | (DR16Buffer[7] << 8);	
	DR16.mouse.y = DR16Buffer[8] | (DR16Buffer[9] << 8);
	DR16.mouse.z = DR16Buffer[10]| (DR16Buffer[11] << 8);
	
	DR16.mouse.press_left 	= DR16Buffer[12];	
	DR16.mouse.press_right 	= DR16Buffer[13];
	
	DR16.keyBoard.key_code 	= DR16Buffer[14] | DR16Buffer[15] << 8; 
}
/******************************************************************************/

