#include "stm32f4xx_gpio.h"
void GPIO_Initialise
(
	GPIO_TypeDef* GPIOx,
	GPIOMode_TypeDef Mode,
	GPIOOType_TypeDef OType,
	uint16_t Pin,
	GPIOPuPd_TypeDef PuPd,
	GPIOSpeed_TypeDef Speed
);
void RCC_GPIO_Initialise
(
	GPIO_TypeDef* GPIOx
);
void RCC_GPIO_DeInitialise
(
	GPIO_TypeDef* I2Cx
);
