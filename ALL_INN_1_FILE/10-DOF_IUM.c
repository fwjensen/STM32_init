#include "I2C.h"
#include "L3GD20H.h"
#include "stm32f4xx_gpio.h"

/**************-DEFINES-*************************/
#define I2Cx I2C1

/**
 * @brief Initialise the 10-DOF_IUM gyroscope.
 *
 * @param I2Cx		x = 1, 2, 3.
 *
 */
void TEN_DOF_IUM_Initialise()
{
    I2C_InitTypeDef I2C_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
	
    //GPIO
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphResetCmd(RCC_AHB1Periph_GPIOB, DISABLE);
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    //IS THIS POSSIBLE > GPIO_PinAFConfig(GPIOB, GPIO_PinSource6 | GPIO_PinSource9, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
    
    //I2C
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 100000;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_Init(I2Cx, &I2C_InitStruct);

	I2C_Cmd(I2Cx, ENABLE);

	//Accelerometer
	L3GD20H_Initialise(I2Cx);
}
