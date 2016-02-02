/**
  ******************************************************************************
  * @file    L3GD20H.h
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

#define L3GD20H_ADDRESS 				((uint8_t)0x6B)
#define L3GD20H_AXIS_AND_POWER_ON		((uint8_t)0x0F)

#define L3GD20H_REGISTER_CTRL_REG1 		((uint8_t)0x20)
#define L3GD20H_REGISTER_CTRL_REG2 		((uint8_t)0x21)
#define L3GD20H_REGISTER_CTRL_REG3 		((uint8_t)0x22)
#define L3GD20H_REGISTER_CTRL_REG4 		((uint8_t)0x23)
#define L3GD20H_REGISTER_CTRL_REG5 		((uint8_t)0x24)
#define L3GD20H_REGISTER_OUT_X_L 		((uint8_t)0x28)
#define L3GD20H_REGISTER_OUT_X_H 		((uint8_t)0x29)
#define L3GD20H_REGISTER_OUT_Y_L 		((uint8_t)0x2A)
#define L3GD20H_REGISTER_OUT_Y_H 		((uint8_t)0x2B)
#define L3GD20H_REGISTER_OUT_Z_L 		((uint8_t)0x2C)
#define L3GD20H_REGISTER_OUT_Z_H 		((uint8_t)0x2D)

void L3GD20H_Initialize(I2C_TypeDef* I2Cx);
