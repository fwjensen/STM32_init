#include "stm32f4xx_usart.h"

extern uint16_t USARTData[1024];

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

void USART_Write
(
    USART_TypeDef * USARTx,
    uint16_t Data
);

void USART_Read
(
		USART_TypeDef * USARTx
);
