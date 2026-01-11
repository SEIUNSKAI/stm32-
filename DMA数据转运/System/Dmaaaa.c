#include "stm32f10x.h"                  // Device header

uint16_t DMASize = 4;

void DMAA_Init(uint32_t AddrA ,uint32_t AddrB, uint16_t Size)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;       //存储器参数
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;		//外设参数
	DMA_InitStructure.DMA_BufferSize = Size;    //传输计数器
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;   //direction
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;	//触发方式
	DMA_InitStructure.DMA_Mode =  DMA_Mode_Normal;  //是否使用自动重装
  	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	DMA_Cmd(DMA1_Channel1, DISABLE);
}


void DMAA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, DMASize);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);    //清除标志位
}
