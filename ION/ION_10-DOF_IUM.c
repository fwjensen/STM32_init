#include "ION_I2C.h"
#include "ION_L3GD20H.h"
#include "ION_LSM303.h"
#include "ION_BMP180.h"

/**
 * @brief Initialise the 10-DOF_IUM.
 *
 * @param I2Cx		x = 1, 2, 3.
 *
 */
void TEN_DOF_IUM_Initialise(I2C_TypeDef* I2Cx)
{
	//I2C
	I2C_Initialise(I2Cx,I2C_Ack_Enable,I2C_AcknowledgedAddress_7bit, 100000, I2C_DutyCycle_2, I2C_Mode_I2C, 0x00);

    //Periph
	_L3GD20H_Initialise(I2Cx);
    _LSM303_ACCEL_Initialise(I2Cx);
    _LSM303_MAG_Initialise(I2Cx);
    _BMP180_Initialise(I2Cx);
}
