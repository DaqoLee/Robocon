#include "BSP_DMA.h"

/**
  * @brief  USART1 RX DMA ���ã����赽�ڴ�(USART1->DR)
  * @param  USART1_DMABuff_addr		DMAĿ��洢��ַ
  * @retval ��
  */
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	/*����DMA2ʱ��*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	  
	/* ��λ��ʼ��DMA������ */
	DMA_DeInit(USART1_RX_DMA_STREAM);

	/* ȷ��DMA��������λ��� */
	while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != DISABLE){
	}

	/*usart1 rx��Ӧdma2��ͨ��4��������2*/	
	DMA_InitStructure.DMA_Channel = USART1_RX_DMA_CHANNEL;  
	/*����DMAԴ���������ݼĴ�����ַ*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_RX_ADDR;	 
	/*�ڴ��ַ(Ҫ����ı�����ָ��)*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;
	/*���򣺴����赽�ڴ�*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	/*�����СDMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = buffsize;
	/*�����ַ����*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	/*�ڴ��ַ����*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	/*�������ݵ�λ*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*�ڴ����ݵ�λ 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	/*DMAģʽ������ѭ��*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	/*���ȼ�����*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
	/*����FIFO*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	/*�洢��ͻ������ 16 ������*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
	/*����ͻ������ 1 ������*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
	/*����DMA2��������*/		   
	DMA_Init(USART1_RX_DMA_STREAM, &DMA_InitStructure);
	  
	/*ʹ��DMA*/
	DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);
  
	/* �ȴ�DMA��������Ч*/
	while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != ENABLE){
	}
  
	//ʹ��DMA����  
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE); 
  
}

