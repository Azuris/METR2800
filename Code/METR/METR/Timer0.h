#ifdef AVR
#include <avr/io.h>
#endif

/* Initialises Timer 0 on the Atmega328P, for the fan 
duty cycle. */
void timer0_init(uint8_t fan_speed);

/* Disconnects Timer 0 on the Atmega328P, from the PinB
 to turn off the fan.*/
void timer0_off(void);