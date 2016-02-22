void Initialize_UART
(
	USART_TypeDef * USARTx,
	uint32_t BaudRate,
	uint16_t WordLength,
	uint16_t StopBits,
	uint16_t Parity,
	uint16_t Mode,
	uint16_t HardwareFlowControl
);

void GPIO_USART_Initialise
(
	USART_TypeDef * USARTx
);

void RCC_USART_Initialise
(
	USART_TypeDef * USARTx
);

void NVIC_USART_Initialise
(
	USART_TypeDef * USARTx
);
