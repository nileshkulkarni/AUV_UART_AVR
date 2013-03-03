#include <avr/io.h>
#include <avr/interrupt.h>
#include "hw.h"


extern volatile bool runController;

void timerInit(void) {
/* prescaler = 1024 */
REG_FREQ_TCCRB = (1 << REG_FREQ_CS2) | (1 << REG_FREQ_CS0);
REG_FREQ_OCRAH = (MOTION_CONTROLLER_OCR & 0xFF00) >> 8;
REG_FREQ_OCRAL = MOTION_CONTROLLER_OCR & 0x00FF;
/* enabling compare match interrupts */
REG_FREQ_TIMSK = (1 << REG_FREQ_OCIEA);
REG_FREQ_TIFR = (1 << REG_FREQ_OCFA);
/* begin timer */
REG_FREQ_TCNT = 0;
}

ISR (REG_FREQ_TIMER_COMPA_vect) {
/* simulating CTC mode by forcing TCNT1 = 0 */
REG_FREQ_TCNT = 0;
DDRC = 0xFF;
runController = TRUE;
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

