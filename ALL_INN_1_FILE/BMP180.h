#include "stm32f4xx.h"

#define BMP180_ADDRESS	(uint8_t)0x77

typedef enum
{
	BMP180_CAL_AC1_MSB			= 0xAA,
	BMP180_CAL_AC1_LSB			= 0xAB,
	BMP180_CAL_AC2_MSB			= 0xAC,
	BMP180_CAL_AC2_LSB			= 0xAD,
	BMP180_CAL_AC3_MSB			= 0xAE,
	BMP180_CAL_AC3_LSB			= 0xAF,
	BMP180_CAL_AC4_MSB			= 0xB0,
	BMP180_CAL_AC4_LSB			= 0xB1,
	BMP180_CAL_AC5_MSB			= 0xB2,
	BMP180_CAL_AC5_LSB			= 0xB3,
	BMP180_CAL_AC6_MSB			= 0xB4,
	BMP180_CAL_AC6_LSB			= 0xB4,
	BMP180_CAL_B1_MSB			= 0xB6,
	BMP180_CAL_B1_LSB			= 0xB7,
	BMP180_CAL_B2_MSB			= 0xB8,
	BMP180_CAL_B2_LSB			= 0xB9,
	BMP180_CAL_MB_MSB			= 0xBA,
	BMP180_CAL_MB_LSB			= 0xBB,
	BMP180_CAL_MC_MSB			= 0xBC,
	BMP180_CAL_MC_LSB			= 0xBD,
	BMP180_CAL_MD_MSB			= 0xBE,
	BMP180_CAL_MD_LSB			= 0xBF,
	BMP180_CONTROL				= 0xF4,
	BMP180_TEMPDATA_MSB			= 0xF6,
	BMP180_TEMPDATA_LSB			= 0xF7,
	BMP180_PRESSUREDATA_MSB		= 0xF6,
	BMP180_PRESSUREDATA_LSB		= 0xF7,
	BMP180_PRESSUREDATA_XLSB	= 0xF8,
	BMP180_READTEMPCMD			= 0x2E,
	BMP180_READPRESSURECMD		= 0x34
}bmp180Registers_t;

typedef enum
{
	BMP180_OSS_SINGLE			= 0x00,
	BMP180_OSS_2TIMES			= 0x01,
	BMP180_OSS_4TIMES			= 0x02,
	BMP180_OSS_8TIMES			= 0x03
}bmp180Oss_t;

void BMP180_Initialise(void);
void GPIO_Initialise(void);
void I2C_Initialise(void);
void I2C_Write8
(
    uint8_t addr, 
    uint8_t reg, 
    uint8_t data
);
uint8_t I2C_Read8
(
    uint8_t addr, 
    uint8_t reg
);
uint16_t I2C_Read16
(
    uint8_t addr, 
    uint8_t reg_MSB, 
    uint8_t reg_LSB
);
void BMP180_CalibrationData(void);
int32_t BMP180_Temperature(bmp180Oss_t oss);
int32_t BMP180_Pressure(bmp180Oss_t oss);
