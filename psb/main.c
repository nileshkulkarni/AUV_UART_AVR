#include <avr/interrupt.h>
#include <util/delay.h>
#include "hw/hw.h"




int main(void){
	uartInit();	
	timerInit();
	adcInit();

	pressureInit();

	DDRC = 0xFF;
	PORTC = 0xAA;
	sei();

	run();
	return 0;

}
