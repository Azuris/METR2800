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
void fan_run(void);

int main(void) {

	DDRD = 0x00;
	DDRB = 0x00;
	//ADC_Throw();
	timer0_init(); //move to mode operation part for final
	timer1_init();
	//fan_run();
	test_run();
	while(1) {
		if (PIND & (1 << PIND2)) {
			
			//watch_delay(6000000);
			
			//timer0_init();
			
			if (PIND == 0x04) {
				Mode_One();
			}
			if (PIND == 0x05) {
				Mode_Two();
			}
			if (PIND == 0x06) {
				Mode_Three();
			}
			if (PIND == 0x07) {
				Mode_Four();
			}
		}
	}		
}

void test_run(void) {
	uint8_t switches;
	uint32_t i;
	uint8_t side;
	while(1) {
		//OCR1A = 1300;
		
		for (int i=900;i<2900;i+=10){
			OCR1A = i;
			watch_delay(94000);
		}
		//OCR1A = 1200;
		////OCR1A = 300;		
		//OCR1B = 1054;
		//watch_delay(200000);
		////OCR1A = 2000;
		//OCR1A = 790;
		////OCR1A = 3200;
		//OCR1B = 1020;
		//watch_delay(200000);
		/**if (i > 800000) {
			side ^= 1;
			PORTD ^= (1 << DDD7);
			i = 0;
		}
		if (side == 0) {
			OCR1A = 1300;//320;//backward
			OCR1B = 789;//197;
			OCR0A = 255;
		}
		if (side == 1) {
			OCR1A = 2000;//500;//forward
			OCR1B = 3525;//541;
		}
		i++;**/
	}
}

void fan_run(void) {
	OCR0A = 191;
	watch_delay(3000000);
	OCR0A = 0;
}