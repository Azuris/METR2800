/*
 * Timer1.c
 *
 * Created: 25/09/2014 11:31:47 AM
 *  Author: s4292369
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void timer_init(void) {
	ICR1 = 4999;

	DDRB |= (1 << DDB1) | (1 << DDB4);
	PORTB = PORTB & (1 << DDB4);
	TCNT1 = 0;
	TCCR1A |= (1 << COM1A1); //Enable compare output A in timer1

	//Set PWM mode Frequency and Phase Correct with prescalar 8
	TCCR1B |= (1 << WGM13)|(1 << CS11);

	TIFR1 = (0 << ICF1) | (0 << OCF1B) | (0 << OCF1A) | (0 << TOV1);

	OCR1A = 2500; //25% duty cycle

	TCCR1A |= (1 << COM1A1);
	return;
}