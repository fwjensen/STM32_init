#include "stm32f4xx_i2c.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "GPIO.h"
#include "I2C.h"

/************-DEFINES-*******************/
#define I2Cx I2C1
//Only works for I2C1 and I2C2
#define I2Cx_GPIO (I2Cx == I2C1 ? GPIOB : GPIOB)
#define I2Cx_SCL_GPIO (I2Cx == I2C1 ? GPIO_Pin_6 : GPIO_Pin_10)
#define I2Cx_SDA_GPIO (I2Cx == I2C1 ? GPIO_Pin_9 : GPIO_Pin_11)
#define I2Cx_SCL_GPIO_SRC (I2Cx == I2C1 ? GPIO_PinSource6 : GPIO_PinSource10)
#define I2Cx_SDA_GPIO_SRC (I2Cx == I2C1 ? GPIO_PinSource9 : GPIO_PinSource11)
#define I2C_GPIO_AF (I2Cx == I2C1 ? GPIO_AF_I2C1 : GPIO_AF_I2C2)
#define I2C_RCC_Perip (I2Cx == I2C1 ? RCC_APB1Periph_I2C1 : RCC_APB1Periph_I2C2)

void I2C_Initialise()
{
	I2C_InitTypeDef I2C_InitStruct;

	I2C_GPIO_Initialise();
	I2C_RCC_DeInitialise();
	I2C_RCC_Initialise();

	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2Cx, &I2C_InitStruct);

	I2C_Cmd(I2Cx, ENABLE);
}

void I2C_GPIO_Initialise()
{
    GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_GPIO_DeInitialise(I2Cx_GPIO);
	RCC_GPIO_Initialise(I2Cx_GPIO);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = I2Cx_SCL_GPIO | I2Cx_SDA_GPIO;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2Cx_GPIO, &GPIO_InitStruct);
    
    //IS THIS POSSIBLE
    GPIO_PinAFConfig(I2Cx_GPIO, I2Cx_SCL_GPIO_SRC | I2Cx_SDA_GPIO_SRC, I2C_GPIO_AF);
	GPIO_PinAFConfig(I2Cx_GPIO, I2Cx_SDA_GPIO_SRC, I2C_GPIO_AF);
}

void I2C_RCC_Initialise()
{
	RCC_APB1PeriphClockCmd(I2C_RCC_Perip, ENABLE);
}

void I2C_RCC_DeInitialise()
{
	RCC_APB1PeriphResetCmd(I2C_RCC_Perip, ENABLE);
	RCC_APB1PeriphResetCmd(I2C_RCC_Perip, DISABLE);
}

/**
 * @brief Read 8bits from the I2Cx.
 *
 * @param I2Cx		x = 1, 2, 3.
 * @param addr		L3GD20H_ADDRESS, LSM303_ADDRESS, BMP180_ADDRESS or uint8_t value.
 * @param reg		L3GD20H__REGISTER_, LSM303_REGISTER_, BMP180_REGISTER_ or uint8_t value.
 * @param data		uint8_t value.
 *
 */
void I2C_Write8(uint8_t addr, uint8_t reg, uint8_t data)
{
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));

	I2C_Send7bitAddress(I2Cx, addr<<1,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2Cx, reg);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2Cx, data);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));
}

/**
 * @brief Read 8bits from the I2Cx.
 *
 * @param I2Cx		x = 1, 2, 3.
 * @param addr		L3GD20H_ADDRESS, LSM303_ADDRESS, BMP180_ADDRESS or uint8_t value.
 * @param reg		L3GD20H__REGISTER_, LSM303_REGISTER_, BMP180_REGISTER_ or uint8_t value.
 *
 */
uint8_t I2C_Read8(uint8_t addr, uint8_t reg)
{
	uint8_t data = 0;

	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2Cx, addr<<1,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2Cx, reg);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));

	I2C_Send7bitAddress(I2Cx, addr<<1, I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	I2C_NACKPositionConfig(I2Cx, I2C_NACKPosition_Current);
	I2C_AcknowledgeConfig(I2Cx, DISABLE);

	//need to add a wait here for new data, right now it goes to fast to get the new data.
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_RXNE));
	data = I2C_ReceiveData(I2Cx);
	//while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED));

	I2C_GenerateSTOP(I2Cx, ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));

	return data;
}

/**
 * @brief Read 16bits from the I2Cx.
 *
 * @param I2Cx		x = 1, 2, 3.
 * @param addr		L3GD20H_ADDRESS, LSM303_ADDRESS, BMP180_ADDRESS or uint8_t value.
 * @param reg1		L3GD20H__REGISTER_, LSM303_REGISTER_, BMP180_REGISTER_ or uint8_t value.
 * @param reg2		L3GD20H__REGISTER_, LSM303_REGISTER_, BMP180_REGISTER_ or uint8_t value.
 *
 */
uint16_t I2C_Read16(uint8_t addr, uint8_t reg_MSB, uint8_t reg_LSB)
{
	uint8_t lsb = 0, msb = 0;
	uint16_t data = 0;

	msb = I2C_Read8(addr, reg_MSB);
	lsb = I2C_Read8(addr, reg_LSB);

	data = lsb | msb << 8;

	return data;
}
