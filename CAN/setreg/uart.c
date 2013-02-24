#include <avr/io.h>
#include "common.h"
#include <util/delay.h>


# define BAUD_PRESCALE (((FCPU/(USART_BAUDRATE * 8UL))) - 1)
# define USART_BAUDRATE 9600    
# define FCPU 16000000
# define BAUD_PRESCALE (((FCPU/(USART_BAUDRATE * 8UL))) - 1)



void uart_init(void)                 
{
	UCSR0A |= (1<<U2X0);    //beacause of this in the baud_prescale formula 8 is there instead of 16
	UCSR0B |= (1<<RXCIE0)|(1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);//URSEL // Use 8-bit character sizes

	UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = BAUD_PRESCALE;
}



unsigned char uart_rx( void )        
{
	while ( !(UCSR0A & _BV(RXC0)) ); // wait until receive complete
	return UDR0;
}


void uart_tx( unsigned char data )
{
	while ( !(UCSR0A & _BV(UDRE0)) ); // wait until UDR is empty
	UDR0 = data;
}


