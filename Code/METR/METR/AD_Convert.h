/*
 * AD_Convert.h
 *
 * Created: 11/09/2014 2:53:08 PM
 *  Author: s4292369
 */ 
#ifdef AVR
#include <avr/io.h>
#include <stdint.h>
#endif


void InitADC(void);

uint16_t ReadADC(uint8_t ch);

uint16_t ReadADC(uint8_t ch);

/** Channels between ADC0-3 [0x00, 0x01, 0x02, 0x03]
0x02 forward beacon, 0x03 backward beacon
respectively **/
uint16_t ADC_Run(uint8_t channel);

void ADC_Throw(void);