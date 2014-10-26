#include "Mode_Operation.h"

/* Runs a single ball drop on a stationary target.*/
void Mode_One() {
	uint16_t adVolts;
	uint16_t adOne;
	
	timer0_init(140);
	watch_delay(3000000);
	adOne = ADC_Run(0x00);
	while(1) {
		if ((adOne < 420)) {
			timer0_off();
			OCR1B = 350; //(push)
			watch_delay(1500000);
			OCR1B = 200; //(pull)
			OCR1A = 197;
			watch_delay(2000000);
			timer0_init(100);
			timer0_off();
			watch_delay(1500000);
			timer0_init(140);
			while (1) {
				adVolts = ADC_Run(0x03);
				if (adVolts < 322) {
					timer0_off();
					OCR1A = 650;
					return;
				}
			}
		}
		adOne = ADC_Run(0x00);
	}
	return;
}

/* Runs a single ball drop on a slow moving target.*/
void Mode_Two() {
	uint16_t adVolts;
	uint16_t adOne;
	
	timer0_init(140);
	watch_delay(12000000);
	timer0_off();
	watch_delay(3000000);
	while(1) {
		adOne = ADC_Run(0x00);
		if ((adOne < 480)) {
			timer0_off();
			OCR1B = 350; //(push)
			watch_delay(1500000);
			OCR1B = 200; //(pull)
			watch_delay(2000000);
			OCR1A = 210;
			watch_delay(2000000);
			timer0_init(70);
			timer0_off();
			watch_delay(1500000);
			timer0_init(140);
			while (1) {
				adVolts = ADC_Run(0x03);
				if (adVolts < 322) {
					timer0_off();
					OCR1A = 650;
					return;
				}
			}
		}
	}
}