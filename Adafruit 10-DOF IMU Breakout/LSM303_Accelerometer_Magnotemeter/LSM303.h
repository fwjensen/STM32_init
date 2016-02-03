/**
  ******************************************************************************
  * @file    LSM303.h
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

//#define LSM303_REGISTER_ACCEL_CTRL_REG1_A         = 0x20
//#define LSM303_REGISTER_ACCEL_CTRL_REG2_A         = 0x21
//#define LSM303_REGISTER_ACCEL_CTRL_REG3_A         = 0x22
//#define LSM303_REGISTER_ACCEL_CTRL_REG4_A         = 0x23
//#define LSM303_REGISTER_ACCEL_CTRL_REG5_A         = 0x24
//#define LSM303_REGISTER_ACCEL_CTRL_REG6_A         = 0x25
//#define LSM303_REGISTER_ACCEL_REFERENCE_A      ((uint8_t)0x26)
//#define LSM303_REGISTER_ACCEL_STATUS_REG_A     ((uint8_t)0x27)
//#define LSM303_REGISTER_ACCEL_OUT_X_L_A        ((uint8_t)0x28)
//#define LSM303_REGISTER_ACCEL_OUT_X_H_A        ((uint8_t)0x29)
//#define LSM303_REGISTER_ACCEL_OUT_Y_L_A        ((uint8_t)0x2A)
//#define LSM303_REGISTER_ACCEL_OUT_Y_H_A        ((uint8_t)0x2B)
//#define LSM303_REGISTER_ACCEL_OUT_Z_L_A        ((uint8_t)0x2C)
//#define LSM303_REGISTER_ACCEL_OUT_Z_H_A        ((uint8_t)0x2D)

typedef enum
    {
      LSM303_REGISTER_ACCEL_CTRL_REG1_A         = 0x20,
      LSM303_REGISTER_ACCEL_CTRL_REG2_A         = 0x21,
      LSM303_REGISTER_ACCEL_CTRL_REG3_A         = 0x22,
      LSM303_REGISTER_ACCEL_CTRL_REG4_A         = 0x23,
      LSM303_REGISTER_ACCEL_CTRL_REG5_A         = 0x24,
      LSM303_REGISTER_ACCEL_CTRL_REG6_A         = 0x25,
      LSM303_REGISTER_ACCEL_REFERENCE_A         = 0x26,
      LSM303_REGISTER_ACCEL_STATUS_REG_A        = 0x27,
      LSM303_REGISTER_ACCEL_OUT_X_L_A           = 0x28,
      LSM303_REGISTER_ACCEL_OUT_X_H_A           = 0x29,
      LSM303_REGISTER_ACCEL_OUT_Y_L_A           = 0x2A,
      LSM303_REGISTER_ACCEL_OUT_Y_H_A           = 0x2B,
      LSM303_REGISTER_ACCEL_OUT_Z_L_A           = 0x2C,
      LSM303_REGISTER_ACCEL_OUT_Z_H_A           = 0x2D,
      LSM303_REGISTER_ACCEL_FIFO_CTRL_REG_A     = 0x2E,
      LSM303_REGISTER_ACCEL_FIFO_SRC_REG_A      = 0x2F,
      LSM303_REGISTER_ACCEL_INT1_CFG_A          = 0x30,
      LSM303_REGISTER_ACCEL_INT1_SOURCE_A       = 0x31,
      LSM303_REGISTER_ACCEL_INT1_THS_A          = 0x32,
      LSM303_REGISTER_ACCEL_INT1_DURATION_A     = 0x33,
      LSM303_REGISTER_ACCEL_INT2_CFG_A          = 0x34,
      LSM303_REGISTER_ACCEL_INT2_SOURCE_A       = 0x35,
      LSM303_REGISTER_ACCEL_INT2_THS_A          = 0x36,
      LSM303_REGISTER_ACCEL_INT2_DURATION_A     = 0x37,
      LSM303_REGISTER_ACCEL_CLICK_CFG_A         = 0x38,
      LSM303_REGISTER_ACCEL_CLICK_SRC_A         = 0x39,
      LSM303_REGISTER_ACCEL_CLICK_THS_A         = 0x3A,
      LSM303_REGISTER_ACCEL_TIME_LIMIT_A        = 0x3B,
      LSM303_REGISTER_ACCEL_TIME_LATENCY_A      = 0x3C,
      LSM303_REGISTER_ACCEL_TIME_WINDOW_A       = 0x3D
    } lsm303AccelRegisters_t;
