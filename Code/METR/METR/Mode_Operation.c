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

void Mode_One() {
	uint16_t adVolts;
	uint16_t adOne;
	
	timer0_init(140);
	watch_delay(3000000);
	adOne = ADC_Run(0x00);
	while(1) {
		if ((adOne < 420)) {
			timer0_off();
			OCR1B = 350; //(push)
			watch_delay(1500000);
			OCR1B = 200; //(pull)
			OCR1A = 197;
			watch_delay(2000000);
			timer0_init(100);
			timer0_off();
			watch_delay(1500000);
			timer0_init(140);
			while (1) {
				adVolts = ADC_Run(0x03);
				if (adVolts < 322) {
					timer0_off();
					OCR1A = 650;
					return;
				}
			}
		}
		adOne = ADC_Run(0x00);
	}
	return;
}

void Mode_Two() {
	uint16_t adVolts;
	uint16_t adOne;
	
	timer0_init(140);
	watch_delay(12000000);
	timer0_off();
	watch_delay(3000000);
	while(1) {
		adOne = ADC_Run(0x00);
		if ((adOne < 480)) {
			timer0_off();
			OCR1B = 350; //(push)
			watch_delay(1500000);
			OCR1B = 200; //(pull)
			watch_delay(2000000);
			OCR1A = 210;
			watch_delay(2000000);
			timer0_init(70);
			timer0_off();
			watch_delay(1500000);
			timer0_init(140);
			while (1) {
				adVolts = ADC_Run(0x03);
				if (adVolts < 322) {
					timer0_off();
					OCR1A = 650;
					return;
				}
			}
		}
	}
}
//2.3 = 471
void Mode_Three() {
	uint16_t adVolts;
	uint16_t adOne;
	uint16_t adTwo;
	uint8_t side;
	
	side = 0; //0 is forward direction
	timer0_init(110);
	while(1) {
		if (side == 0) {
			adVolts = ADC_Run(0x02);
		} else {
			adVolts = ADC_Run(0x03);
		}
		if (adVolts < 300) {
			timer0_off();
			if (side == 0) {
				OCR1A = 197;	
			} else {
				OCR1A = 641;
			}
			watch_delay(2000000);
			side ^= 1;
			timer0_init(110);
		} 
		adOne = ADC_Run(0x00);
		adTwo = ADC_Run(0x01);
		//ad's below 5 (0.02mV) either side of the beacons
		if (adOne < 493 && adTwo < 493) {
			timer0_off();
			OCR1B = 350; //(push)
			watch_delay(1500000);
			OCR1B = 200; //(pull)
			if (side == 0) {
				OCR1A = 197;
				watch_delay(2000000);
			}
			timer0_init(171);
			while (1) {
				adVolts = ADC_Run(0x02);
				if (adVolts < 350) {
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
				timer0_init(110);
				side ^= 1;
			} else {
				OCR0A = 110;
			}	
		}
		if (adTwo > adOne) {
			if (side == 1) {
				timer0_off();
				OCR1A = 650;
				timer0_init(110);
				side ^= 1;
			} else {
				OCR0A = 110;
			}
		}		
	}
}

void Mode_Four() {
	return;
}