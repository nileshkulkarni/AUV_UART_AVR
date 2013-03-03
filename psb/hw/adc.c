#include <avr/interrupt.h>
#include <avr/io.h>
#include "hw/hw.h"


void adcInit(void) {
/* enable ADC and interrupt */
//ADCSRA = (1 << ADEN) | (1 << ADIE);
ADCSRA = (1 << ADEN);
/* voltage source is AVCC */
ADMUX = (1 << REFS0);
}

uint16_t adcSample(void) {
/* start sampling */
ADCSRA |= (1 << ADSC);
	while(!(ADCSRA & (1 << ADIF))) {}
ADCSRA |= (1 << ADIF);
uint16_t adcData;
adcData = ADCL;
adcData = adcData | ((0x00FF & ADCH)<<8);
return adcData;
}