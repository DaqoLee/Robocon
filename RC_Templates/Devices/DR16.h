/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : DR16.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-13         
  * Description:    
  * Function List:  
  	1. ....
  	   <version>: 		
  <modify staff>:
  		  <data>:
   <description>:  
  	2. ...
  ******************************************************************************
 */



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
}DR16_Data_t;

/******************************************************************************/
void DR16_DataDecode(uint8_t *DR16Buffer);
/******************************************************************************/
#endif


 

