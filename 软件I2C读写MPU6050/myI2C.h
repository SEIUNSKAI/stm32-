#ifndef __MY_I2C_H
#define __MY_I2C_H
#include <stdint.h>

void myI2C_W_SCL(uint8_t BitValue);
void myI2C_W_SDA(uint8_t BitValue);
uint8_t myI2C_R_SDA(void);
void myI2C_Init(void);
void myI2C_Start(void);
void myI2C_Stop(void);
void myI2C_SendByte(uint8_t Byte);
uint8_t myI2C_RecieveByte(void);
void myI2C_SendAck(uint8_t Ackbit);
uint8_t myI2C_RecieveAck(void);

#endif