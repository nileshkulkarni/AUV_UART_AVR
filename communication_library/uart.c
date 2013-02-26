#include "uart.h"
#include <avr/io.h>
#include <avr/interrup.h>



#define NO_DATA 0x00

bool receiveValue=false;
char receivedData;
bool transmitValue=false;
char transmittedData;
void uart_init( uint16_t ubrr){
		/* Set baud rate */
		UBRR0H = (unsigned char)(ubrr>>8);
		UBRR0L = (unsigned char)ubrr;
		/* Enable receiver and transmitter */
		UCSR0B = (1<<RXEN0)|(1<<TXEN0);
		/* Set frame format: 8data, 1 stop bit */
		UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
} // USART_Init

void put_c(char data){
	
	if(transmitValue){
		while ( !( UCSR0A & (1<<UDRE0)) ); /* wait for empty transmit buffer*/
		/* Put data into buffer, sends the data */
		UDR0 = data ;
		transmitValue=false;
	}
}

char get_c(){
	/* Wait for data to be received */
	/*while ( !(UCSR0A & (1<<RXC0)) );*/
	/* Get and return received data from buffer */
	/*return UDR0;*/
	if(receiveValue)
			return receivedData;
	else
			return NO_DATA;
}

void put_s(char * buffer, int bufferlen){
		while(*buffer){
				put_c(*buffer++);
		}
}
ISR({0032}_vect){
	while ( !(UCSR0A & (1<<RXC0)));
	receiveValue=true;
	receivedData = UDR0;
}

ISR({0036}_vect){
	transmitValue=true;
}


		
