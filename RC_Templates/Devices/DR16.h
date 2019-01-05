#ifndef __DR16_H_
#define __DR16_H_
#include "stm32f4xx.h"

/*遥控解码数据存储结构体*/
typedef struct 
{
	int16_t ch1;	/*each ch value from -660 -- +660*/
	int16_t ch2;
	int16_t ch3;
	int16_t ch4;
	
	uint8_t switch_left;	
	uint8_t switch_right;
	
	struct
	{
		int16_t x;
		int16_t y;
		int16_t z;
	
		uint8_t press_left;
		uint8_t press_right;
        
    uint8_t jumppress_left;
    uint8_t jumppress_right;
	}mouse;
	
	struct 
	{
/**********************************************************************************
   * 键盘通道:15   14   13   12   11   10   9   8   7   6     5     4   3   2   1
   *          V    C    X	   Z    G    F    R   E   Q  CTRL  SHIFT  D   A   S   W
************************************************************************************/
		uint16_t key_code;              
    uint16_t jumpkey_code;         
	}keyBoard;
	
	void (*p_DR16getMsg)(uint8_t *DR16Buffer);
	
}DR16_t;

/******************************************************************************/
extern DR16_t DR16;
void DR16_Init(void);
/******************************************************************************/
#endif


 

