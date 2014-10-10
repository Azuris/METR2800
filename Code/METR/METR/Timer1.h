/*
 * Timer1.h
 *
 * Created: 26/09/2014 11:28:14 AM
 *  Author: s4292369
 */ 
#ifdef AVR
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#endif

void timer1_init(void);

void watch_delay(uint32_t length);