#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "GPIO.h"

/*
 * USART_InitStructure.USART_BaudRate = 9600;
 * USART_InitStructure.USART_WordLength = USART_WordLength_8b;
 * USART_InitStructure.USART_StopBits = USART_StopBits_1;
 * USART_InitStructure.USART_Parity = USART_Parity_No;
 * USART_InitStructure.USART_Mode = USART_Mode_Rx;
 * USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
 */
void Initialize_UART(USART_TypeDef * USARTx, uint32_t BaudRate, uint16_t WordLength, uint16_t StopBits, uint16_t Parity, uint16_t Mode, uint16_t HardwareFlowControl)
{
	USART_InitTypeDef USART_InitStruct;

	GPIO_USART_Initialise(USARTx);

	RCC_USART_Initialise(USARTx);

	USART_InitStruct.USART_BaudRate = BaudRate;
	USART_InitStruct.USART_WordLength = WordLength;
	USART_InitStruct.USART_StopBits = StopBits;
	USART_InitStruct.USART_Parity = Parity;
	USART_InitStruct.USART_Mode = Mode;
	USART_InitStruct.USART_HardwareFlowControl = HardwareFlowControl;

	USART_Init(USARTx, &USART_InitStruct);

	USART_Cmd(USARTx, ENABLE);

	//Enable RX interrupt
	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
}

void GPIO_USART_Initialise(USART_TypeDef * USARTx){
	if(USARTx == USART1)
	{
		GPIO_Initialise(GPIOA,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_9 | GPIO_Pin_10, GPIO_PuPd_UP,GPIO_Speed_50MHz);
	}
	else if(USARTx == USART2)
	{
		GPIO_Initialise(GPIOA,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_2 | GPIO_Pin_3, GPIO_PuPd_UP,GPIO_Speed_50MHz);
	}
	else if(USARTx == USART3)
	{
		GPIO_Initialise(GPIOB,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_10 | GPIO_Pin_11, GPIO_PuPd_UP,GPIO_Speed_50MHz);
	}
	else if(USARTx == UART4)
	{
		GPIO_Initialise(GPIOA,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_0 | GPIO_Pin_1, GPIO_PuPd_UP,GPIO_Speed_50MHz);
	}
	else if(USARTx == UART5)
	{
		GPIO_Initialise(GPIOC,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_12, GPIO_PuPd_UP,GPIO_Speed_50MHz);
		GPIO_Initialise(GPIOD,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_2, GPIO_PuPd_UP,GPIO_Speed_50MHz);
	}
	else if(USARTx == USART6)
	{
		GPIO_Initialise(GPIOC,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_6 | GPIO_Pin_7, GPIO_PuPd_UP,GPIO_Speed_50MHz);
	}
	else
	{
		while(1);
	}
}

void RCC_USART_Initialise(USART_TypeDef * USARTx)
{
	if(USARTx == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	}
	else if(USARTx == USART2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	}
	else if(USARTx == USART3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	}
	else if(USARTx == UART4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	}
	else if(USARTx == UART5)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	}
	else if(USARTx == USART6)
	{
		RCC_APB1PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	}
	else
	{
		while(1);
	}
}
