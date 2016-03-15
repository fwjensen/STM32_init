#include "stm32f4xx_i2c.h"

void I2C_Initialise();

void I2C_Write8
(
	uint8_t addr,
	uint8_t reg,
	uint8_t data
);

uint8_t I2C_Read8
(
	uint8_t addr,
	uint8_t reg
);

uint16_t I2C_Read16
(
	uint8_t addr,
	uint8_t reg_MSB,
	uint8_t reg_LSB
);

void RCC_I2C_Initialise();
void RCC_I2C_DeInitialise();
void I2C_GPIO_Initialise();
void I2C_RCC_DeInitialise();
void I2C_RCC_Initialise();
