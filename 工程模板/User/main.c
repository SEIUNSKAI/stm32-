#include "stm32f10x.h"  
#include "Delay.h"
#include "OLED.h"


int main(void)
{
	
	OLED_Init();
	Countsensor_Init();
	OLED_ShowString(1, 1, "Count:");
	
	
	while (1)
		{
			OLED_ShowNum(1, 7, getcount(), 5);
		}
			
}
// gittest