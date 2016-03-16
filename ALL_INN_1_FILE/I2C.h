#include "stm32f4xx.h"

void I2C_Initialise(void);
void GPIO_Initialise(void);

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
