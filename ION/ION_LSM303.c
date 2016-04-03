#include "ION_LSM303.h"
#include "ION_I2C.h"

I2C_TypeDef* I2C = I2C2;

/**
 * @brief Initialise for the LSM303 Accelerometer.
 * 
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void _LSM303_ACCEL_Initialise(I2C_TypeDef* I2Cx)
{
    //I2C
    I2C = I2Cx;
    
    //Power ON
	I2C_Write8(I2C, LSM303_ADDRESS_ACCEL, LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x57);
}

/**
 * @brief Initialise for the LSM303 Accelerometer.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void LSM303_ACCEL_Initialise(I2C_TypeDef* I2Cx)
{
    //I2C
    I2C = I2Cx;
    I2C_Initialise(I2Cx,I2C_Ack_Enable,I2C_AcknowledgedAddress_7bit, 100000, I2C_DutyCycle_2, I2C_Mode_I2C, 0x00);
    
    //Power ON
	I2C_Write8(I2Cx, LSM303_ADDRESS_ACCEL, LSM303_REGISTER_ACCEL_CTRL_REG1_A, 0x57);
}

/**
 * @brief Initialise for the LSM303 Magnetometer.
 * 
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void _LSM303_MAG_Initialise(I2C_TypeDef* I2Cx)
{
    //I2C
    I2C = I2Cx;
    
    //Power ON
	I2C_Write8(I2C, LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_CRA_REG_M, 0x00);
	//Gain 1.3
	I2C_Write8(I2C, LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_CRB_REG_M, LSM303_MAGGAIN_1_3);
}

/**
 * @brief Initialise for the LSM303 Magnetometer.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void LSM303_MAG_Initialise(I2C_TypeDef* I2Cx)
{
    //I2C
    I2C = I2Cx;
	I2C_Initialise(I2Cx,I2C_Ack_Enable,I2C_AcknowledgedAddress_7bit, 100000, I2C_DutyCycle_2, I2C_Mode_I2C, 0x00);

	I2C_Write8(I2C, LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_CRA_REG_M, 0x00);
	//Gain 1.3
	I2C_Write8(I2C, LSM303_ADDRESS_MAG, LSM303_REGISTER_MAG_CRB_REG_M, LSM303_MAGGAIN_1_3);
}

/**
 * @brief Get Accelerometer X axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_ACCEL_X()
{
	return I2C_Read16(I2C,LSM303_ADDRESS_ACCEL,LSM303_REGISTER_ACCEL_OUT_X_H_A,LSM303_REGISTER_ACCEL_OUT_X_L_A);
}

/**
 * @brief Get Accelerometer Y axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_ACCEL_Y()
{
	return I2C_Read16(I2C,LSM303_ADDRESS_ACCEL,LSM303_REGISTER_ACCEL_OUT_Y_H_A,LSM303_REGISTER_ACCEL_OUT_Y_L_A);
}

/**
 * @brief Get Accelerometer Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_ACCEL_Z()
{
	return I2C_Read16(I2C,LSM303_ADDRESS_ACCEL,LSM303_REGISTER_ACCEL_OUT_Z_H_A,LSM303_REGISTER_ACCEL_OUT_Z_L_A);
}

/**
 * @brief Get Accelerometer X, Y and Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
lsm303AccelAxis LSM303_ACCEL_XYZ()
{
	lsm303AccelAxis AXIS;
	AXIS.X = LSM303_ACCEL_X();
	AXIS.Y = LSM303_ACCEL_Y();
	AXIS.Z = LSM303_ACCEL_Z();
	return AXIS;
}

/**
 * @brief Get Magnetometer X axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_MAG_X()
{
	return I2C_Read16(I2C,LSM303_ADDRESS_MAG,LSM303_REGISTER_MAG_OUT_X_H_M,LSM303_REGISTER_MAG_OUT_X_L_M);
}

/**
 * @brief Get Magnetometer Y axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_MAG_Y()
{
	return I2C_Read16(I2C,LSM303_ADDRESS_MAG,LSM303_REGISTER_MAG_OUT_Y_H_M,LSM303_REGISTER_MAG_OUT_Y_L_M);
}

/**
 * @brief Get Magnetometer Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
uint16_t LSM303_MAG_Z()
{
	return I2C_Read16(I2C,LSM303_ADDRESS_MAG,LSM303_REGISTER_MAG_OUT_Z_H_M,LSM303_REGISTER_MAG_OUT_Z_L_M);
}

/**
 * @brief Get Magnetometer X, Y and Z axis.
 *
 * @param I2Cx			x = 1, 2, 3.
 */
lsm303MagAxis LSM303_MAG_XYZ()
{
	lsm303MagAxis AXIS;
	AXIS.X = LSM303_MAG_X();
	AXIS.Y = LSM303_MAG_Y();
	AXIS.Z = LSM303_MAG_Z();
	return AXIS;
}
