#include "uart.h"
#include "crc.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


bool uartReceiveValue;
char uartReceivedData;
bool uartTransmitValue;
char uartTransmittedData;
bool uartReceiveBufferFull;
int uartReceiveBufferLength;
bool uartTransmitBufferFull;


char uartReceiveBuffer[RECEIVE_BUFFER_SIZE];
char uartTransmitBuffer[TRANSMIT_BUFFER_SIZE];




void uart_init( uint16_t ubrr){
		/* Set baud rate */
		UBRR2H = (unsigned char)(ubrr>>8);
		UBRR2L = (unsigned char)ubrr;
		/* Enable receiver and transmitter */
		UCSR2A |= (1<<U2X2);
		UCSR2B |= (1<<RXCIE2)|(1<<TXCIE2)|(1<<RXEN2)|(1<<TXEN2);
		/* Set frame format: 8data, 1 stop bit */
		UCSR2C = (1<<UCSZ20)|(1<<UCSZ21);
		uartTransmitValue = true;
		uartReceiveValue = false;
		uartReceiveBufferLength=0;
		uartReceiveBufferFull=false;
		uartTransmitBufferFull=false;

} 

void put_c(unsigned char data){
	
		while ( !( UCSR2A & (1<<UDRE2)) ); /* wait for empty transmit buffer*/
		/* Put data into buffer, sends the data */
		UDR2 = data ;
		uartTransmitValue=false;
}



unsigned char get_c(){
	/* Wait for data to be received */
	/* Get and return received data from buffer */
	if(uartReceiveValue){	
			return uartReceivedData;
			uartReceiveValue = false;
	}	
	else
			return NO_DATA;		
}

void put_s(char * buffer, int bufferlen){
	
	for(int i=0;i<bufferlen;i++){
				put_c(*buffer++);
		}
}

ISR(USART2_RX_vect){
	while ( !(UCSR2A & (1<<RXC2)));
	uartReceiveValue=true;
	uartReceivedData = UDR2;
	
	if(uartReceiveBufferLength < RECEIVE_BUFFER_SIZE){
			uartReceiveBuffer[uartReceiveBufferLength]=uartReceivedData;
			uartReceiveBufferLength++;
			if(uartReceiveBufferLength ==RECEIVE_BUFFER_SIZE){
					uartReceiveBufferFull =true;
					
			}
	}
	
}
/*
ISR(USART2_TX_vect){
	uartTransmitValue=true;
}	
*/
