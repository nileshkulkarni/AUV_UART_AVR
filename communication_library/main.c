#include <avr/interrupt.h>
#include <util/delay.h>
#include "crc.h"
#include "uart.h"

extern bool uartReceiveBufferFull;
extern char uartReceiveBuffer[RECEIVE_BUFFER_SIZE];
extern int uartReceiveBufferLength;

#define BAUD 9600

int main(){
	uart_init(MYUBRR);	
	sei();
	DDRC = 0xFF;
	char baud;
	unsigned char c=0xAA;
	while(1){
		if(uartReceiveBufferFull == true){
				put_s(uartReceiveBuffer,RECEIVE_BUFFER_SIZE);
				uartReceiveBufferFull=false;
				uartReceiveBufferLength=0;
				break;
		}
		else{
				put_s("Yet\n",4);
		}



	}
	return 0;

}
