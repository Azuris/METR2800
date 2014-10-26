#ifdef AVR
#include <avr/io.h>
#endif

/* Intialises Timer 1 on the Atmega328P for Fast PWM output compare mode on A and B.
Sets the intial positions for the servos.*/
void timer1_init(void);

/* */
void watch_delay(uint32_t length);