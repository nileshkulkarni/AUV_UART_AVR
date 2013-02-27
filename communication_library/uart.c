#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define NO_DATA 0x00

typedef int bool;
#define true 1
#define false 0

bool receiveValue;
char receivedData;
bool transmitValue;
char transmittedData;

void uart_init( uint16_t ubrr){
		/* Set baud rate */
		UBRR2H = (unsigned char)(ubrr>>8);
		UBRR2L = (unsigned char)ubrr;
		//UBRR2 = 95;
		/* Enable receiver and transmitter */
		UCSR2A |= (1<<U2X2);
	//	UCSR0B =(1<<TXCIE0)|(1<<RXEN0)|(1<<TXEN0);
		UCSR2B |= (1<<RXCIE2)|(1<<TXCIE2)|(1<<RXEN2)|(1<<TXEN2);
		/* Set frame format: 8data, 1 stop bit */
		UCSR2C = (1<<UCSZ20)|(1<<UCSZ21);
		transmitValue = true;
		receiveValue = false;

} // USART_SR0A

void put_c(unsigned char data){
	
	if(transmitValue){
		while ( !( UCSR2A & (1<<UDRE2)) ); /* wait for empty transmit buffer*/
		/* Put data into buffer, sends the data */
		UDR2 = data ;
		transmitValue=false;
	}
}

unsigned char get_c(){
	/* Wait for data to be received */
	//while ( !(UCSR2A & (1<<RXC2)) );
	/* Get and return received data from buffer */
	//return UDR2;
	if(receiveValue){	
			return receivedData;
			receiveValue = false;
	}	
	else
			return NO_DATA;

			
}

void put_s(char * buffer, int bufferlen){
		while(*buffer){
				put_c(*buffer++);
		}
}

ISR(USART2_RX_vect){
	while ( !(UCSR2A & (1<<RXC2)));
	receiveValue=true;
//	PORTC=0xAA;
	receivedData = UDR2;
}

ISR(USART2_TX_vect){
//	PORTC=0xAA;
	transmitValue=true;
}	
