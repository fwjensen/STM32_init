#include "ION_ADC.h"
#include "ION_GPIO.h"


void ADC_Initialise(ADC_TypeDef * ADCx)
{
    ADC_InitTypeDef ADC_InitStruct;
    
    ADC_RCC_Initialise(ADCx);
    
    ADC_GPIO_Initialise(ADCx);
    
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStruct.ADC_NbrOfConversion = 1;
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADCx, &ADC_InitStruct);
}

void ADC_RCC_Initialise(ADC_TypeDef * ADCx)
{
    if(ADCx == ADC1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    }
    else if(ADCx == ADC2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
    }
    else if(ADCx == ADC3)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    }
    else
    {
        while(1);
    }
}

void ADC_GPIO_Initialise(ADC_TypeDef * ADCx)
{
    if(ADCx == ADC1)
    {
        GPIO_Initialise(GPIOA, GPIO_Mode_AF, GPIO_OType_OD, GPIO_Pin_10, GPIO_PuPd_NOPULL,GPIO_Speed_50MHz);
    }
    else if(ADCx == ADC2)
    {
        GPIO_Initialise(GPIOA, GPIO_Mode_AF, GPIO_OType_OD, GPIO_Pin_10, GPIO_PuPd_NOPULL,GPIO_Speed_50MHz);
    }
    else if(ADCx == ADC3)
    {
        GPIO_Initialise(GPIOA, GPIO_Mode_AF, GPIO_OType_OD, GPIO_Pin_10, GPIO_PuPd_NOPULL,GPIO_Speed_50MHz);
    }
    else
    {
        while(1);
    }
}
