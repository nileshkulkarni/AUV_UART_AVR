#include <avr/interrupt.h>
#include <util/delay.h>
#include "crc.h"
#include "uart.h"
#include "database.h"

struct database theDatabase;

int main(void){
	uart_init(MYUBRR);	
	sei();
	while(1){
		linkHandle();
	}
	return 0;

}
