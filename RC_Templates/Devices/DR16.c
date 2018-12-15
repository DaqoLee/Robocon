#include "DR16.h"

DR16_Data_t DR16_Data;

/**
  * @brief  DBUSÊý¾Ý½âÂë
  * @param  void
  * @retval void
  */
void DR16_DataDecode(uint8_t *DR16Buffer)
{
	DR16_Data.ch1 = (DR16Buffer[0] | DR16Buffer[1]<<8) & 0x07FF;
	DR16_Data.ch1 -= 1024;
	DR16_Data.ch2 = (DR16Buffer[1]>>3 | DR16Buffer[2]<<5 ) & 0x07FF;
	DR16_Data.ch2 -= 1024;
	DR16_Data.ch3 = (DR16Buffer[2]>>6 | DR16Buffer[3]<<2 | DR16Buffer[4]<<10) & 0x07FF;
	DR16_Data.ch3 -= 1024;
	DR16_Data.ch4 = (DR16Buffer[4]>>1 | DR16Buffer[5]<<7) & 0x07FF;		
	DR16_Data.ch4 -= 1024;
	
	DR16_Data.switch_left = ( (DR16Buffer[5] >> 4)& 0x000C ) >> 2;
	DR16_Data.switch_right =  (DR16Buffer[5] >> 4)& 0x0003 ;
	
	DR16_Data.mouse.x = DR16Buffer[6] | (DR16Buffer[7] << 8);	//x axis
	DR16_Data.mouse.y = DR16Buffer[8] | (DR16Buffer[9] << 8);
	DR16_Data.mouse.z = DR16Buffer[10]| (DR16Buffer[11] << 8);
	
	DR16_Data.mouse.press_left 	= DR16Buffer[12];	// is pressed?
	DR16_Data.mouse.press_right 	= DR16Buffer[13];
	
	DR16_Data.keyBoard.key_code 	= DR16Buffer[14] | DR16Buffer[15] << 8; //key borad code
}


