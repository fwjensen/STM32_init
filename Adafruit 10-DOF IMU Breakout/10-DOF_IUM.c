/**
  ******************************************************************************
  * @file    10-DOF_IUM.c
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

#include "I2C.h"

/**
 * @brief Initialise the 10-DOF_IUM gyroscope.
 *
 * @param I2Cx		x = 1, 2, 3.
 *
 */
void TEN_DOF_IUM_Initialise(I2C_TypeDef* I2Cx)
{
	I2C_Initialise(I2Cx,I2C_Ack_Enable,I2C_AcknowledgedAddress_7bit, 100000, I2C_DutyCycle_2, I2C_Mode_I2C, 0x00);

	L3GD20H_Initialise(I2Cx);
}
