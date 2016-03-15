#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "GPIO.h"

/***********-DEFINES-**********************/
#define GPIOx GPIOA
#define GPIO_RCC (GPIOx == GPIOA ? RCC_AHB1Periph_GPIOA : GPIOx == GPIOB ? RCC_AHB1Periph_GPIOB : GPIOx == GPIOC ? RCC_AHB1Periph_GPIOC : GPIOx == GPIOD ? RCC_AHB1Periph_GPIOD : RCC_AHB1Periph_GPIOE)

void GPIO_Initialise()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_GPIO_DeInitialise(GPIOx);

	RCC_GPIO_Initialise(GPIOx);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOx,&GPIO_InitStruct);
}

void RCC_GPIO_Initialise()
{
  RCC_AHB1PeriphClockCmd(GPIO_RCC,ENABLE);
}

void RCC_GPIO_DeInitialise()
{
	RCC_AHB1PeriphResetCmd(GPIO_RCC,ENABLE);
	RCC_AHB1PeriphResetCmd(GPIO_RCC,DISABLE);
}
