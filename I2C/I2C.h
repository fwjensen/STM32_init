/**
  ******************************************************************************
  * @file    I2C.h
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

void I2C_Initialise
(
	I2C_TypeDef* I2Cx,
	uint16_t Ack,
	uint16_t AcknowledgedAdress,
	uint32_t ClockSpeed,
	uint16_t DutyCycle,
	uint16_t Mode,
	uint16_t OwnAddress1
);

void I2C_Write8
(
	I2C_TypeDef* I2Cx,
	uint8_t addr,
	uint8_t reg,
	uint8_t data
);

uint8_t I2C_Read8
(
	I2C_TypeDef* I2Cx,
	uint8_t addr,
	uint8_t reg
);

uint16_t I2C_Read16
(
		I2C_TypeDef* I2Cx,
		uint8_t addr,
		uint8_t reg_MSB,
		uint8_t reg_LSB
);
