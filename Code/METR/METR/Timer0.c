/*
 * Timer0.c
 *
 * Created: 8/10/2014 10:58:40 AM
 *  Author: s4292369
 */
#include "Timer0.h"
 /** Set up Timer0 on the Atmega328P to enable compare output mode on A
 for Fast PWM with clock prescaler 1024 (16Mhz)  64 (1MHz)**/
void timer0_init(uint8_t fan_speed) {

	DDRD |= (1 << DDD6);
	TCNT0 = 0;
	TCCR0A |= (1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
	TCCR0B |= (1<<CS02)|(1<<CS00); //61.3Hz

	OCR0A = fan_speed; //75% voltage Max = 255 

	return;
}

void timer0_off(void) {
	OCR0A = 0;
	TCCR0A &= 0x00;
	TCCR0B &= 0x00;
	return;
}