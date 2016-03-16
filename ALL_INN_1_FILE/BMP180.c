#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "BMP180.h"

//short
int16_t AC1 = 0, AC2 = 0, AC3 = 0, B1 = 0, B2 = 0, MB = 0, MC = 0, MD = 0;
//unsigned short
uint16_t  AC4 = 0, AC5 = 0, AC6 = 0;
//long
int32_t  UT = 0, UP = 0, X1 = 0, X2 = 0, B5 = 0, T = 0, B6 = 0, X3 = 0, B3 = 0, P = 0;
//unsigned long
uint32_t B4 = 0, B7 = 0;

int x = 0;

void BMP180_Initialise()
{
    GPIO_Initialise();
	
    I2C_Initialise();
    
    //Power ON
	I2C_Write8(BMP180_ADDRESS, BMP180_CAL_AC1_LSB, 0x00);
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

	I2C_GenerateSTART(I2C2, ENABLE);
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

void BMP180_CalibrationData()
{
	AC1 = (int16_t)I2C_Read16(BMP180_ADDRESS, BMP180_CAL_AC1_MSB, BMP180_CAL_AC1_LSB);
	AC2 = (int16_t)I2C_Read16(BMP180_ADDRESS, BMP180_CAL_AC2_MSB, BMP180_CAL_AC2_LSB);
	AC3 = (int16_t)I2C_Read16(BMP180_ADDRESS, BMP180_CAL_AC3_MSB, BMP180_CAL_AC3_LSB);
	AC4 = I2C_Read16(BMP180_ADDRESS, BMP180_CAL_AC4_MSB, BMP180_CAL_AC4_LSB);
	AC5 = I2C_Read16(BMP180_ADDRESS, BMP180_CAL_AC5_MSB, BMP180_CAL_AC5_LSB);
	AC6 = I2C_Read16(BMP180_ADDRESS, BMP180_CAL_AC6_MSB, BMP180_CAL_AC6_LSB);
	B1 = (int16_t)I2C_Read16(BMP180_ADDRESS, BMP180_CAL_B1_MSB, BMP180_CAL_B1_LSB);
	B2 = (int16_t)I2C_Read16(BMP180_ADDRESS, BMP180_CAL_B2_MSB, BMP180_CAL_B2_LSB);
	MB = (int16_t)I2C_Read16(BMP180_ADDRESS, BMP180_CAL_MB_MSB, BMP180_CAL_MB_LSB);
	MC = (int16_t)I2C_Read16(BMP180_ADDRESS, BMP180_CAL_MC_MSB, BMP180_CAL_MC_LSB);
	MD = (int16_t)I2C_Read16(BMP180_ADDRESS, BMP180_CAL_MD_MSB, BMP180_CAL_MD_LSB);
}

int32_t BMP180_Temperature(bmp180Oss_t oss)
{
	I2C_Write8(BMP180_ADDRESS, BMP180_CONTROL, BMP180_READTEMPCMD);
	for(x = 0;x < 0xfff;x++); // wait 4.5ms
	UT = I2C_Read16(BMP180_ADDRESS, BMP180_TEMPDATA_MSB, BMP180_TEMPDATA_LSB);

	X1 = (UT - AC6) * AC5 / 32768;
	X2 = MC * 2048 / (X1 + MD);
	B5 = X1 + X2;
	T = (B5 + 8) / 16; //Temperature
	return T;
}

int32_t BMP180_Pressure(bmp180Oss_t oss)
{
	I2C_Write8(BMP180_ADDRESS,BMP180_CONTROL,BMP180_READPRESSURECMD+(oss<<6));
	for(x = 0;x < 0xfff;x++); //wait?
	UP = (I2C_Read16(BMP180_ADDRESS, BMP180_PRESSUREDATA_MSB, BMP180_PRESSUREDATA_LSB)<<8)+(I2C_Read8(BMP180_ADDRESS, BMP180_PRESSUREDATA_XLSB)>>(8-oss));

	B6 = B5 - 4000;
	X1 = (B2 * (B6 * B6 / 4096)) / 2048;
	X2 = AC2 * B6 / 2048;
	X3 = X1 + X2;
	B3 = (((AC1 * 4  + X3)<<oss) + 2) / 4;
	X1 = AC3 * B6 / 8192;
	X2 = (B1 * (B6 * B6 / 4096))/65536;
	X3 = ((X1 + X2) + 2) / 4;
	B4 = AC4 * (uint32_t)(X3 + 32768) / 32768;
	B7 = ((uint32_t)(UP - B3)) * (50000>>oss);
	if(B7 <  0x80000000){P = (B7 * 2) / B4;}
	else{P = (B7 / B4) * 2;}
	X1 = (P / 256) * (P / 258);
	X1 = (X1 * 3038) / 65536;
	X2 = ((-7357) * P) / 65536;
	P = P + (X1 + X2 + 3791) / 16; //Pressure
	return P;
}
