#include "stm32f4xx_can.h"

void CAN_Initialise();
void GPIO_Initialise(void);
uint8_t CAN_Write(uint32_t address, uint8_t length, uint8_t data[8]);
void CAN1_RX0_IRQHandler(void);
