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
			adVolts = ADC_Run(0x02);
			// 1000 ADC
			if (adVolts < 200) {
				//timer0_off();
				timer0_init(200);
			}
		}
	return;
}
//2.3 = 471
void Mode_Three() {
	uint16_t adVolts;
	uint16_t adOne;
	uint16_t adTwo;
	uint8_t side;
	
	side = 0; //0 is forward direction
	timer0_init(191);
	while(1) {
		if (side == 0) {
			adVolts = ADC_Run(0x02);
		} else {
			adVolts = ADC_Run(0x03);
		}
		if (adVolts < 5) {
			timer0_off();
			if (side == 0) {
				OCR1A = 197;	
			} else {
				OCR1A = 641;
			}
			watch_delay(2000000);
			side ^= 1;
			timer0_init(150);
		} 
		adOne = ADC_Run(0x00);
		adTwo = ADC_Run(0x01);
		//ad's below 5 (0.02mV) either side of the beacons
		if (adOne < 5 && adTwo < 5) {
			timer0_off();
			OCR1B = 500; //(push)
			watch_delay(1500000);
			OCR1B = 200; //(pull)
			if (side == 0) {
				OCR1A = 197;
				watch_delay(2000000);
			}
			timer0_init(191);
			while (1) {
				adVolts = ADC_Run(0x02);
				if (adVolts < 5) {
					timer0_off();
					OCR1A = 650;
					watch_delay(2000000);
					return;		
				}
			}
		}
		if (adOne > adTwo) {
			if (side == 0) {
				timer0_off();
				OCR1A = 197;
				timer0_init(151);
				side ^= 1;
			} else {
				OCR0A = 151;
			}	
		}
		if (adTwo > adOne) {
			if (side == 1) {
				
			}
		}		
	}
}

void Mode_Four() {
	return;
}