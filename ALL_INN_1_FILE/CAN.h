#include "stm32f4xx_can.h"

void CAN_Initialise(CAN_TypeDef * CANx);
void CAN_RCC_Initialise(CAN_TypeDef * CANx);
void CAN_GPIO_Initialise(CAN_TypeDef * CANx);
uint8_t CAN_Write(uint32_t address, uint8_t length, uint8_t data[8]);
void CAN1_RX0_IRQHandler (void);
