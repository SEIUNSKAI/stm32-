#include "stm32f10x.h"  
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"

uint16_t Num;

int main(void)
{
	Encoder_Init();
	OLED_Init();
	
	OLED_ShowString(1, 1, "Num:");
	while (1)
		{
			OLED_ShowSignedNum(1, 5, Encoder_Get(), 5);
			Delay_ms(1000);
		}
			
}


