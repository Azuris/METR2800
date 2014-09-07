/*
 * METR.c
 *
 * Created: 4/09/2014 8:30:46 PM
 *  Author: User
 */ 


#include <avr/io.h>

int main(void) {
	uint8_t test;
	
	DDRD = 0x00;
	while(1) {
		if (PIND ^= 0x04) {
			//run stationary single drop
			DDRD |= (1 << DDD6);
			TCCR0A |= 0b10000001;
			TCCR0B |= 0b00001010;
			//require timing for angles
			// freq = (8MHz or 16Mhz)/8*510
			return 0;
		}
		if (PIND ^= 0x05) {
			//run moving single drop
			return 0;
		}
		if (PIND ^= 0x06) {
			//run ballistic run
			return 0;
		}
		if (PIND ^= 0x07) {
			//run moving multiple drop
			return 0;
		}
	}	
}