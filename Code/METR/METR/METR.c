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
#include "Timer1.h"

int main(void) {
	uint8_t switches;
	int test;
	
	DDRD = 0x00;
	DDRB = 0xFF;
	DDRD |= (1 << DDD7); 
	PORTD = (1 << DDD7);
	timer_init();
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