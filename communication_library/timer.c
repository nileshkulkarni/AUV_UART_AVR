#include <avr/io.h>
#include <avr/interrupt.h>
#include "system_config.h"

#define MOTION_CONRTROLLER_OCR (FOSC/MOTION_CONTROLLER_FREQ/1024)

void timer_init(void) {
// prescaler = 1024
TCCR1B = (1 << CS02) | (1 << CS00);
/*
OCR1AH = 0xFF00 & MOTION_CONRTROLLER_OCR;
OCR1AL = 0x00FF & MOTION_CONRTROLLER_OCR;
*/
OCR1AH = (MOTION_CONRTROLLER_OCR & 0xFF00) >> 8;
OCR1AL = MOTION_CONRTROLLER_OCR & 0x00FF;
TIMSK1 = (1 << OCIE1A);
TIFR1 = (1 << OCF1A);
TCNT1 = 0;
}

ISR (TIMER1_COMPA_vect) {

TCNT1 = 0;
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

