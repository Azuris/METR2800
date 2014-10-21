/*
 * Mode_Operation.c
 *
 * Created: 11/09/2014 4:34:51 PM
 *  Author: s4292369
 */ 

#include "Timer1.h"
#include "Timer0.h"
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
	uint16_t adVolts;
	uint16_t adOne;
	uint16_t adTwo;
	uint8_t side;
	
	side = 0; //0 is forward direction
	timer0_init();
	while(1) {
		if (side == 0) {
			adVolts = ADC_Run(0x02);
		} else {
			adVolts = ADC_Run(0x03);
		}
		if (adVolts < 5) {
			OCR0A = 5;
			if (side == 0) {
				OCR1B = 1020;	
			} else {
				OCR1B = 1050;
			}
			watch_delay(3000000);
			side ^= 1;
		} 
		adOne = ADC_Run(0x00);
		adTwo = ADC_Run(0x01);
		//ad's below 5 (0.02mV) either side of the beacons
		if (adOne < 5 && adTwo < 5) {
			OCR0A = 5;
			OCR1A = 0; //(push)
			watch_delay(3000000);
			OCR1A = 0; //(pull)
			if (side == 0) {
				OCR1B = 1020;
				watch_delay(3000000);
			}
			OCR0A = 171;
			while (1) {
				adVolts = ADC_Run(0x02);
				if (adVolts < 5) {
					OCR0A = 5;
					break;		
				}
			}
		}
		
		break;
	}
	return;
}

void Mode_Four() {
	return;
}