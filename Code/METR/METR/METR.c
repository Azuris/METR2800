/*
 * METR.c
 *
 * Created: 4/09/2014 8:30:46 PM
 *  Author: User
 */ 

/** FUSE settings for ATMEGA328
BODLEVEL = DISABLED
RSTDISBL = [ ]
DWEN = [ ]
SPIEN = [X]
WDTON = [ ]
EESAVE = [ ]
BOOTSZ = 2048W_3800
BOOTRST = [ ]
CKDIV8 = [ ]
CKOUT = [ ]
SUT_CKSEL = EXTFSXTAL_16KCK_14CK_65MS

EXTENDED = 0xFF (valid)
HIGH = 0xD9 (valid)
LOW = 0xF7 (valid)
**/
/** FUSE settings for ATMEGA328P
BODLEVEL = DISABLED
RSTDISBL = [ ]
DWEN = [ ]
SPIEN = [X]
WDTON = [ ]
EESAVE = [ ]
BOOTSZ = 2048W_3800
BOOTRST = [ ]
CKDIV8 = [ ]
CKOUT = [ ]
SUT_CKSEL = EXTFSXTAL_16KCK_14CK_65MS

EXTENDED = 0xFF (valid)
HIGH = 0xD9 (valid)
LOW = 0xF7 (valid)
**/     
#ifndef F_CPU
#define F_CPU 1600000UL
#endif
#include <util/delay.h>
#include <stdint.h>
#include "AD_Convert.h"
#include "Mode_Operation.h"
#include "Timer1.h"
#include "Timer0.h"

#ifdef AVR
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

void test_run(void);

int main(void) {
	uint8_t switches;
	uint32_t test;
	uint8_t side;
	
	test = 0;
	side = 0;
	DDRD = 0x00;
	DDRB = 0xFF;
	timer0_init();
	timer1_init();
	test_run();
	while(1) {
		switches = PIND;
		if (switches & 0x04) {
			
			//Send signal to the fan to receive power
			
			Mode_One(switches);
			
			Mode_Two(switches);
			
			Mode_Three(switches);
			
			Mode_Four(switches);
		}
	}		
}

void test_run(void) {
	uint8_t switches;
	uint8_t fcl;
	uint16_t inc;
	uint32_t test;
	uint8_t side;
	
	DDRD = (1 << DDD6)|(1 << DDD7);
	//PORTD ^= (1 << DDD6);
	test = 0;
	side = 0;
	inc = 550;
	fcl = 0;
	while(1) {
		switches = PIND;
		if (switches & 0x04) {
			PORTB ^= 0x04;
		}
		test = test + 1;
		if (test > 800000) {
			PORTD ^= (1 << DDD7);
			fcl += 1;
			side ^= 1;
			test = 0;
		}
		if (side == 0) {
			OCR1A = 5261;//380
			OCR1B = 6665;
			OCR0A = 255;
		}
		if (side == 1) {
			OCR1A = 3636;//550
			OCR1B = 6895;
			OCR0A = 255;
		}
		if (fcl > 2) {
			inc = inc - 50;
			fcl = 0;
		}	
	}
}
