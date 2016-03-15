#include "I2C.h"
#include "L3GD20H.h"

/**
 * @brief Initialise the 10-DOF_IUM gyroscope.
 *
 * @param I2Cx		x = 1, 2, 3.
 *
 */
void TEN_DOF_IUM_Initialise(I2C_TypeDef* I2Cx)
{
	//I2C
	I2C_Initialise(I2Cx,I2C_Ack_Enable,I2C_AcknowledgedAddress_7bit, 100000, I2C_DutyCycle_2, I2C_Mode_I2C, 0x00);

	//Accelerometer
	L3GD20H_Initialise(I2Cx);
}
