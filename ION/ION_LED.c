/*
* LEDs for debugging purposes.
* The LEDS are connected to:
*
* LED 1 : PD0
* LED 2 : PD1
* LED 3 : PD2
* LED 4 : PD3
*/

#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "ION_LED.h"


void LED_init()
{
	GPIO_InitTypeDef GPIO_initStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_initStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_initStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_initStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_initStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_initStruct.GPIO_Pin = LED1 | LED2 | LED3 | LED4;
	
	GPIO_Init(GPIOD, &GPIO_initStruct);
}


/*
* Turns on LED number N as indicated by the silkscreen on the PCB.

*/
void LED_on(uint16_t ledN)	
{
	//HAL_GPIO_WritePin(LED_GPIO, ledN, GPIO_PIN_SET);
	GPIO_WriteBit(LED_GPIO,ledN,Bit_SET);
}

/*
* Turns off LED number N as indicated by the silkscreen on the PCB.

*/
void LED_off(uint16_t ledN)
{
	//HAL_GPIO_WritePin(LED_GPIO,ledN,GPIO_PIN_RESET);
    GPIO_WriteBit(LED_GPIO,ledN,Bit_RESET);
}


/*
* Toggles LED number N as indicated by the silkscreen on the PCB.
*/
void LED_toggle(uint16_t ledN)
{
	//HAL_GPIO_TogglePin(LED_GPIO, ledN);
    GPIO_ToggleBits(LED_GPIO,ledN);
}
