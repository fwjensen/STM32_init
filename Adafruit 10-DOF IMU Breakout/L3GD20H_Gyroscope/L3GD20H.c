/**
  ******************************************************************************
  * @file    L3GD20H.c
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

#include "L3GD20H.h"
#include "I2C.h"

void L3GD20H_Initialize(I2C_TypeDef* I2Cx){
	write8(I2Cx,L3GD20H_ADDRESS,L3GD20H_REGISTER_CTRL_REG1,L3GD20H_AXIS_AND_POWER_ON); //Turning on X, Y, Z axis.
}
