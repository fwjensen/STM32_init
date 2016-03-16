#include "stm32f4xx_can.h"
#include "stm32f4xx_gpio.h"
#include "CAN.h"

void CAN_Initialise()
{
	CAN_InitTypeDef CAN_InitStruct;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	void GPIO_Initialise();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2,ENABLE);
	
	/* CAN register init */
	CAN_DeInit(CAN2);
	
	/* CAN cell init */
	CAN_InitStruct.CAN_TTCM = DISABLE;
	CAN_InitStruct.CAN_ABOM = DISABLE;
	CAN_InitStruct.CAN_AWUM = DISABLE;
	CAN_InitStruct.CAN_NART = DISABLE;
	CAN_InitStruct.CAN_RFLM = DISABLE;
	CAN_InitStruct.CAN_TXFP = DISABLE;
	CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStruct.CAN_SJW = CAN_SJW_3tq;

    //Bus length 3-5m.
    
	/* CAN Baudrate = 500 KBps (CAN clocked at 42 MHz) */
	CAN_InitStruct.CAN_BS1 = CAN_BS1_4tq;
	CAN_InitStruct.CAN_BS2 = CAN_BS2_2tq;
	CAN_InitStruct.CAN_Prescaler = (42000000 / 7) / 500000; //12
	CAN_Init(CAN2, &CAN_InitStruct);

	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber = 0;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	/* Enable FIFO 0 message pending Interrupt */
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);

}

void GPIO_Initialise()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOA,DISABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
    
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN2); //Tx
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN2); //Rx
}

// CAN Transmit
uint8_t i = 0;

uint8_t CAN_Write(uint32_t address, uint8_t length, uint8_t data[8])
{
    CanTxMsg msg;
	msg.StdId 	= address;
	msg.IDE 	= CAN_Id_Standard;
	msg.RTR		= CAN_RTR_Data;
	msg.DLC		= length;
    
	for(i=0; i < length; i++){
		msg.Data[i] = data[i];
	}
 
	return CAN_Transmit(CAN2, &msg);
}


/*
CAN RX Interrupt
*/

CanRxMsg msgRx;

void CAN2_RX0_IRQHandler(void){
	__disable_irq();
	if(CAN2->RF0R & CAN_RF0R_FMP0)
	{
		CAN_Receive(CAN2, CAN_FIFO0, &msgRx);
		
	}
	__enable_irq();
}
