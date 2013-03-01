#include <avr/interrupt.h>
#include <util/delay.h>
#include "crc.h"
#include "hw/hw.h"
#include "database.h"
#include "communicate.h"

struct database theDatabase;

int main(void){
	DDRC = 0xFF;
	PORTC = 0xAF;
	uartInit(MYUBRR);	
	timerInit();
	adcInit();
	sei();
	while(1){
		communicate();
	}
	return 0;

}
