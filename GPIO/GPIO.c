#include "stm32f4xx_gpio.h"
#include "GPIO.h"

/**
  * @brief Initialising the GPIOx.
  *
  * @param GPIOx	x = A, B, C, D, E.
  * @param Mode		GPIO_Mode_x => x = AF, AN, IN, OUT.
  * @param OType	GPIO_OType_x => x = OD, PP.
  * @param Pin		GPIO_Pin_x => x = 0..15.
  * @param PuPd		GPIO_PuPd_x => x = DOWN, UP, NOPULL.
  * @param Speed	GPIO_Speed_x => x = 2MHz, 25MHz, 50MHz, 100MHz.
  *
  */
void GPIO_Initialise(GPIO_TypeDef* GPIOx, GPIOMode_TypeDef Mode, GPIOOType_TypeDef OType, uint16_t Pin, GPIOPuPd_TypeDef PuPd, GPIOSpeed_TypeDef Speed)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_GPIO_DeInitialise(GPIOx);

	RCC_GPIO_Initialise(GPIOx);

	GPIO_InitStruct.GPIO_Mode = Mode;
	GPIO_InitStruct.GPIO_OType = OType;
	GPIO_InitStruct.GPIO_Pin = Pin;
	GPIO_InitStruct.GPIO_PuPd = PuPd;
	GPIO_InitStruct.GPIO_Speed = Speed;

	GPIO_Init(GPIOx,&GPIO_InitStruct);
}
/**
 * @brief Initialise GPIOx clock.
 *
 * @param GPIOx		x = A, B, C, D, E.
 *
 */
void RCC_GPIO_Initialise(GPIO_TypeDef* GPIOx)
{
  if (GPIOx == GPIOA)
  {
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  }
  else if (GPIOx == GPIOB)
  {
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
  }
  else if (GPIOx == GPIOC)
  {
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
  }
  else if (GPIOx == GPIOD)
  {
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
  }
  else if (GPIOx == GPIOE)
  {
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
  }
  else
  {
	  while(1);
  }
}

/**
 * @brief DeInitialise GPIOx clock.
 *
 * @param GPIOx		x = A, B, C, D, E.
 *
 */
void RCC_GPIO_DeInitialise(GPIO_TypeDef* GPIOx)
{
	if (GPIOx == GPIOA)
	{
		RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA,ENABLE);
		RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA,DISABLE);
	}
	else if (GPIOx == GPIOB)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,DISABLE);
	}
	else if (GPIOx == GPIOC)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,DISABLE);
	}
	else if (GPIOx == GPIOD)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,DISABLE);
	}
	else if (GPIOx == GPIOE)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,DISABLE);
	}
	else
	{
		while(1);
	}
}
