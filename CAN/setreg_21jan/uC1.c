#include <avr/io.h>
#include "spi.h"
#include <util/delay.h>

int main(void)
{
	DDRB|=0b00000101;
	spi_init();		// init SPI-Interface (as "Master")

	while(1){
	PORTB&=0b11111101;
	PORTB|=0b00000001;
	_delay_ms(5000);
	spi_write(0b00000011);
	uart_tx('a');
	PORTB&=0b11111110;
	PORTB|=0b00000010;

	_delay_ms(5000);
	PORTB&=0b11111101;
	PORTB|=0b00000001;
	_delay_ms(5000);
	
	spi_write(0b00001111);
	
	PORTB&=0b11111110;
	PORTB|=0b00000010;
	_delay_ms(5000);
	
uart_tx('b');
	
	
	
	PORTB&=0b11111101;
	PORTB|=0b00000001;
	_delay_ms(5000);
	
	char c =spi_read();
	PORTB&=0b11111110;
	PORTB|=0b00000010;
	_delay_ms(5000);
	
	uart_tx('c');
	//_delay_ms(5000);
	}

}	



	
