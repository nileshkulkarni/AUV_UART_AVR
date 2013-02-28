#include <avr/interrupt.h>
#include <util/delay.h>
#include "crc.h"
#include "uart.h"

extern bool uartReceiveBufferFull;
extern char uartReceiveBuffer[UART_BUFFER_SIZE];
extern int uartReceiveBufferLength;

#define BAUD 9600

int main(){
	uart_init(MYUBRR);	
	sei();
	while(1){
		linkHandle();
		//motionControl();
	}
	return 0;

}
