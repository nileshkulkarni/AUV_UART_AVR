#include "hw.h"
#include "crc.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


bool uartReceiveBufferFull;
int uartReceiveBufferLength;
uint8_t uartReceiveBuffer[UART_BUFFER_SIZE];
uint8_t uartTransmitBuffer[UART_BUFFER_SIZE];




void uartInit( uint16_t ubrr){
		/* Set baud rate */
		UBRR2H = (uint8_t)(ubrr>>8);
		UBRR2L = (uint8_t)ubrr;
		/* Enable receiver and transmitter */
		UCSR2A |= (1<<U2X2);
		UCSR2B |= (1<<RXCIE2)|(1<<TXCIE2)|(1<<RXEN2)|(1<<TXEN2);
		/* Set frame format: 8data, 1 stop bit */
		UCSR2C = (1<<UCSZ20)|(1<<UCSZ21);
		uartReceiveBufferLength=0;
		uartReceiveBufferFull=FALSE;

} 

void put_c(uint8_t data){
	
		while ( !( UCSR2A & (1<<UDRE2)) ); /* wait for empty transmit buffer*/
		/* Put data into buffer, sends the data */
		UDR2 = data ;
}




void put_s(uint8_t * buffer, int bufferlen){
	
	for(int i=0;i<bufferlen;i++){
				put_c(*buffer++);
		}
}

ISR(USART2_RX_vect){
	while ( !(UCSR2A & (1<<RXC2)));
	
	if(uartReceiveBufferLength < UART_BUFFER_SIZE){
			uartReceiveBuffer[uartReceiveBufferLength]=UDR2;
			uartReceiveBufferLength++;
			if(uartReceiveBufferLength ==UART_BUFFER_SIZE){
					uartReceiveBufferFull =TRUE;
					
			}
	}
	
}
