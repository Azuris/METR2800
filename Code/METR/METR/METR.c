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
#include <stdio.h>
#include "AD_Convert.h"
#include "Mode_Operation.h"
#include "serialio.h"
#include "Timer1.h"
#include "Timer0.h"

#include <avr/io.h>

void test_run(void);
void fan_run(void);
void test_run2(void);

int main(void) {

	DDRD = 0x00;
	DDRC = 0x00;
	DDRB = 0x00;
	ADC_Throw();
	timer1_init();
	//fan_run();
	//test_run();
	if (PIND & (1<<PIND0)) {
		Mode_One();	
	} else {
		Mode_Two();
	}
	return 1;
}

void test_run(void) {
	uint16_t adVolts;
	uint16_t adOne;
	uint8_t side;
	uint8_t multi;
	
	side = 0;
	multi = 0;
	
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
			timer0_init(80);
			timer0_off();
			watch_delay(1500000);
			timer0_init(140);
			while (1) {
				adVolts = ADC_Run(0x03);
				if (adVolts < 300) {
					timer0_off();
					OCR1A = 650;
					watch_delay(2000000);
					multi++;
					break;
				}
			}
		}
		adOne = ADC_Run(0x00);
	}
	return;
}

void fan_run(void) {
	uint8_t side;
	uint16_t adVolts;
	side = 0;
	timer0_init(121);
	while (1) {
		if (side == 0) {
			adVolts = ADC_Run(0x02);
			if (adVolts < 10) {
				timer0_off();
				OCR1A = 210;
				watch_delay(1700000);
				timer0_init(200);
				side ^= 1;
			}			
		} else {
			adVolts = ADC_Run(0x03);
			if (adVolts < 10) {
				timer0_off();
				OCR1A = 650;
				watch_delay(1700000);
				timer0_init(121);
				side ^= 1;
			}
		}
	}
	
}

void test_run2(void) {
	uint16_t adVolts;
	uint16_t adOne;
	
	timer0_init(140);
	watch_delay(12000000);
	timer0_off();
	watch_delay(3000000);
	while(1) {
		adOne = ADC_Run(0x00);
		//ad's below 5 (0.02mV) either side of the beacons
		if ((adOne < 480)){//  && (adTwo < 480)) {
			timer0_off();
			OCR1B = 350; //(push)
			watch_delay(1500000);
			OCR1B = 200; //(pull)
			watch_delay(2000000);
			OCR1A = 210;
			watch_delay(2000000);
			timer0_init(151);
			while (1) {
				adVolts = ADC_Run(0x03);
				if (adVolts < 320) {
					timer0_off();
					OCR1A = 650;
					return;
				}
			}
		}
	}
}