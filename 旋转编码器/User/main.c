#include "stm32f10x.h"  
#include "OLED.h"
#include "Encoder.h"

uint16_t num;

int main(void)
{
	
	OLED_Init();
	Encoder_Init();
	OLED_ShowString(1, 1, "Number:");
	
	
	while (1)
		{
			num += getdata();
			OLED_ShowSignedNum(1, 8, num, 5 );
		}
			
}
