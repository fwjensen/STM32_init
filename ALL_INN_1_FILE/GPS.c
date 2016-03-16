#include "GPS.h"
#include "stm32f4xx_usart.h"

volatile char num[1024];
volatile int p = 0;

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
    GPIO_Initialise();
    USART_Initialise();
    NVIC_Initialise();
}

void GPIO_Initialise()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA,DISABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //Tx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //Rx
}

void USART_Initialise()
{
	USART_InitTypeDef USART_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2, &USART_InitStruct);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}

void NVIC_Initialise()
{
	NVIC_InitTypeDef NVIC_InitStruct;
    
    NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

void USART2_IRQHandler(void)
{
	// check if the USART1 receive interrupt flag was set
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
		USART_Read();
	}
}

void USART_Write(uint16_t Data)
{
	USART_SendData(USART2,Data);
}

void USART_Read()
{
	num[p++] = USART_ReceiveData(USART2);
	if(p == 1024)
    {
		p = 0;
	}
}
