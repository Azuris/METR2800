/*
 * AD_Convert.h
 *
 * Created: 11/09/2014 2:53:08 PM
 *  Author: s4292369
 */ 
#ifdef AVR
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#endif


void InitADC(void);

uint16_t ReadADC(uint8_t ch);

uint16_t ReadADC(uint8_t ch);

uint16_t ADC_Run(uint8_t channel);