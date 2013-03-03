#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "hw.h"


bool sbcReceiveBufferFull;
int sbcReceiveBufferLength;
uint8_t sbcReceiveBuffer[MCB_SBC_BUFFER_SIZE];
uint8_t sbcTransmitBuffer[MCB_SBC_BUFFER_SIZE];

bool psbReceiveBufferFull;
int psbReceiveBufferLength;
uint8_t psbReceiveBuffer[PSB_MCB_BUFFER_SIZE];
uint8_t psbTransmitBuffer[PSB_MCB_BUFFER_SIZE];



void uartInit(){
	/* init the mcb-sbc buffer */
		/* Set baud rate */
		uint16_t ubrr = MCB_SBC_BAUD_UBRR;
		REG_SBC_UBRRH = (uint8_t)(ubrr>>8);
		REG_SBC_UBRRL = (uint8_t)ubrr;
		/* Enable receiver and transmitter */
		REG_SBC_UCSRA |= (1<<REG_SBC_U2X);
		REG_SBC_UCSRB |= (1<<REG_SBC_RXCIE)|(1<<REG_SBC_RXEN)|(1<<REG_SBC_TXEN);
		/* Set frame format: 8data, 1 stop bit */
		REG_SBC_UCSRC = (1<<REG_SBC_UCSZ0)|(1<<REG_SBC_UCSZ1);
		sbcReceiveBufferLength=0;
		sbcReceiveBufferFull=FALSE;

	/* init the psb-mcb buffer */
		/* Set baud rate */
		ubrr = PSB_MCB_BAUD_UBRR;
		REG_PSB_UBRRH = (uint8_t)(ubrr>>8);
		REG_PSB_UBRRL = (uint8_t)ubrr;
		/* Enable receiver and transmitter */
		REG_PSB_UCSRA |= (1<<REG_PSB_U2X);
		REG_PSB_UCSRB |= (1<<REG_PSB_RXCIE)|(1<<REG_PSB_RXEN)|(1<<REG_PSB_TXEN);
		/* Set frame format: 8data, 1 stop bit */
		REG_PSB_UCSRC = (1<<REG_PSB_UCSZ0)|(1<<REG_PSB_UCSZ1);
		psbReceiveBufferLength=0;
		psbReceiveBufferFull=FALSE;


} 

void sbcPutc(uint8_t data){
	
		while ( !( REG_SBC_UCSRA & (1<<REG_SBC_UDRE)) ); /* wait for empty transmit buffer*/
		/* Put data into buffer, sends the data */
		REG_SBC_UDR = data ;
}

void psbPutc(uint8_t data){
	
		while ( !( REG_PSB_UCSRA & (1<<REG_PSB_UDRE)) ); /* wait for empty transmit buffer*/
		/* Put data into buffer, sends the data */
		REG_PSB_UDR = data ;
}




void sbcPuts(uint8_t * buffer, int bufferlen){
	
	for(int i=0;i<bufferlen;i++){
				sbcPutc(*buffer++);
		}
}

void psbPuts(uint8_t * buffer, int bufferlen){
	
	for(int i=0;i<bufferlen;i++){
				psbPutc(*buffer++);
		}
}

ISR(REG_SBC_USART_RX_vect){
	while ( !(REG_SBC_UCSRA & (1<<REG_SBC_RXC)));
	
	if(sbcReceiveBufferLength < MCB_SBC_BUFFER_SIZE){
			sbcReceiveBuffer[sbcReceiveBufferLength]=REG_SBC_UDR;
			sbcReceiveBufferLength++;
			if(sbcReceiveBufferLength ==MCB_SBC_BUFFER_SIZE){
					sbcReceiveBufferFull =TRUE;
					
			}
	}
	
}

ISR(REG_PSB_USART_RX_vect){
	while ( !(REG_PSB_UCSRA & (1<<REG_PSB_RXC)));
	
	if(psbReceiveBufferLength < PSB_MCB_BUFFER_SIZE){
			psbReceiveBuffer[psbReceiveBufferLength]=REG_PSB_UDR;
			psbReceiveBufferLength++;
			if(psbReceiveBufferLength == PSB_MCB_BUFFER_SIZE){
					psbReceiveBufferFull =TRUE;
					
			}
	}
	
}
