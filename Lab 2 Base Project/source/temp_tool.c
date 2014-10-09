#include "temp_tool.h"

void adcInitialize () {

	ADC_InitTypeDef adc_init_s;
	ADC_CommonInitTypeDef adc_common_init_s;


		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 		//Clock Gating.  Enables the ADC interface clock	
	
																	//Configure the ADC Prescaler, conversion resolution and data  alignment using the ADC_Init() function.
	adc_common_init_s.v = ADC_Mode_Independent;
	adc_common_init_s.ADC_Prescaler = ADC_Prescaler_Div2;
	adc_common_init_s.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	adc_common_init_s.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
		ADC_CommonInit(&adc_common_init_s); 					//Initialization
	
	adc_init_s.ADC_Resolution = ADC_Resolution_12b;
	adc_init_s.ADC_ScanConvMode = DISABLE;
	adc_init_s.ADC_ContinuousConvMode = DISABLE;
	adc_init_s.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	adc_init_s.ADC_DataAlign = ADC_DataAlign_Right;
	adc_init_s.ADC_NbrOfConversion = 1;
		ADC_Init(ADC1, &adc_init_s); 								//Initialization

		ADC_Cmd(ADC1, ENABLE); 										//Enable ADC
}

void sensorInitialize () {

		ADC_TempSensorVrefintCmd(ENABLE); 							//Enable temperature sensor
		ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_480Cycles);
}


void getVoltage () {

		ADC_SoftwareStartConv(ADC1); 								//Starting Conversion, waiting for it to finish, clearing the flag, reading the result
		while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); 		//Could be through interrupts (Later)
		ADC_ClearFlag (ADC1, ADC_FLAG_EOC); 						//EOC means End Of Conversion
		ADC_GetConversionValue(ADC1); 								// Result available in ADC1->DR
}

float getCelcius (float volts) {
		return (((volts/1000) - 0.0076f)/0.0025f) +25;

}
