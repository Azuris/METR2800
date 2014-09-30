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

#include <avr/io.h>
#include <util/delay.h>
#include "AD_Convert.h"
#include "Mode_Operation.h"
#include "Timer1.h"

int main(void) {
	uint8_t switches;
	int test;
	int side;
	
	test = 0;
	side = 0;
	DDRD = 0x00;
	DDRB = 0xFF;
	//DDRD |= (1 << DDD7); 
	//PORTD = (1 << DDD7);
	timer_init();
	while(1) {
		switches = PIND;
		if (switches & 0x04) {
			PORTB ^= 0x04;
		} /**else {
			PORTB = 0x00;
		}**/
		test += 1;
		if (test == 30000) {
			side ^= 1;
			test = 0;
		}
		/**if (side == 0) {
			OCR1A = 500;
		}
		if (side == 1) {
			OCR1A = 3000;
		}**/
	}
	while(1) {
		switches = PIND;
		//if (switches & 0x04) {
			
			//Send signal to the fan to receive power
			//DDRD |= (1 << DDD7); 
			//PORTD ^= (1 << DDD7);
			
			Mode_One(switches);
			
			Mode_Two(switches);
			
			Mode_Three(switches);
			
			Mode_Four(switches);

	}	
}