#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "hw.h"


bool mcbReceiveBufferFull;
int mcbReceiveBufferLength;
uint8_t mcbReceiveBuffer[PSB_MCB_BUFFER_SIZE];
uint8_t mcbTransmitBuffer[PSB_MCB_BUFFER_SIZE];




void uartInit(){
		/* Set baud rate */
		uint16_t ubrr = PSB_MCB_BAUD_UBRR;
		UBRR2H = (uint8_t)(ubrr>>8);
		UBRR2L = (uint8_t)ubrr;
		/* Enable receiver and transmitter */
		UCSR2A |= (1<<U2X2);
		UCSR2B |= (1<<RXCIE2)|(1<<RXEN2)|(1<<TXEN2);
		//UCSR2B |= (1<<RXCIE2)|(1<<TXCIE2)|(1<<RXEN2)|(1<<TXEN2);
		/* Set frame format: 8data, 1 stop bit */
		UCSR2C = (1<<UCSZ20)|(1<<UCSZ21);
		mcbReceiveBufferLength=0;
		mcbReceiveBufferFull=FALSE;

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
	
	if(mcbReceiveBufferLength < PSB_MCB_BUFFER_SIZE){
			mcbReceiveBuffer[mcbReceiveBufferLength]=UDR2;
			mcbReceiveBufferLength++;
			if(mcbReceiveBufferLength ==PSB_MCB_BUFFER_SIZE){
					mcbReceiveBufferFull =TRUE;
					
			}
	}
	
}
