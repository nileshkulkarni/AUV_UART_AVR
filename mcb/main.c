#include <avr/interrupt.h>
#include <util/delay.h>
#include "hw/hw.h"
#include "database.h"
#include "communicate.h"

struct database theDatabase;

int main(void){
	DDRC = 0xFF;
	PORTC = 0xAF;
	uartInit();	
	timerInit();
	adcInit();
	sei();
	
	/* entern the infinitum of communication */
	communicate();
	return 0;

}
