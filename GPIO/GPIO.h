/**
  ******************************************************************************
  * @file	GPIO.h
  * @owner	ION Racing
  *******************************************************************************
  * @attention
  *
  * MAY BE USED FREE OF CHARGE.
  * SELLING WITHOUT PRIOR WRITTEN CONSENT PROHIBITED.
  *
  * <h2><center>&copy; COPYRIGHT 2016 ION Racing</center></h2>
  ******************************************************************************
  */

/*-----------------------------------------------------------------------------*/

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
	I2C_TypeDef* I2Cx
);
