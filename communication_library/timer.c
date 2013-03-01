#include <avr/io.h>
#include <avr/interrupt.h>
#include "system_config.h"

void timer_init(void) {
// prescaler = 1024
TCCR0B = (1 << CS02) | (1 << CS00);
OCR0A = 0x01;
TIMSK0 = (1 << OCIE0A);
TIFR0 = (1 << OCF0A);
TCNT0 = 0;
}

ISR (TIMER0_COMPA_vect) {
static int i = 0;
	if (i == 0) {
	PORTC = 0xF0;
	i = 1;
	}
	else {
	PORTC = 0x00;
	i = 0;
	}
}

