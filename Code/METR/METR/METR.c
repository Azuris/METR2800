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
#include <stdio.h>
#include <stdint.h>
#include "AD_Convert.h"
#include "Mode_Operation.h"
#include "serialio.h"
#include "Timer1.h"
#include "Timer0.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void test_run(void);
void fan_run(void);

int main(void) {

	DDRD = 0x00;
	DDRC = 0x00;
	DDRB = 0x00;
	//ADC_Throw();
	//timer0_init(191); //move to mode operation part for final
	timer1_init();
	//fan_run();
	//test_run();
	init_serial_stdio(19200, 0);
	clear_serial_input_buffer();
	sei();
	while(1) {
		if (PIND & (1 << PIND0)) {
			
			//watch_delay(6000000);
			
			//timer0_init();
			
			if (PIND == 0x01) {
				//Mode_One();
			}
			if (PIND == 0x03) {
				Mode_Two();
	
			}
			if (PIND == 0x05) {
				//Mode_Three();
			}
			if (PIND == 0x07) {
				//Mode_Four();
			}
		}
		printf("fssf\n");
	}		
}

void test_run(void) {
	uint8_t switches;
	uint32_t i;
	uint8_t side;
	i = 0;
	while(1) {
		//OCR1A = 1300;
		
		//for (int i=170;i<649;i+=10){
			////OCR1A = i;
			//OCR1B = i;
			//watch_delay(3000000);
		//}
		OCR0A = 100;
		OCR1B = 197;	
		OCR1A = 200;
		watch_delay(3000000);
		OCR1B = 650;
		OCR1A = 500;
		OCR0A = 0;
		watch_delay(3000000);
		if (i > 2) {
			TCCR0A &= 0x00;
			TCCR0B &= 0x00;
		}
		i++;
		/**if (side == 0) {
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
	uint8_t side;
	side = 0;
	while (1) {
		timer0_init(191);
		watch_delay(9000000);
		timer0_off();
		if (side == 0) {
			OCR1A = 210;
		} else {
			OCR1A = 650;
		}
		watch_delay(2000000);
		side ^= 1;
	}
	
}