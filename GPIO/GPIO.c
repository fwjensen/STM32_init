/**
  ******************************************************************************
  * @file    GPIO.c
  * @author  Fredrik Wigsnes
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

#include "stm32f4xx_gpio.h"
#include "GPIO.h"
#include "RCC.h"

/**
  * @brief Initializing the GPIOx.
  *
  * @param GPIOx	x = A, B, C, D, E.
  * @param Mode		GPIO_Mode_x => x = AF, AN, IN, OUT.
  * @param OType	GPIO_OType_x => x = OD, PP.
  * @param Pin		GPIO_Pin_x => x = 0..15.
  * @param PuPd		GPIO_PuPd_x => x = DOWN, UP, NOPULL.
  * @param Speed	GPIO_Speed_x => x = 2MHz, 25MHz, 50MHz, 100MHz.
  *
  */
void GPIO_Initialize(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef Mode, GPIOOType_TypeDef OType, uint16_t Pin, GPIOPuPd_TypeDef PuPd, GPIOSpeed_TypeDef Speed)
{
	GPIO_Pin_10;
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_GPIO_DeInit(GPIOx);

	RCC_GPIO_Init(GPIOx);

	GPIO_InitStruct.GPIO_Mode = Mode;
	GPIO_InitStruct.GPIO_OType = OType;
	GPIO_InitStruct.GPIO_Pin = Pin;
	GPIO_InitStruct.GPIO_PuPd = PuPd;
	GPIO_InitStruct.GPIO_Speed = Speed;

	GPIO_Init(GPIOx,&GPIO_InitStruct);
}
