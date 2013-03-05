#include <avr/interrupt.h>
#include <util/delay.h>
#include "hw/hw.h"
#include "database.h"
#include "run.h"

int main(void){
	DDRC = 0xFF;
	PORTC = 0xAF;
	controllerReset();
	uartInit();	
	timerInit();
	initDatabase();
	sei();
	//sbcPuts("auv-iitb",8);	
	/* entern the infinitum of communication and controlling*/
	run();
	return 0;

}
