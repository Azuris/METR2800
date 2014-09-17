/*
 * METR.c
 *
 * Created: 4/09/2014 8:30:46 PM
 *  Author: User
 */ 

#ifndef F_CPU
#define F_CPU 1600000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "AD_Convert.h"
#include "Mode_Operation.h"

int main(void) {
	uint8_t switches;
	int test;
	
	test = 0;
	DDRD = 0x00;
	DDRC = 0x00;
	ICR1 = 4999;
	
	DDRB |= (1 << DDB1) | (1 << DDB4);
	PORTB = PORTB & (1 << DDB4);
	TCNT1 = 0;
	TCCR1A |= (1 << COM1A1); //Enable compare output A in timer1
	
	//Set PWM mode Frequency and Phase Correct with prescalar 8
	TCCR1B |= (1 << WGM13)|(1 << CS11); 
	
	TIFR1 = (0 << ICF1) | (0 << OCF1B) | (0 << OCF1A) | (0 << TOV1);
				
	OCR1A = 2500; //25% duty cycle
	while(test <30000) {
		test = test + 1;
	}
	TCCR1A |= (1 << COM1A1); 
	return 1;
	while(1) {
		switches = PIND;
		if (switches & 0x04) {
			
			//Send signal to the fan to receive power
			DDRD |= (1 << DDD7); 
			PORTD = (1 << DDD7);
			
			Mode_One(switches);
			
			Mode_Two(switches);
			
			Mode_Three(switches);
			
			Mode_Four(switches);
		}
	}	
}