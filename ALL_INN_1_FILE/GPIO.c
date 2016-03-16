#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "GPIO.h"

void GPIO_Initialise()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOD,DISABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOD,&GPIO_InitStruct);
}
