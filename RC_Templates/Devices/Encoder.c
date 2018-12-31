#include "Encoder.h"
#include "string.h"
Posture_t Posture;


void Posture_getMessage(uint8_t *EncoderBuf)
{
			if(EncoderBuf[0]==0x0D&&EncoderBuf[1]==0x0A&&\
		   EncoderBuf[26]==0x0A&&EncoderBuf[27]==0x0D)
			{
				memcpy(Posture.DataBuff,&EncoderBuf[2],sizeof(uint8_t[24]));
			}
}

