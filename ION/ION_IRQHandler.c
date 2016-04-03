#include "stm32f4xx_usart.h"
#include "ION_USART.h"

void USART1_IRQHandler(void){
	// check if the USART1 receive interrupt flag was set
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
		USART_Read(USART1);
	}
}
void USART2_IRQHandler(void){
	// check if the USART2 receive interrupt flag was set
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		USART_Read(USART2);
	}
}
void USART3_IRQHandler(void){
	// check if the USART1 receive interrupt flag was set
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET){

	}
}
void UART4_IRQHandler(void){
	// check if the USART1 receive interrupt flag was set
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET){

	}
}
void UART5_IRQHandler(void){
	// check if the USART1 receive interrupt flag was set
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET){

	}
}
void USART6_IRQHandler(void){
	// check if the USART1 receive interrupt flag was set
	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET){

	}
}
