#include "stm32f10x.h"  
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"

int main(void)
{
	
	OLED_Init();
	MyRTC_Init();
	
	while (1)
		{
			OLED_ShowNum(1, 1, RTC_GetCounter(), 10);
		}
			
}
