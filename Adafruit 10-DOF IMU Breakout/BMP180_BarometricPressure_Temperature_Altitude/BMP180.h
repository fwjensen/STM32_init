/**
  ******************************************************************************
  * @file    BMP180.h
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

#define BMP085_ADDRESS			(uint8_t)0x77

typedef enum
{
	BMP185_CAL_AC1           = (uint8_t)0xAA,
	BMP185_CAL_AC2           = (uint8_t)0xAC,
	BMP185_CAL_AC3           = (uint8_t)0xAE,
	BMP185_CAL_AC4           = (uint8_t)0xB0,
	BMP185_CAL_AC5           = (uint8_t)0xB2,
	BMP185_CAL_AC6           = (uint8_t)0xB4,
	BMP185_CAL_B1            = (uint8_t)0xB6,
	BMP185_CAL_B2            = (uint8_t)0xB8,
	BMP185_CAL_MB            = (uint8_t)0xBA,
	BMP185_CAL_MC            = (uint8_t)0xBC,
	BMP185_CAL_MD            = (uint8_t)0xBE,
	BMP185_CONTROL           = (uint8_t)0xF4,
	BMP185_TEMPDATA          = (uint8_t)0xF6,
	BMP185_PRESSUREDATA      = (uint8_t)0xF6,
	BMP185_READTEMPCMD       = (uint8_t)0x2E,
	BMP185_READPRESSURECMD   = (uint8_t)0x34
} bmp180Registers_t;
