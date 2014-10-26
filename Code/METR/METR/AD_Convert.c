#include "AD_Convert.h"

/* Initialises the Analogue Digital Converter on the Atmega238P with the 
following conditions*/
void InitADC(void) {
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//Prescalar div factor =128
}

/*Read the given AD Converter channel that is between Ch1-4, and waits
for the Conversion complete flag before returning the value.*/
uint16_t ReadADC(uint8_t ch) {
	if (ch > 0x04) {
		return ADC;
	}
	ADMUX |= ch;        
	
	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	ADCSRA|=(1<<ADIF);

	return(ADC);
}
/* Runs the Analogue Digital converter for a single conversion by 
initialising the registers (to clear any possible corruption 
in the registers) and returns the outputted value by the converter.*/
uint16_t ADC_Run(uint8_t channel) {
	uint16_t adc_result;

	//Initialize ADC
	InitADC();

	adc_result=ReadADC(channel);         // Read Analog value from channel-4
	
	return adc_result;
}

/* This function runs the AD converter on the Atmega328P for the first time, 
to allow it to stabilise and set up for the AD converter (as suggested by the data 
sheet), and ignores the returned value */
void ADC_Throw(void) {
	//InitADC();
	ADC_Run(0x00);
	return;
}
