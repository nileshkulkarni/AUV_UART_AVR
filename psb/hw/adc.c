#include <avr/interrupt.h>
#include <avr/io.h>
#include "hw/hw.h"

volatile uint16_t adcData;
volatile bool adcReceivedData;

void adcInit(void) {
/* enable ADC and interrupt */
ADCSRA = (1 << ADEN) | (1 << ADIE);
/* voltage source is AVCC */
ADMUX = (1 << REFS0);

adcReceivedData = TRUE;
}

void adcStartSampling(void) {
/* start sampling */
ADCSRA |= (1 << ADSC);
	while(ADCSRA & (1 << ADSC)) {}
adcData = 0x0000 & ADCL;
adcData += ((0x00FF & ADCH)<<8);
adcReceivedData = TRUE;
}
