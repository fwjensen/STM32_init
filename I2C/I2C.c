/**
  ******************************************************************************
  * @file    I2C.c
  * @author  Fredrik Wigsnes
  *******************************************************************************
  * @attention
  *
  * MAY BE USED FREE OF CHARGE.
  * SELLING WITHOUT PRIOR WRITTEN CONSENT PROHIBITED.
  *
  * <h2><center>&copy; COPYRIGHT 2016 ION Racing</center></h2>
  ******************************************************************************
  */

/*-----------------------------------------------------------------------------*/

#include "stm32f4xx_i2c.h"
#include "stm32f4xx_gpio.h"
#include "GPIO.h"
#include "RCC.h"

/**
 * @brief Initializing the I2Cx.
 *
 * @param I2Cx						x = 1, 2, 3.
 * @param Ack						I2C_Ack_x x => x = Enable, Disable.
 * @param AcknowledgedAddress		I2C_AcknowledgedAddress_x => x = 7bit, 10bit.
 * @param ClockSpeed				Standard 100KHz, check Manual.
 * @param DutyCycle					I2C_DutyCycle_x x => 2, 16_9.
 * @param Mode						I2C_Mode_x x => I2C, SMBusDevice, SMBusHost.
 * @param OwnAddress1				Master address not relevant.
 *
 */
void I2C_Initialize(I2C_TypeDef* I2Cx, uint16_t Ack, uint16_t AcknowledgedAdress, uint32_t ClockSpeed, uint16_t DutyCycle, uint16_t Mode, uint16_t OwnAddress1)
{
	if(I2Cx == I2C1){
		GPIO_Initialize(GPIOB,GPIO_Mode_AF,GPIO_OType_OD,GPIO_Pin_6 | GPIO_Pin_9, GPIO_PuPd_NOPULL,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
	}else if(I2Cx == I2C2){
		GPIO_Initialize(GPIOB,GPIO_Mode_AF,GPIO_OType_OD,GPIO_Pin_10 | GPIO_Pin_11, GPIO_PuPd_NOPULL,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);
	}else if(I2Cx == I2C3){
		GPIO_Initialize(GPIOA,GPIO_Mode_AF,GPIO_OType_OD,GPIO_Pin_8, GPIO_PuPd_NOPULL,GPIO_Speed_50MHz);
		GPIO_Initialize(GPIOC,GPIO_Mode_AF,GPIO_OType_OD,GPIO_Pin_9, GPIO_PuPd_NOPULL,GPIO_Speed_50MHz);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_I2C3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_I2C3);
	}else{
	 while(1);
	}

	I2C_InitTypeDef I2C_InitStruct;

	RCC_I2C_DeInit(I2Cx);

	RCC_I2C_Init(I2Cx);

	I2C_InitStruct.I2C_Ack = Ack;
	I2C_InitStruct.I2C_AcknowledgedAddress = AcknowledgedAdress;
	I2C_InitStruct.I2C_ClockSpeed = ClockSpeed;
	I2C_InitStruct.I2C_DutyCycle = DutyCycle;
	I2C_InitStruct.I2C_Mode = Mode;
	I2C_InitStruct.I2C_OwnAddress1 = OwnAddress1;

	I2C_Init(I2Cx,&I2C_InitStruct);

	I2C_Cmd(I2Cx, ENABLE);
}

void write8(I2C_TypeDef* I2Cx,uint8_t addr, uint8_t reg, uint8_t data)
{
	I2C_AcknowledgeConfig(I2Cx,ENABLE);
	while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

	I2C_GenerateSTART(I2Cx,ENABLE);
	while(!I2C_GetFlagStatus(I2Cx, I2C_FLAG_SB));

	I2C_Send7bitAddress(I2Cx,reg<<1,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2Cx,addr);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(I2Cx,data);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(I2Cx,ENABLE);
	while(I2C_GetFlagStatus(I2Cx,I2C_FLAG_STOPF));
}

uint8_t read8(I2C_TypeDef* I2Cx, uint8_t addr, uint8_t reg)
{
	uint8_t data = 0;

	I2C_AcknowledgeConfig(I2Cx,ENABLE);
	while(I2C_GetFlagStatus(I2Cx,I2C_FLAG_BUSY));

	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_GetFlagStatus(I2Cx,I2C_FLAG_SB));
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(I2Cx,reg<<1,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2Cx,addr);
	while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTART(I2Cx,ENABLE);
	while(!I2C_GetFlagStatus(I2Cx,I2C_FLAG_SB));

	I2C_Send7bitAddress(I2Cx,reg<<1,I2C_Direction_Receiver);
	while (!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	I2C_NACKPositionConfig(I2Cx,I2C_NACKPosition_Current);
	I2C_AcknowledgeConfig(I2Cx,DISABLE);

	//need to add a wait here for new data, right now it goes to fast to get the new data.
	while(!I2C_GetFlagStatus(I2Cx,I2C_FLAG_RXNE));
	data = I2C_ReceiveData(I2Cx);
	//while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED));

	I2C_GenerateSTOP(I2Cx,ENABLE);
	while(I2C_GetFlagStatus(I2Cx,	I2C_FLAG_STOPF));

	return data;
}
