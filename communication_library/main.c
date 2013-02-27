#include <avr/interrupt.h>
#include <util/delay.h>
#define FOSC 14745600 // Clock Speed
#define BAUD 9600
#define MYUBRR ((FOSC/BAUD/8)-1)
//#define MYUBRR 95
#include "uart.h"
extern bool receiveBufferFull;
extern char receiveBuffer[10];
extern int receiveBufferLength;
int main(){
	uart_init(MYUBRR);	
	sei();
	DDRC = 0xFF;
	char baud;
	unsigned char c=0xAA;
	while(1){
		   // c = get_c();
			//PORTC = (0xFF - c);
			//put_c('a');
		//	_delay_ms(1000);
		//	PORTC = 0x00;
		//	_delay_ms(1000);

		if(receiveBufferFull == true){
				put_s(receiveBuffer,10);
				receiveBufferFull=false;
				receiveBufferLength=0;
				break;
		}
		else{
				put_s("Yet\n",4);
		}



	}
	return 0;

}