#include "LSM303.h"
#include "I2C.h"

/**
 * @brief Initialise for the LSM303 Accelerometer.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void LSM303_ACCEL_Initialise(I2C_TypeDef* I2Cx)
{
	I2C_Write8(I2Cx,LSM303_ADDRESS_ACCEL,LSM303_REGISTER_ACCEL_CTRL_REG1_A,0x57);
}

/**
 * @brief Initialise for the LSM303 Magnetometer.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void LSM303_MAG_Initialise(I2C_TypeDef* I2Cx)
{
	I2C_Write8(I2Cx,LSM303_ADDRESS_MAG,LSM303_REGISTER_MAG_CRA_REG_M,0x00);
	//Gain 1.3
	I2C_Write8(LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_CRB_REG_M,LSM303_MAGGAIN_1_3);
}

/**
 * @brief Get Accelerometer X axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_ACCEL_X(I2C_TypeDef* I2Cx)
{
	return I2C_Read16(I2Cx,LSM303_ADDRESS_ACCEL,LSM303_REGISTER_ACCEL_OUT_X_H_A,LSM303_REGISTER_ACCEL_OUT_X_L_A);
}

/**
 * @brief Get Accelerometer Y axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_ACCEL_Y(I2C_TypeDef* I2Cx)
{
	return I2C_Read16(I2Cx,LSM303_ADDRESS_ACCEL,LSM303_REGISTER_ACCEL_OUT_Y_H_A,LSM303_REGISTER_ACCEL_OUT_Y_L_A);
}

/**
 * @brief Get Accelerometer Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_ACCEL_Z(I2C_TypeDef* I2Cx)
{
	return I2C_Read16(I2Cx,LSM303_ADDRESS_ACCEL,LSM303_REGISTER_ACCEL_OUT_Z_H_A,LSM303_REGISTER_ACCEL_OUT_Z_L_A);
}

/**
 * @brief Get Accelerometer X, Y and Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_ACCEL_XYZ(I2C_TypeDef* I2Cx)
{
	uint16_t axis[3];
	axis[0] = LSM303_ACCEL_X(I2Cx);
	axis[1] = LSM303_ACCEL_Y(I2Cx);
	axis[2] = LSM303_ACCEL_Z(I2Cx);
	return axis;
}

/**
 * @brief Get Magnetometer X axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_MAG_X(I2C_TypeDef* I2Cx)
{
	return I2C_Read16(I2Cx,LSM303_ADDRESS_MAG,LSM303_REGISTER_MAG_OUT_X_H_M,LSM303_REGISTER_MAG_OUT_X_L_M);
}

/**
 * @brief Get Magnetometer Y axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_MAG_Y(I2C_TypeDef* I2Cx)
{
	return I2C_Read16(I2Cx,LSM303_ADDRESS_MAG,LSM303_REGISTER_MAG_OUT_Y_H_M,LSM303_REGISTER_MAG_OUT_Y_L_M);
}

/**
 * @brief Get Magnetometer Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_MAG_Z(I2C_TypeDef* I2Cx)
{
	return I2C_Read16(I2Cx,LSM303_ADDRESS_MAG,LSM303_REGISTER_MAG_OUT_Z_H_M,LSM303_REGISTER_MAG_OUT_Z_L_M);
}

/**
 * @brief Get Magnetometer X, Y and Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 */
uint16_t LSM303_MAG_XYZ(I2C_TypeDef* I2Cx)
{
	uint16_t axis[3];
	axis[0] = LSM303_MAG_X(I2Cx);
	axis[1] = LSM303_MAG_Y(I2Cx);
	axis[2] = LSM303_MAG_Z(I2Cx);
	return axis;
}
