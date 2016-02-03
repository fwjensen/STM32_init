/**
  ******************************************************************************
  * @file    L3GD20H.c
  * @author  Fredrik Wigsnes
  *******************************************************************************
  * @verbatim
  *
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================
  *          1.	Initialise I2Cx/GPIOx.
  *
  *          2. Initialise L3GD20H.
  *
  *          3.	Now you can use the methods to get X, Y, Z.
  *
  * @endverbatim
  ******************************************************************************
  * @attention
  *
  * MAY BE USED FREE OF CHARGE.
  * SELLING WITHOUT PRIOR WRITTEN CONSENT PROHIBITED.
  *
  * <h2><center>&copy; COPYRIGHT 2016 ION Racing</center></h2>
  ******************************************************************************
  */

/*-----------------------------------------------------------------------------*/
#include "L3GD20H.h"
#include "I2C.h"

/**
 * @brief Initialise for the L3GD20H.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void L3GD20H_Initialise(I2C_TypeDef* I2Cx)
{
	I2C_Write8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_CTRL_REG1,L3GD20H_AXIS_AND_POWER_ON); //Turning on X, Y, Z axis.
}

/**
 * @brief Get X axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_X(I2C_TypeDef* I2Cx)
{
	return (I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_X_L)|(I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_X_H)<<8));
}

/**
 * @brief Get Y axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_Y(I2C_TypeDef* I2Cx)
{
	return (I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Y_L)|(I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Y_H)<<8));
}

/**
 * @brief Get X axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_Z(I2C_TypeDef* I2Cx)
{
	return (I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Z_L)|(I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Z_H)<<8));
}

/**
 * @brief Get X, Y and Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_XYZ(I2C_TypeDef* I2Cx)
{
	uint16_t axis[3];
	axis[0] = L3GD20H_X(I2Cx);
	axis[1] = L3GD20H_Y(I2Cx);
	axis[2] = L3GD20H_Z(I2Cx);
	return axis;
}
