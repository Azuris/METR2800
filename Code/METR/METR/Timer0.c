#include "Timer0.h"

/* Set up Timer 0 on the Atmega328P to enable compare output mode on A
for Fast PWM with clock prescalar 1024 (16Mhz) and duty cycle fan speed, fan_speed.*/
void timer0_init(uint8_t fan_speed) {

	DDRD |= (1 << DDD6);
	TCNT0 = 0;
	TCCR0A |= (1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
	TCCR0B |= (1<<CS02)|(1<<CS00); //61.3Hz

	OCR0A = fan_speed; 
	return;
}

/* Disconnects Timer 0 compare output mode A from Pin B, to not allow
any PWM signals to travel to the fan.*/
void timer0_off(void) {
	OCR0A = 0;
	TCCR0A &= 0x00;
	TCCR0B &= 0x00;
	return;
}