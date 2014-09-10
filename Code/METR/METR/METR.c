/*
 * METR.c
 *
 * Created: 4/09/2014 8:30:46 PM
 *  Author: User
 */ 

#ifndef F_CPU
#define F_CPU 2000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	uint8_t test;
	
	ICR1 = 3125;
	DDRD = 0x00;
	DDRB |= (1 << DDB1);
	while(1) {
		PORTB ^= 0x02;
		_delay_ms(200);
	}
	TCNT1 = 0;
	TCCR1A |= (1 << COM1A1);
	TCCR1B |= (1 << WGM13)|(1 << CS11)|(1 << CS10);
				
	OCR1A = 280;
	
	return 1;
	while(1) {
		if (PIND == 0x04) {
			//run stationary single drop
			DDRD |= (1 << DDD6);
			TCCR0A |= 0b10000001;
			TCCR0B |= 0b00000101;
			
			OCR0A = 0x0A;
			_delay_ms(100);
			OCR0A = 0x38;
			_delay_ms(100);
			//require timing for angles
			// freq = (8MHz or 16Mhz)/8*510
			return 0;
		}
		if (PIND == 0x05) {
			//run moving single drop
			return 0;
		}
		if (PIND == 0x06) {
			//run ballistic run
			return 0;
		}
		if (PIND == 0x07) {
			//run moving multiple drop
			return 0;
		}
	}	
}