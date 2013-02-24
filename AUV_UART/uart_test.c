
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "uart.h"

#ifndef F_CPU
#define F_CPU 4000000UL
#endif

#define UART_BAUD_RATE 9600
#define __AVR_ATmega32__ 1 
void processData(int c){
		PORTC = c;

}
int main(void){
	
	DDRC = 0x00;	
		
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	sei();
	unsigned int c;
	while(1)
	{
		PORTC = 0xFF;
		char s = 'a';
		uart_putc(s);
	}
	return 0;
}
