/**
  ******************************************************************************
  * @file    BMP180.c
  * @author  Fredrik Wigsnes
  *******************************************************************************
  * @verbatim
  *
  *          ===================================================================
  *                                 How to use this driver
  *          ===================================================================
  *          1.
  *
  *          2.
  *
  *          3.
  *
  *          4.
  *
  *          5.
  *
  *          6.
  *
  *          7.
  *
  *          8.
  *
  *          9.
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

/**
 * @brief Initialise for the BMP180.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void BMP180_Initialise(I2C_TypeDef* I2Cx){
	I2C_Write8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_CTRL_REG1,L3GD20H_AXIS_AND_POWER_ON); //Turning on X, Y, Z axis.
}

/**
 * @brief Get X axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_X(I2C_TypeDef* I2Cx){
	return (I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_X_L)|(I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_X_H)<<8));
}

/**
 * @brief Get Y axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_Y(I2C_TypeDef* I2Cx){
	return (I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Y_L)|(I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Y_H)<<8));
}

/**
 * @brief Get Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_Z(I2C_TypeDef* I2Cx){
	return (I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Z_L)|(I2C_Read8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_OUT_Z_H)<<8));
}

/**
 * @brief Get X, Y and Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t L3GD20H_XYZ(I2C_TypeDef* I2Cx){
	uint16_t axis[3];
	axis[0] = L3GD20H_X(I2Cx);
	axis[1] = L3GD20H_Y(I2Cx);
	axis[2] = L3GD20H_Z(I2Cx);
	return axis;
}
