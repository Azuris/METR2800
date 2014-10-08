/*
 * Mode_Operation.c
 *
 * Created: 11/09/2014 4:34:51 PM
 *  Author: s4292369
 */ 
#ifndef F_CPU
#define F_CPU 1600000UL
#endif

#include <util/delay.h>
#include "AD_Convert.h"

#ifdef AVR
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

void Mode_One(uint8_t swiValue) {
	uint16_t adVolts;
	uint8_t value;
	
	value = swiValue & 0x03;
	//run stationary single drop
	if (value == 0x00) {
		adVolts = ADC_Run(0x00);
		// 1000 ADC
		if (adVolts < 205) {
			OCR0A = 0;	//send signal to block fan from receiving power
		} 
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