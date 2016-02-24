#include "USART.h"
#include "stm32f4xx_usart.h"

void GPS_Initialise()
{
	USART_Initialize(USART2,9600,USART_WordLength_8b,USART_StopBits_1,USART_Parity_No,USART_Mode_Rx,USART_HardwareFlowControl_None);

}
