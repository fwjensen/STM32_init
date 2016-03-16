#include "ION_L3GD20H.h"
#include "ION_I2C.h"

/*************-DEFINES-***************************/
#define I2Cx I2C1

/**
 * @brief Initialise for the L3GD20H.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void L3GD20H_Initialise()
{
    //Typedefs
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

	//Power ON
	I2C_Write8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_CTRL_REG1,L3GD20H_AXIS_AND_POWER_ON);
}

/**
 * @brief Get X axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_X()
{
	return I2C_Read16(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_X_H,L3GD20H_REGISTER_OUT_X_L);
}

/**
 * @brief Get Y axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_Y()
{
	return I2C_Read16(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Y_H,L3GD20H_REGISTER_OUT_Y_L);
}

/**
 * @brief Get X axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_Z()
{
	return I2C_Read16(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Z_H,L3GD20H_REGISTER_OUT_Z_L);
}

/**
 * @brief Get X, Y and Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_XYZ()
{
	uint16_t axis[3];
	axis[0] = L3GD20H_X();
	axis[1] = L3GD20H_Y();
	axis[2] = L3GD20H_Z();
	//FIX THIS LATER!
	return axis[1];
}
