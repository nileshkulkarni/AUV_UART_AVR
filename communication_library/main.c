#include <avr/interrupt.h>
#include <util/delay.h>
#include "crc.h"
#include "uart.h"
#include "database.h"

struct database theDatabase;

int main(void){
	DDRC = 0xFF;
	PORTC = 0xAF;
	uart_init(MYUBRR);	
	timerInit();
	adcInit();
	sei();
	while(1){
		communicate();
	}
	return 0;

}
