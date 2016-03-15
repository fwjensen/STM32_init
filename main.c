#include "GPIO.h"
#include "I2C.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "GPS.h"
#include "USART.h"
#include "IRQHandler.h"
#include "CAN.h"
#include "stm32f4xx_can.h"
#include "LED.h"

volatile int k = 0;
int main(void)
{
	uint8_t data[8];
    data[0] = 0;
    data[1] = 10;
    data[2] = 20;
    data[3] = 30;
    data[4] = 40;
    data[5] = 50;
    data[6] = 60;
    data[7] = 70;
    
    CAN_Initialise(CAN2);
    LED_init();
	while(1)
    {
        for(k = 0;k < 0xFFFFFF;k++){};
        LED_toggle(LED1);
        
        CAN_Write(0x123,8,data);
    }
}
