#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "LSM303.h"

void LSM303_Initialise()
{
    GPIO_Initialise();
	
    I2C_Initialise();
    
    //Power ON Accelerometer
	I2C_Write8(LSM303_ADDRESS_ACCEL, LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x57);
    
    //Power ON Magnetometer
    I2C_Write8(LSM303_ADDRESS_MAG,LSM303_REGISTER_MAG_CRA_REG_M,0x00);
	//Gain 1.3 NOT SURE WHAT THIS DO.
	I2C_Write8(LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_CRB_REG_M, LSM303_MAGGAIN_1_3);
}

void GPIO_Initialise()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, DISABLE);
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);    
}

void I2C_Initialise()
{
    I2C_InitTypeDef I2C_InitStruct;
	
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2C1, &I2C_InitStruct);

	I2C_Cmd(I2C1, ENABLE);
}

void I2C_Write8(uint8_t addr, uint8_t reg, uint8_t data)
{
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));

	I2C_Send7bitAddress(I2C1, addr<<1,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, reg);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2C1, data);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));
}

uint8_t I2C_Read8(uint8_t addr, uint8_t reg)
{
	uint8_t data = 0;

	I2C_AcknowledgeConfig(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2C1, addr<<1,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, reg);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_SB));

	I2C_Send7bitAddress(I2C1, addr<<1, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	I2C_NACKPositionConfig(I2C1, I2C_NACKPosition_Current);
	I2C_AcknowledgeConfig(I2C1, DISABLE);

	//need to add a wait here for new data, right now it goes to fast to get the new data.
	while(!I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE));
	data = I2C_ReceiveData(I2C1);
	//while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));

	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));

	return data;
}

uint16_t I2C_Read16(uint8_t addr, uint8_t reg_MSB, uint8_t reg_LSB)
{
	uint8_t lsb = 0, msb = 0;
	uint16_t data = 0;

	msb = I2C_Read8(addr, reg_MSB);
	lsb = I2C_Read8(addr, reg_LSB);

	data = lsb | msb << 8;

	return data;
}

uint16_t LSM303_ACCEL_X()
{
	return I2C_Read16(LSM303_ADDRESS_ACCEL, LSM303_REGISTER_ACCEL_OUT_X_H_A, LSM303_REGISTER_ACCEL_OUT_X_L_A);
}

uint16_t LSM303_ACCEL_Y()
{
	return I2C_Read16(LSM303_ADDRESS_ACCEL, LSM303_REGISTER_ACCEL_OUT_Y_H_A, LSM303_REGISTER_ACCEL_OUT_Y_L_A);
}

uint16_t LSM303_ACCEL_Z()
{
	return I2C_Read16(LSM303_ADDRESS_ACCEL, LSM303_REGISTER_ACCEL_OUT_Z_H_A, LSM303_REGISTER_ACCEL_OUT_Z_L_A);
}

uint16_t LSM303_ACCEL_XYZ()
{
	uint16_t axis[3];
	axis[0] = LSM303_ACCEL_X();
	axis[1] = LSM303_ACCEL_Y();
	axis[2] = LSM303_ACCEL_Z();
	//FIX THIS LATER!
	return axis[1];
}

uint16_t LSM303_MAG_X()
{
	return I2C_Read16(LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_OUT_X_H_M, LSM303_REGISTER_MAG_OUT_X_L_M);
}

uint16_t LSM303_MAG_Y()
{
	return I2C_Read16(LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_OUT_Y_H_M, LSM303_REGISTER_MAG_OUT_Y_L_M);
}

uint16_t LSM303_MAG_Z()
{
	return I2C_Read16(LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_OUT_Z_H_M, LSM303_REGISTER_MAG_OUT_Z_L_M);
}

uint16_t LSM303_MAG_XYZ()
{
	uint16_t axis[3];
	axis[0] = LSM303_MAG_X();
	axis[1] = LSM303_MAG_Y();
	axis[2] = LSM303_MAG_Z();
	//FIX THIS LATER!
	return axis[1];
}
