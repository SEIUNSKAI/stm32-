#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "key.h"

uint8_t KeyNum;

int main(void)
{
	LED_Init();
	Key_Init();
	
	while (1)
		{
			KeyNum = Key_GetNum();
			if (KeyNum == 1) 
			{
				LED1_TURN();
			}
			if (KeyNum == 2) 
			{
				LED2_TURN();
			}
		}
		
}

