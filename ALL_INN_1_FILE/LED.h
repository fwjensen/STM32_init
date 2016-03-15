#include "stm32f4xx_gpio.h"

void LED_init(void);
void LED_on(uint16_t ledN);
void LED_off(uint16_t ledN);
void LED_toggle(uint16_t ledN);

//GPIO used for LEDs.
#define LED_GPIO GPIOD
//LED pins.
#define LED1 GPIO_Pin_12 // PD0
#define LED2 GPIO_Pin_13 // PD1
#define LED3 GPIO_Pin_14 // PD2
#define LED4 GPIO_Pin_15 // PD3
