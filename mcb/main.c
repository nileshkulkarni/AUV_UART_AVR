#include <avr/interrupt.h>
#include <util/delay.h>
#include "hw/hw.h"
#include "database.h"
#include "run.h"

int main(void){
	DDRC = 0xFF;
	PORTC = 0xAF;
	controllerInit();
	uartInit();	
	timerInit();
	sei();
	
	/* entern the infinitum of communication and controlling*/
	run();
	return 0;

}
