/**
  ************************************* Copyright ******************************   
  * (C) Copyright 2018,Daqo Lee,China, GCU.
  *		All Rights Reserved
  *
  * By(ZHE WOLF TEAM OF GCU ROBOT)
  * https://github.com/GCUWildwolfteam
  *
  * FileName   : servo.h   
  * Version    : v1.0		
  * Author     : Daqo Lee			
  * Date       : 2018-12-21         
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



#ifndef __SERVO_H_
#define __SERVO_H_
#include "stm32f4xx.h"

#define PING          0x01
#define READ          0x02
#define WRITE         0x03
#define REG_WRITE     0x04
#define ACTION        0x05
#define FACTORY_REST  0x06
#define REBOOT        0x08
#define STATUS        0x55
#define SYNC_READ     0x82
#define SYNC_WRITE    0x83
#define BULK_READ     0x92
#define BULK_WRITE    0x93 


void Dynamixel_setMassage(uint8_t ID, uint16_t Length, uint8_t Cmd, uint8_t *Data);
#endif


 

