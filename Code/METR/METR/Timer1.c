/*
 * Timer1.c
 *
 * Created: 25/09/2014 11:31:47 AM
 *  Author: s4292369
 */ 
#ifndef F_CPU
#define F_CPU 1600000UL
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//FAST PWM (1<<WGM13) (1<<WGM12) (1<<WGM11)
//Phase/Freq (1<<WGM13)
//Pre 8 (1<<CS11)
//Pre 64 (1<<CS11) (1<<CS10)
void timer_init(void) {
	ICR1 = 4999;

	//DDRB |= (1 << DDB1); //| (1 << DDB4);
	//PORTB = PORTB & (1 << DDB4);
	TCNT1 = 0;
	TCCR1A |= (1 << COM1A1)|(1<<WGM11); //Enable compare output A in timer1

	//Set PWM mode Frequency and Phase/FAST Correct with prescalar 64
	TCCR1B |= (1 << WGM13)|(1 << WGM12)|(1 << CS11)|(1<<CS10);

	TIFR1 = (0 << ICF1) | (0 << OCF1B) | (0 << OCF1A) | (0 << TOV1);

	OCR1A = 2500; //50% duty cycle

	return;
}