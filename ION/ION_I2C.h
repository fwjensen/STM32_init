#include "stm32f4xx_i2c.h"

void I2C_Initialise();

void I2C_Write8
(
	I2C_TypeDef* I2Cx,
	uint8_t addr,
	uint8_t reg,
	uint8_t data
);

uint8_t I2C_Read8
(
	I2C_TypeDef* I2Cx,
	uint8_t addr,
	uint8_t reg
);

uint16_t I2C_Read16
(
	I2C_TypeDef* I2Cx,
	uint8_t addr,
	uint8_t reg_MSB,
	uint8_t reg_LSB
);

void RCC_I2C_Initialise
(
	I2C_TypeDef* I2Cx
);
void RCC_I2C_DeInitialise
(
	I2C_TypeDef* I2Cx
);
void I2C_GPIO_Initialise
(
	I2C_TypeDef* I2Cx
);
void I2C_RCC_DeInitialise
(
	I2C_TypeDef* I2Cx
);
void I2C_RCC_Initialise
(
	I2C_TypeDef* I2Cx
);
