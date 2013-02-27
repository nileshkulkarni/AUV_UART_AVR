
#include <util/delay.h>
#define FOSC 14745600 // Clock Speed
#define BAUD 9600
#define MYUBRR ((FOSC/BAUD/8)-1)
//#define MYUBRR 95
#include "uart.h"

int main(){
	uart_init(MYUBRR);	
	DDRC = 0xFF;
	char baud;
	unsigned char c=0xAA;
	while(1){
		    c = get_c();
			PORTC = (0xFF - c);
			put_s("dhga",4);
		//	_delay_ms(1000);
		//	PORTC = 0x00;
		//	_delay_ms(1000);
	}
	return 0;

}
