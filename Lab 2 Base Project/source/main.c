#include <stdio.h>
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_conf.h"
//#include "temp_tool.h"

static volatile uint16_t flag;
static volatile uint16_t tick_count;
static volatile uint16_t loop_count;

//============================================================================================================================================================================
//Temperature-related Functions
//============================================================================================================================================================================

void adcInitialize () {

	ADC_InitTypeDef adc_init_s;
	ADC_CommonInitTypeDef adc_common_init_s;


		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 		//Clock Gating.  Enables the ADC interface clock	
	
																	//Configure the ADC Prescaler, conversion resolution and data  alignment using the ADC_Init() function.
	adc_common_init_s.ADC_Mode = ADC_Mode_Independent;
	adc_common_init_s.ADC_Prescaler = ADC_Prescaler_Div2;
	adc_common_init_s.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	adc_common_init_s.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
		ADC_CommonInit(&adc_common_init_s); 						//Initialization
	
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
		ADC_GetConversionValue(ADC1); 								//Result available in ADC1->DR
}

float getCelcius (float volts) {
		return (((volts/1000) - 0.0076f)/0.0025f) +25;

}

//need to do a moving average
//want to have 'd' samples in the buffer
//when a new sample is added replace oldest sample in the buffer

struct movingAverage{
	int pointer;
	int size;
	float* list;
};

void initMovingAverage(struct movingAverage ma, int size){	//initialize the struct with a list size
	float theList[size];
	ma.pointer = 0;
	ma.size = size;
	ma.list = theList;
}
void initAverageValues(struct movingAverage ma){			//populate the moving average array
	for (int i = 0; i < ma.size;i++){
		getVoltage ();
		ma.list[i] = getCelcius(ADC1->DR);	
	}
}

void addSample(struct movingAverage ma, float sample){	//add a sample to the moving average
	ma.list[ma.pointer] = sample;
	ma.pointer = (ma.pointer + 1) %ma.size; //wrap around 
}

float getAverage (struct movingAverage ma){
	float average;
	for (int i = 0; i < ma.size;i++){
		average = average + ma.list[i];
	}
	average = average/ma.size;
	return average;
}



//============================================================================================================================================================================
//Main
//============================================================================================================================================================================

void SysTick_Handler(){
	
	flag = 1;
	
}

int main(){

	int volts = 0;
	float final_temperature = 0;

	flag = 0;
	//tick_count = 0;
	//loop_count = 0;

	// At 168MHz, this just a bit slower than 50Hz
	SysTick_Config(20 * SystemCoreClock / 1000);

	adcInitialize();
	sensorInitialize();


	
	while(1){

		if(flag) {

			flag = 0;
			printf("Temperature is %f\n", final_temperature);
		}

		getVoltage ();
		volts = ADC1->DR;
		final_temperature = getCelcius(volts);


	}
	
	return 0;
}