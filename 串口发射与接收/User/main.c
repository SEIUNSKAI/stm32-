#include "stm32f10x.h"  
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RXData;

int main(void)
{
	OLED_Init();
	Serial_Init();
	
	OLED_ShowString(1, 1, "RXData:");
	
	while (1)
		{
			if(GetFlagData() == 1)
			{
				RXData = Get_RxData();
				Serial_SendByte(RXData);
				OLED_ShowHexNum(1, 8, RXData, 2);
			}
		}
			
}
