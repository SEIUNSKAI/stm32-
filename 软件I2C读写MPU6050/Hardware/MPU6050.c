#include "stm32f10x.h"
#include "myI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t data)
{
    myI2C_Start();
    myI2C_SendByte(MPU6050_ADDRESS);   //寻址
    myI2C_RecieveAck();
    myI2C_SendByte(RegAddress);     //指定写入的寄存器
    myI2C_RecieveAck();
    myI2C_SendByte(data);    //写入数据
    myI2C_RecieveAck();
    myI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
    uint8_t Data;

    myI2C_Start();
    myI2C_SendByte(MPU6050_ADDRESS);   //寻址
    myI2C_RecieveAck();
    myI2C_SendByte(RegAddress);     //指定要读的寄存器
    myI2C_RecieveAck();

    myI2C_Start();
    myI2C_SendByte(MPU6050_ADDRESS | 0x01);  //指定读模式
    myI2C_RecieveAck();
    Data = myI2C_RecieveByte();
    myI2C_SendAck(1);
    myI2C_Stop();

    return Data;
}

void MPU6050_Init(void)
{
    myI2C_Init();
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
    MPU6050_WriteReg(MPU6050_CONFIG, 0x09);
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH, DataL;								//定义数据高8位和低8位的变量
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);		//读取加速度计X轴的高8位数据
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);		//读取加速度计X轴的低8位数据
	*AccX = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);		
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);		
	*AccY = (DataH << 8) | DataL;						
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);		
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);		
	*AccZ = (DataH << 8) | DataL;						
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);		
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);		
	*GyroX = (DataH << 8) | DataL;						
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);		
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);		
	*GyroY = (DataH << 8) | DataL;						
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);		
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);		
	*GyroZ = (DataH << 8) | DataL;						
}

