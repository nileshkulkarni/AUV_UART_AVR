#include <avr/interrupt.h>
#include <avr/io.h>
#include "system_config.h"
#include "utils.h"
#include "database.h"

volatile uint16_t adcData;
volatile bool adcReceivedData;
extern struct database theDatabase;

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
}

ISR(ADC_vect) {
/* read ADCL first and then ADCH */
adcData = 0x0000 & ADCL;
adcData += ((0x00FF & ADCH)<<8);
adcReceivedData = TRUE;
static int i = 0;
	if (i == 0) {
	PORTC = 0x0F;
	i = 1;
	}
	else {
	PORTC = 0x00;
	i = 0;
	}
}


void pressureSensorHandler (void) {

	if (adcReceivedData == TRUE) {
		theDatabase.sensorDepth = (DEPTH_CALIBRATION_SLOPE*adcData) + DEPT_CALIBRATION_INTERCEPT;
		adcReceivedData = FALSE;
		adcStartSampling();
	}
}
