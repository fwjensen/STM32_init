#include "stm32f4xx_usart.h"
void USART_Initialize
(
	USART_TypeDef * USARTx,
	uint32_t BaudRate,
	uint16_t WordLength,
	uint16_t StopBits,
	uint16_t Parity,
	uint16_t Mode,
	uint16_t HardwareFlowControl
);

void USART_GPIO_Initialise
(
	USART_TypeDef * USARTx
);

void USART_RCC_Initialise
(
	USART_TypeDef * USARTx
);

void USART_NVIC_Initialise
(
	USART_TypeDef * USARTx
);
void USART_Read
(
		USART_TypeDef * USARTx
);
