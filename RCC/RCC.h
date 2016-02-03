/**
  ******************************************************************************
  * @file    RCC.h
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

void RCC_GPIO_Initialise(GPIO_TypeDef* GPIOx);
void RCC_GPIO_DeInitialise(I2C_TypeDef* I2Cx);
void RCC_I2C_Initialise(I2C_TypeDef* I2Cx);
void RCC_I2C_DeInitialise(I2C_TypeDef* I2Cx);
