/**
  ******************************************************************************
  * @file    10-DOF_IUM.c
  * @author  Fredrik Wigsnes
  *******************************************************************************
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

void TEN_DOF_IUM_Initialize(I2C_TypeDef* I2Cx)
{
	I2C_Initialize(I2Cx,I2C_Ack_Enable,I2C_AcknowledgedAddress_7bit, 100000, I2C_DutyCycle_2, I2C_Mode_I2C, 0x00);

	L3GD20H_Initialize(I2Cx);
}
