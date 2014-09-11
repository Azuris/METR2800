#include <avr/io.h>
#include "AD_Convert.h"

void InitADC(void)
{
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
}

uint16_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0x07;
	ADMUX|=ch;         
	
	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete
	while(!(ADCSRA & (1<<ADIF)));

	//Clear ADIF by writing one to it
	ADCSRA|=(1<<ADIF);

	return(ADC);
}

uint16_t ADC_Run(uint8_t channel)
{
	uint16_t adc_result;

	//Initialize ADC
	InitADC();

	adc_result=ReadADC(channel);           // Read Analog value from channel-4
	
	return adc_result;
}
