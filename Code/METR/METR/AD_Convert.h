#include <avr/io.h>

/* Initialises the Analogue Digital converter registers*/
void InitADC(void);

/* Runs the Analogue Digital converter on the Atmega328P for
single conversion*/
uint16_t ReadADC(uint8_t ch);

/* Runs the Analogue Digital converter from a
Channels between ADC0-3 [0x00, 0x01, 0x02, 0x03]
0x02 forward beacon, 0x03 backward beacon respectively 
and returns the converted value*/
uint16_t ADC_Run(uint8_t channel);

/* Runs the very first Analogue Digital conversion to stabilise
the Analogue Digital converter, with the returned value ignored,
as suggested by the datasheet. */
void ADC_Throw(void);