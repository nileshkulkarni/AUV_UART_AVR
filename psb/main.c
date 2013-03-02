#include <avr/interrupt.h>
#include <util/delay.h>
#include "hw/hw.h"




int main(void){
	uartInit();	
	timerInit();
	adcInit();

	pressureInit();

	sei();

	run();
	return 0;

}
