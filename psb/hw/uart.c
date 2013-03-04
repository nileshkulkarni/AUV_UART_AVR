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
		UBRR3H = (uint8_t)(ubrr>>8);
		UBRR3L = (uint8_t)ubrr;
		/* Enable receiver and transmitter */
		UCSR3A |= (1<<U2X3);
		UCSR3B |= (1<<RXCIE3)|(1<<RXEN3)|(1<<TXEN3);
		//UCSR2B |= (1<<RXCIE2)|(1<<TXCIE2)|(1<<RXEN2)|(1<<TXEN2);
		/* Set frame format: 8data, 1 stop bit */
		UCSR3C = (1<<UCSZ30)|(1<<UCSZ31);
		mcbReceiveBufferLength=0;
		mcbReceiveBufferFull=FALSE;

} 

void put_c(uint8_t data){
	
		while ( !( UCSR3A & (1<<UDRE3)) ); /* wait for empty transmit buffer*/
		/* Put data into buffer, sends the data */
		UDR3 = data ;
}




void put_s(uint8_t * buffer, int bufferlen){
	
	for(int i=0;i<bufferlen;i++){
				put_c(*buffer++);
		}
}

ISR(USART3_RX_vect){
	while ( !(UCSR3A & (1<<RXC3)));
	
	if(mcbReceiveBufferLength < PSB_MCB_BUFFER_SIZE){
			mcbReceiveBuffer[mcbReceiveBufferLength]=UDR3;
			mcbReceiveBufferLength++;
			if(mcbReceiveBufferLength ==PSB_MCB_BUFFER_SIZE){
					mcbReceiveBufferFull =TRUE;
					
			}
	}
	
}
