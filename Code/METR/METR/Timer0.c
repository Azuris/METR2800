/*
 * Timer0.c
 *
 * Created: 8/10/2014 10:58:40 AM
 *  Author: s4292369
 */
#ifdef AVR
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
 /** Set up Timer0 on the Atmega328P to enable compare output mode on A
 for Fast PWM with clock prescaler 1024**/
void timer0_init(void) {

	DDRD |= (1 << DDD6);
	TCNT0 = 0;
	TCCR0A |= (1 << COM0A1)|(1<<WGM00);
	TCCR0B |= (1 << CS02);//(1<<CS00);(1<<WGM01)|

	OCR0A = 128; //Max = 255

	return;
}