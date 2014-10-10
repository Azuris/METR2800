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

int main(void) {

	DDRD = 0x00;
	DDRD ^= (1 << DDD7);
	DDRB = 0x00;
	timer0_init();
	timer1_init();
	test_run();
	while(1) {
		if (PIND & (1 << PIND2)) {
			
			//watch_delay(6000000);
			
			//Send signal to the fan to receive power
			
			if (PIND & (1 << PIND1)) {
				//Mode_Two();
				PORTD ^= (1<<PORTD7);
				watch_delay(15000000);
			}
			
			if (PIND & (1 << PIND0)) {
				//Mode_Three();
			}
			
			if (PIND & ((1 << PIND1)|(1 << PIND0))) {
				//Mode_Four();
			}
			/**if (PIND & 0x04) {
				PORTD = PORTD & (0 << PORTD7);
			}**/
			
			//Mode_One();
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
	while(1) {
		switches = PIND;
		if (switches & 0x04) {
			PORTB ^= 0x04;
		}
		//OCR1A = 1300;
		
		/**for (int i=300;i<3000;i+=50){
			OCR1A = i;
			watch_delay(150000);
		}**/
		OCR1A = 300;		
		OCR1B = 789;
		watch_delay(6000000);
		//OCR1A = 2000;
		OCR1A = 3200;
		OCR1B = 3525;
		watch_delay(6000000);
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
