#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "GPIO.h"
#include "USART.h"
#include "misc.h"

volatile char num[1024];
volatile int p = 0;

/**
 * @brief Initialising U(S)ARTx.
 *
 * @param USARTx/UARTx				x = 1, 2, 3, 4, 5, 6.
 * @param BaudRate					example 9600.
 * @param WordLength				USART_WordLength_x => x = 8b, 9b.
 * @param StopBits					USART_StopBits_x => x = 0_5, 1, 1_5, 2.
 * @param Parity					USART_Parity_x => x = Even, No, Odd.
 * @param Mode						USART_Mode_x => x = Rx, Tx.
 * @param HardwareFlowControl		USART_HardwareFlowControl_x => x = CTS, None, RTS, RTS_CTS.
 *
 */
void USART_Initialize(USART_TypeDef* USARTx, uint32_t BaudRate, uint16_t WordLength, uint16_t StopBits, uint16_t Parity, uint16_t Mode, uint16_t HardwareFlowControl)
{
	USART_InitTypeDef USART_InitStruct;
	
	USART_RCC_Initialise(USARTx);

	USART_GPIO_Initialise(USARTx);

	USART_InitStruct.USART_BaudRate = BaudRate;
	USART_InitStruct.USART_WordLength = WordLength;
	USART_InitStruct.USART_StopBits = StopBits;
	USART_InitStruct.USART_Parity = Parity;
	USART_InitStruct.USART_Mode = Mode;
	USART_InitStruct.USART_HardwareFlowControl = HardwareFlowControl;

	USART_Init(USARTx, &USART_InitStruct);

	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

	USART_Cmd(USARTx, ENABLE);

	USART_NVIC_Initialise(USARTx);
}

/**
 * @brief Initialise USARTx GPIO.
 *
 * @param USARTx		x = 1, 2, 3, 4, 5, 6.
 *
 */
void USART_GPIO_Initialise(USART_TypeDef * USARTx)
{
	if(USARTx == USART1)
	{
		//Pin9 - Tx, Pin10 - Rx.
		GPIO_Initialise(GPIOA,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_9 | GPIO_Pin_10, GPIO_PuPd_UP,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //Tx
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //Rx
	}
	else if(USARTx == USART2)
	{
		//Pin2 - Tx, Pin3 - Rx.
		GPIO_Initialise(GPIOA,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_2 | GPIO_Pin_3, GPIO_PuPd_NOPULL,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //Tx
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //Rx
	}
	else if(USARTx == USART3)
	{
		//Pin10 - Tx, Pin11 - Rx.
		GPIO_Initialise(GPIOB,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_10 | GPIO_Pin_11, GPIO_PuPd_UP,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3); //Tx
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3); //Rx
	}
	else if(USARTx == UART4)
	{
		//Pin0 - Tx, Pin1 - Rx.
		GPIO_Initialise(GPIOA,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_0 | GPIO_Pin_1, GPIO_PuPd_UP,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4); //Tx
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4); //Rx
	}
	else if(USARTx == UART5)
	{
		//Pin12 - Tx, Pin2 - Rx.
		GPIO_Initialise(GPIOC,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_12, GPIO_PuPd_UP,GPIO_Speed_50MHz);
		GPIO_Initialise(GPIOD,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_2, GPIO_PuPd_UP,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5); //Tx
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5); //Rx
	}
	else if(USARTx == USART6)
	{
		//Pin6 - Tx, Pin7 - Rx.
		GPIO_Initialise(GPIOC,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_6 | GPIO_Pin_7, GPIO_PuPd_UP,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6); //Tx
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6); //Rx
	}
	else
	{
		while(1);
	}
}

/**
 * @brief Initialise USARTx RCC.
 *
 * @param USARTx		x = 1, 2, 3, 4, 5, 6.
 *
 */
void USART_RCC_Initialise(USART_TypeDef * USARTx)
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
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	}
	else
	{
		while(1);
	}
}

/**
 * @brief Initialise USARTx NVIC.
 *
 * @param USARTx		x = 1, 2, 3, 4, 5, 6.
 *
 */
void USART_NVIC_Initialise(USART_TypeDef * USARTx)
{
	NVIC_InitTypeDef NVIC_InitStruct;

	if(USARTx == USART1)
	{
		NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	}
	else if(USARTx == USART2)
	{
		NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	}
	else if(USARTx == USART3)
	{
		NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	}
	else if(USARTx == UART4)
	{
		NVIC_InitStruct.NVIC_IRQChannel = UART4_IRQn;
	}
	else if(USARTx == UART5)
	{
		NVIC_InitStruct.NVIC_IRQChannel = UART5_IRQn;
	}
	else if(USARTx == USART6)
	{
		NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
	}
	else
	{
		while(1);
	}

	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

void USART_Write(USART_TypeDef * USARTx, uint16_t Data)
{
	USART_SendData(USARTx,Data);
}

void USART_Read(USART_TypeDef * USARTx)
{
	num[p++] = USART_ReceiveData(USARTx);
	if(p == 1024){
		p = 0;
	}
}
