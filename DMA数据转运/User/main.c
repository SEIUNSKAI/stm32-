#include "stm32f10x.h"  
#include "Delay.h"
#include "OLED.h"
#include "Dmaaaa.h"

uint8_t Data_A[] = {0x01, 0x02, 0x03, 0x04};
uint8_t Data_B[] = {0, 0, 0, 0};

int main(void)
{
	
	OLED_Init();
	
	DMAA_Init((uint32_t)Data_A, (uint32_t)Data_B, 4);
	
	OLED_ShowString(1, 1, "DataA");
	OLED_ShowString(3, 1, "DataB");
	OLED_ShowHexNum(1, 8, (uint32_t)Data_A, 8);
	OLED_ShowHexNum(3, 8, (uint32_t)Data_B, 8);
		
	while (1)
		{	
			Data_A[0] ++;
			Data_A[1] ++;
			Data_A[2] ++;
			Data_A[3] ++;
			
			OLED_ShowHexNum(2, 1, Data_A[0], 2);
			OLED_ShowHexNum(2, 4, Data_A[1], 2);
			OLED_ShowHexNum(2, 7, Data_A[2], 2);
			OLED_ShowHexNum(2, 10, Data_A[3], 2);
			OLED_ShowHexNum(4, 1, Data_B[0], 2);
			OLED_ShowHexNum(4, 4, Data_B[1], 2);
			OLED_ShowHexNum(4, 7, Data_B[2], 2);
			OLED_ShowHexNum(4, 10, Data_B[3], 2);
			Delay_ms(1000);
			
			DMAA_Transfer();
			
			OLED_ShowHexNum(2, 1, Data_A[0], 2);
			OLED_ShowHexNum(2, 4, Data_A[1], 2);
			OLED_ShowHexNum(2, 7, Data_A[2], 2);
			OLED_ShowHexNum(2, 10, Data_A[3], 2);
			OLED_ShowHexNum(4, 1, Data_B[0], 2);
			OLED_ShowHexNum(4, 4, Data_B[1], 2);
			OLED_ShowHexNum(4, 7, Data_B[2], 2);
			OLED_ShowHexNum(4, 10, Data_B[3], 2);
			Delay_ms(1000);
		}
			
}
