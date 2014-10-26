#include <avr/io.h>

/* Intialises Timer 1 on the Atmega328P for Fast PWM output compare mode on A and B.
Sets the intial positions for the servos.*/
void timer1_init(void);

/* Pauses the program for the number of clock cycles specified.*/
void watch_delay(uint32_t length);