#include "Inf_joystick.h"

uint16_t adc_buff[4];

void Inf_Joystick_Init(void)
{
    /* 1. Ð£×¼ADC */
    HAL_ADCEx_Calibration_Start(&hadc1);

    /* 2. Æô¶¯ADC */
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_buff, 4);
}

void Inf_Joystick_Scan(Remote_Struct *remote)
{
    remote->THR = adc_buff[0];
    remote->YAW = adc_buff[1];
    remote->PIT = adc_buff[2];
    remote->ROL = adc_buff[3];
}
