#ifndef __MYSPI_H
#define __MYSPI_H
#include <stdint.h>

void MySPI_Init(void);
void SPI_Start(void);
void SPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);

#endif
