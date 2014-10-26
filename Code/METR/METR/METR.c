#include "AD_Convert.h"
#include "Mode_Operation.h"
#include "Timer1.h"
#include <avr/io.h>

int main(void) {

	DDRD = 0x00;
	DDRC = 0x00;
	DDRB = 0x00;
	ADC_Throw();
	timer1_init();
	if (PIND & (1<<PIND0)) {
		Mode_One();	
	} else {
		Mode_Two();
	}
	return 1;
}