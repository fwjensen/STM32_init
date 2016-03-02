#include "USART.h"
#include "stm32f4xx_usart.h"


/**
 * We are using Adafruit Ultimate GPS Breakout that you can find here.
 * https://www.adafruit.com/products/746
 *
 * We are using USART2 and are connected like this.
 * Gps	-	stm32
 * 3.3V	- 	Gdd
 * Gnd 	- 	Gnd
 * RX	-	PA2
 * TX 	- 	PA3
 *
 * We use 3.3V instead of 5V.
 *
 */
void GPS_Initialise()
{
	USART_Initialize(USART2,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx | USART_Mode_Rx,USART_HardwareFlowControl_None);
}
