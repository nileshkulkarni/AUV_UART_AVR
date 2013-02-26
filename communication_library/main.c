
#include <util/delay.h>
#define FOSC 14745600 // Clock Speed
#define BAUD 9600
//#define MYUBRR ((FOSC/(BAUD*16))-1)
#define MYUBRR 103
#include "uart.h"

int main(){
	uart_init(MYUBRR);	
	DDRC = 0xFF;
	 char c;
	while(1){
			PORTC = 0xFF;
		//	c = get_c();
			put_c('a');
_delay_ms(1000);
			PORTC = 0x00;
			_delay_ms(1000);
	}
	return 0;

}
