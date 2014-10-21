/*
 * Timer1.c
 *
 * Created: 25/09/2014 11:31:47 AM
 *  Author: s4292369
 */ 
#include "Timer1.h"

//FAST PWM (1<<WGM13) (1<<WGM12) (1<<WGM11)
//Phase/Freq (1<<WGM13)
//Pre 8 (1<<CS11)
//Pre 64 (1<<CS11) (1<<CS10)
/** Set up Timer1 on the Atmega328P to enable Compare Output mode on A and B 
for Fast PWM mode with clock prescaler 64 to 1 for 1 Mhz and initialise the duty cycle to 
5%**/
void timer1_init(void) {
	
	DDRB |= (1 << DDB1)|(1 << DDB2);
	ICR1 = 39999;// for 16Mhz;

	TCNT1 = 0;
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1)|(1<<WGM12)|(1<<WGM11);
	TCCR1B |= (1 << WGM13)||(1<<CS11);

	
	OCR1A = 1300; //Release
	OCR1B = 4799; //Fan Rotate
	return;
}

/** 3000000 on 16Mhz CPU is approx. 1.1s **/
void watch_delay(uint32_t length) {
	uint32_t ticks;
	ticks = length;
	while(ticks) {
		ticks--;
	}
	return;
}