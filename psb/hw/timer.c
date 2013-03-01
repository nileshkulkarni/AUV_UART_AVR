#include <avr/io.h>
#include <avr/interrupt.h>
#include "../system_config.h"
#include "../utils.h"

#define PRESSURE_SENSOR_OCR (FOSC/PRESSURE_SENSOR_FREQ/1024)

extern volatile bool runEstimator;

void timerInit(void) {
/* prescaler = 1024 */
TCCR1B = (1 << CS02) | (1 << CS00);
OCR1AH = (PRESSURE_SENSOR_OCR & 0xFF00) >> 8;
OCR1AL = PRESSURE_SENSOR_OCR & 0x00FF;
/* enabling compare match interrupts */
TIMSK1 = (1 << OCIE1A);
TIFR1 = (1 << OCF1A);
/* begin timer */
TCNT1 = 0;
}

ISR (TIMER1_COMPA_vect) {
/* simulating CTC mode by forcing TCNT1 = 0 */
TCNT1 = 0;
runEstimator = TRUE;
/*
static int i = 0;
	if (i == 0) {
	PORTC = 0xF0;
	i = 1;
	}
	else {
	PORTC = 0x00;
	i = 0;
	}
	*/
}

