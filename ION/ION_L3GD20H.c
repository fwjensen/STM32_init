#include "ION_L3GD20H.h"
#include "ION_I2C.h"

I2C_TypeDef* I2C = I2C2;

/**
 * @brief Initialise for the L3GD20H.
 *
 */
void _L3GD20H_Initialise(I2C_TypeDef* I2Cx)
{
    //I2C
    I2C = I2Cx;
	//Power ON
	I2C_Write8(I2C,L3GD20H_ADDRESS,L3GD20H_REGISTER_CTRL_REG1,L3GD20H_AXIS_AND_POWER_ON);
}

/**
 * @brief Initialise for the L3GD20H.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void L3GD20H_Initialise(I2C_TypeDef* I2Cx)
{
    //I2C
    I2C = I2Cx;
	I2C_Initialise(I2Cx,I2C_Ack_Enable,I2C_AcknowledgedAddress_7bit, 100000, I2C_DutyCycle_2, I2C_Mode_I2C, 0x00);

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
	return I2C_Read16(I2C,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_X_H,L3GD20H_REGISTER_OUT_X_L);
}

/**
 * @brief Get Y axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_Y()
{
	return I2C_Read16(I2C,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Y_H,L3GD20H_REGISTER_OUT_Y_L);
}

/**
 * @brief Get X axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_Z()
{
	return I2C_Read16(I2C,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Z_H,L3GD20H_REGISTER_OUT_Z_L);
}

/**
 * @brief Get X, Y and Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 * Returns a struct.
 */
l3gd20hAxis L3GD20H_XYZ()
{
	l3gd20hAxis AXIS;
	AXIS.X = L3GD20H_X();
	AXIS.Y = L3GD20H_Y();
	AXIS.Z = L3GD20H_Z();
	return AXIS;
}
