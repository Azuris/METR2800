/*
 * Mode_Operation.c
 *
 * Created: 11/09/2014 4:34:51 PM
 *  Author: s4292369
 */ 
#ifndef F_CPU
#define F_CPU 1600000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "AD_Convert.h"

void Mode_One(uint8_t swiValue) {
	uint16_t adVolts;
	uint8_t value;
	
	value = swiValue & 0x03;
	//run stationary single drop
	if (value == 0x00) {
		adVolts = ADC_Run(0x00);
		// 1000 ADC
		if (adVolts > 0x384) {
			PORTD ^= 0x80;	//send signal to block fan from receiving power
		} 
		DDRD |= (1 << DDD6);
		TCCR0A |= 0b10000001;
		TCCR0B |= 0b00000101;
		
		OCR0A = 0x0A;
		_delay_ms(100);
		OCR0A = 0x38;
		_delay_ms(100);
		//require timing for angles
		// freq = (8MHz or 16Mhz)/8*510
		return;
	}
		
	return;
}

void Mode_Two(uint8_t swiValue) {
	return;
}

void Mode_Three(uint8_t swiValue) {
	return;
}

void Mode_Four(uint8_t swiValue) {
	return;
}