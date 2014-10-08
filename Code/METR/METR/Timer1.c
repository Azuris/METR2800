/*
 * Timer1.c
 *
 * Created: 25/09/2014 11:31:47 AM
 *  Author: s4292369
 */ 
#ifdef AVR
#include <avr/io.h>
#include <avr/interrupt.h>
#endif
//FAST PWM (1<<WGM13) (1<<WGM12) (1<<WGM11)
//Phase/Freq (1<<WGM13)
//Pre 8 (1<<CS11)
//Pre 64 (1<<CS11) (1<<CS10)
/** Set up Timer1 on the Atmega328P to enable Compare Output mode on A and B 
for Fast PWM mode with clock prescaler 64  and initialise the duty cycle to 
5%**/
void timer1_init(void) {
	ICR1 = 39999;//4999;

	TCNT1 = 0;
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1)|(1<<WGM11); 
	TCCR1B |= (1 << WGM13)|(1 << WGM12)|(1 << CS11);//|(1<<CS10);
	
	//OCR1A = 0;
	//OCR1B = 0;
	return;
}