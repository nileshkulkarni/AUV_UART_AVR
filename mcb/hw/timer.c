#include <avr/io.h>
#include <avr/interrupt.h>
#include "hw.h"


extern volatile bool runController;

void timerInit(void) {
/* motion controller frequency */
/* prescaler = 1024 */
REG_FREQ_TCCRB = (1 << REG_FREQ_CS2) | (1 << REG_FREQ_CS0);
REG_FREQ_OCRAH = (MOTION_CONTROLLER_OCR & 0xFF00) >> 8;
REG_FREQ_OCRAL = MOTION_CONTROLLER_OCR & 0x00FF;
/* enabling compare match interrupts */
REG_FREQ_TIMSK = (1 << REG_FREQ_OCIEA);
REG_FREQ_TIFR = (1 << REG_FREQ_OCFA);
/* begin timer */
REG_FREQ_TCNT = 0;

/* pwm generation */
DDRE = 0xFF;
DDRH = 0xFF;
TCCR4A = (1 << WGM41)|(1 << WGM40)|(1 << COM4A1)|(1 << COM4B1)|(1 << COM4C1);
TCCR4B = (1 << CS40);
TCCR3A = (1 << WGM31)|(1 << WGM30)|(1 << COM3A1)|(1 << COM3B1)|(1 << COM3C1);
TCCR3B = (1 << CS30);
REG_MOTOR_1_OCR = 512;
REG_MOTOR_2_OCR = 512;
REG_MOTOR_3_OCR = 512;
REG_MOTOR_4_OCR = 512;
REG_MOTOR_5_OCR = 512;
REG_MOTOR_6_OCR = 512;
}

ISR (REG_FREQ_TIMER_COMPA_vect) {
/* simulating CTC mode by forcing TCNT1 = 0 */
REG_FREQ_TCNT = 0;
runController = TRUE;
/*
DDRC = 0xFF;
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

