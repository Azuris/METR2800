/*
 * Mode_Operation.c
 *
 * Created: 11/09/2014 4:34:51 PM
 *  Author: s4292369
 */ 

#include "Timer1.h"
#include "AD_Convert.h"

#include <avr/io.h>

//height 2m ADC 10millivolts 10cm ADC 20millivolts
//max ADC around 2.3V
void Mode_One() {
	uint16_t adVolts;

	//run stationary single drop
		while(1) {
			adVolts = ADC_Run(0x00);
			// 1000 ADC
			if (adVolts < 205) {
				OCR0A = 0;	//send signal to block fan from receiving power
				OCR1A = 2000;
				watch_delay(3000000);
				OCR1A = 1300;
				OCR1B = 789;
				watch_delay(3000000);
				OCR0A = 128;
			}
		}		
	return;
}

void Mode_Two() {
	uint16_t adVolts;
	
		while(1) {
			adVolts = ADC_Run(0x00);
			// 1000 ADC
			if (adVolts < 205) {
				OCR0A = 0;	//send signal to block fan from receiving power
				OCR1A = 2000;
				watch_delay(3000000);
				OCR1A = 1300;
				watch_delay(3000000);
				OCR1A = 2000;
				watch_delay(3000000);
				OCR1A = 1300;
				OCR1B = 789;
				watch_delay(3000000);
				OCR0A = 128;
			}
		}
	return;
}

void Mode_Three() {
	ADC_Run(0x04);
	return;
}

void Mode_Four() {
	return;
}