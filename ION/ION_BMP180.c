#include "ION_I2C.h"
#include "ION_BMP180.h"

I2C_TypeDef* I2C = I2C2;

//short
int16_t AC1 = 0, AC2 = 0, AC3 = 0, B1 = 0, B2 = 0, MB = 0, MC = 0, MD = 0;
//unsigned short
uint16_t  AC4 = 0, AC5 = 0, AC6 = 0;
//long
int32_t  UT = 0, UP = 0, X1 = 0, X2 = 0, B5 = 0, T = 0, B6 = 0, X3 = 0, B3 = 0, P = 0;
//unsigned long
uint32_t B4 = 0, B7 = 0;

int time = 0;

/**
 * @brief Initialise for the BMP180.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void _BMP180_Initialise(I2C_TypeDef* I2Cx)
{
    //I2C
    I2C = I2Cx;
    //Power ON
	I2C_Write8(I2Cx,BMP180_ADDRESS,BMP180_CAL_AC1_LSB,0x00);
}

/**
 * @brief Initialise for the BMP180.
 *
 * @param I2Cx			x = 1, 2, 3.
 *
 */
void BMP180_Initialise(I2C_TypeDef* I2Cx)
{
    //I2C
    I2C = I2Cx;
	I2C_Initialise(I2Cx,I2C_Ack_Enable,I2C_AcknowledgedAddress_7bit, 100000, I2C_DutyCycle_2, I2C_Mode_I2C, 0x00);

    //Power ON
	I2C_Write8(I2Cx,BMP180_ADDRESS,BMP180_CAL_AC1_LSB,0x00);
}

void BMP180_CalibrationData()
{
	AC1 = (int16_t)I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_AC1_MSB,BMP180_CAL_AC1_LSB);
	AC2 = (int16_t)I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_AC2_MSB,BMP180_CAL_AC2_LSB);
	AC3 = (int16_t)I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_AC3_MSB,BMP180_CAL_AC3_LSB);
	AC4 = I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_AC4_MSB,BMP180_CAL_AC4_LSB);
	AC5 = I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_AC5_MSB,BMP180_CAL_AC5_LSB);
	AC6 = I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_AC6_MSB,BMP180_CAL_AC6_LSB);
	B1 = (int16_t)I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_B1_MSB,BMP180_CAL_B1_LSB);
	B2 = (int16_t)I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_B2_MSB,BMP180_CAL_B2_LSB);
	MB = (int16_t)I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_MB_MSB,BMP180_CAL_MB_LSB);
	MC = (int16_t)I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_MC_MSB,BMP180_CAL_MC_LSB);
	MD = (int16_t)I2C_Read16(I2C,BMP180_ADDRESS,BMP180_CAL_MD_MSB,BMP180_CAL_MD_LSB);
}

int32_t BMP180_Temperature(bmp180Oss_t oss)
{
	I2C_Write8(I2C,BMP180_ADDRESS,BMP180_CONTROL,BMP180_READTEMPCMD);
	for(time = 0;time < 0xFFF;time++); // wait 4.5ms
	UT = I2C_Read16(I2C,BMP180_ADDRESS,BMP180_TEMPDATA_MSB,BMP180_TEMPDATA_LSB);

	X1 = (UT - AC6) * AC5 / 32768;
	X2 = MC * 2048 / (X1 + MD);
	B5 = X1 + X2;
	T = (B5 + 8) / 16; //Temperature
	return T;
}

int32_t BMP180_Pressure(bmp180Oss_t oss)
{
	I2C_Write8(I2C,BMP180_ADDRESS,BMP180_CONTROL,BMP180_READPRESSURECMD+(oss<<6));
	for(time = 0;time < 0xfff;time++); //wait?
	UP = (I2C_Read16(I2C,BMP180_ADDRESS,BMP180_PRESSUREDATA_MSB,BMP180_PRESSUREDATA_LSB)<<8)+(I2C_Read8(I2C,BMP180_ADDRESS,BMP180_PRESSUREDATA_XLSB)>>(8-oss));

	B6 = B5 - 4000;
	X1 = (B2 * (B6 * B6 / 4096)) / 2048;
	X2 = AC2 * B6 / 2048;
	X3 = X1 + X2;
	B3 = (((AC1 * 4  + X3)<<oss) + 2) / 4;
	X1 = AC3 * B6 / 8192;
	X2 = (B1 * (B6 * B6 / 4096))/65536;
	X3 = ((X1 + X2) + 2) / 4;
	B4 = AC4 * (uint32_t)(X3 + 32768) / 32768;
	B7 = ((uint32_t)(UP - B3)) * (50000>>oss);
	if(B7 <  0x80000000){P = (B7 * 2) / B4;}
	else{P = (B7 / B4) * 2;}
	X1 = (P / 256) * (P / 258);
	X1 = (X1 * 3038) / 65536;
	X2 = ((-7357) * P) / 65536;
	P = P + (X1 + X2 + 3791) / 16; //Pressure
	return P;
}
