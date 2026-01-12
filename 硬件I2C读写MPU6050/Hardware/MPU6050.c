#include "stm32f10x.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t data)
{
	I2C_GenerateSTART(I2C2, ENABLE);
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);	//开始通信
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);  //写入从机地址

	I2C_SendData(I2C2, RegAddress);
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING) != SUCCESS);	   //要写入的寄存器的地址

	I2C_SendData(I2C2, data);
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);  //发送要写入的数据

	I2C_GenerateSTOP(I2C2, ENABLE);  //终止通信
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;

	I2C_GenerateSTART(I2C2, ENABLE);
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);	//开始通信
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);  //写入从机地址

	I2C_SendData(I2C2, RegAddress);
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);	   //要写入的寄存器的地址

	I2C_GenerateSTART(I2C2, ENABLE);
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);

	I2C_AcknowledgeConfig(I2C2, DISABLE);
	I2C_GenerateSTOP(I2C2, ENABLE);

	while(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
	Data = I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);

	return Data;
}

void MPU6050_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);

	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C2, &I2C_InitStructure);

	I2C_Cmd(I2C2, ENABLE);

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

