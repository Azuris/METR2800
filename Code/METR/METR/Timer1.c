#include "Timer1.h"

/* Set up Timer1 on the Atmega328P to enable Compare Output mode on A and B 
for Fast PWM mode with clock prescalar 64 and initialise the duty cycles for 
each servo initial position.*/
void timer1_init(void) {	
	DDRB |= (1 << DDB1)|(1 << DDB2);
	ICR1 = 4999;

	TCNT1 = 0;
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1)|(1<<WGM11);
	TCCR1B |= (1 << WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);

	OCR1A = 650; 
	OCR1B = 200; 
	return;
}

/* Pauses the program by the number of clock cycles specified. 
(3000000 on 16Mhz CPU is approx. 1.1s) */
void watch_delay(uint32_t length) {
	uint32_t ticks;
	ticks = length;
	while(ticks) {
		ticks--;
	}
	return;
}