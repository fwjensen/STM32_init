#include "ION_CAN.h"
#include "ION_GPIO.h"
#include "stm32f4xx_can.h"
#include "stm32f4xx_gpio.h"

void CAN_Initialise(CAN_TypeDef * CANx)
{
	CAN_InitTypeDef CAN_InitStruct;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	CAN_GPIO_Initialise(CANx);
	
	CAN_RCC_Initialise(CANx);
	
	/* CAN register init */
	CAN_DeInit(CANx);
	
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
	CAN_InitStruct.CAN_BS1 = CAN_BS1_10tq; //CAN_BS1_4tq;
	CAN_InitStruct.CAN_BS2 = CAN_BS1_1tq; //CAN_BS2_2tq;
	CAN_InitStruct.CAN_Prescaler = 5;//(42000000 / 7) / 500000; -> 12
	CAN_Init(CANx, &CAN_InitStruct);

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
	CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);

}

void CAN_GPIO_Initialise(CAN_TypeDef * CANx)
{
	if(CANx == CAN1)
	{
		GPIO_Initialise(GPIOA,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_11 | GPIO_Pin_12,GPIO_PuPd_UP,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);
	}
	else if(CANx == CAN2)
	{
		GPIO_Initialise(GPIOB,GPIO_Mode_AF,GPIO_OType_PP,GPIO_Pin_5 | GPIO_Pin_6,GPIO_PuPd_UP,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_CAN2); //RX
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_CAN2); //TX
	}
}

/**
 *
 *
 */
void CAN_RCC_Initialise(CAN_TypeDef * CANx)
{
    if (CANx == CAN1)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
    }
    else if (CANx == CAN2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2,ENABLE);
    }
    else
    {
      while(1);
    }
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
    
	for(i=0; i < length; i++)
    {
		msg.Data[i] = data[i];
	}
	return CAN_Transmit(CAN2, &msg);
}


/*
CAN RX Interrupt
*/

CanRxMsg msgRx;

void CAN2_RX0_IRQHandler (void){
	__disable_irq();
	if(CAN2->RF0R & CAN_RF0R_FMP0)
	{
		CAN_Receive(CAN2, CAN_FIFO0, &msgRx);
	}
	__enable_irq();
}
