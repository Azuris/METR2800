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

#include <avr/io.h>
#include <avr/interrupt.h>

void test_run(void);
void self_delay(void);

int main(void) {
	uint8_t switches;
	uint32_t test;
	uint8_t side;
	
	test = 0;
	side = 0;
	DDRD = 0x00;
	DDRB = 0x00;
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
	uint32_t i;
	uint8_t side;
	
	i = 0;
	side = 0;
	DDRD = (1 << DDD7);
	//PORTD ^= (1 << DDD6);
	while(1) {
		switches = PIND;
		if (switches & 0x04) {
			PORTB ^= 0x04;
		}
		if (i > 800000) {
			side ^= 1;
			PORTD ^= (1 << DDD7);
			i = 0;
		}
		if (side == 0) {
			OCR1A = 320;//backward
			OCR1B = 197;
			OCR0A = 255;
		}
		if (side == 1) {
			OCR1A = 500;//forward
			OCR1B = 541;
		}
		i++;
		/**OCR1A = 550;
		OCR1B = 400;
		OCR0A = 255;
		delay(1600000);**/
	}
}

void self_delay(void) {
	int i;
	i = 0;
	while(i < 5) {
		i++;
	}
	return;
}
