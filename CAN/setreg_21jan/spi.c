/******************************************************************************
 * Copyright (C) 2005 Martin THOMAS, Kaiserslautern, Germany
 * <eversmith@heizung-thomas.de>
 * http://www.siwawi.arubi.uni-kl.de/avr_projects
 *****************************************************************************
 *
 * File    : spi.c
 * Version : 0.9
 * 
 * Summary : AVR SPI driver
 *
 *****************************************************************************/

#include <avr/io.h>
#include "spi.h"
#include "termio.h"



/* init as SPI-Master */
void spi_init(void)
{
	// SCK, SS!!, MOSI as outputs
	SPIDDR |= (1<<SPISCK)|(1<<SPISS)|(1<<SPIMOSI);
	// MISO as input
	SPIDDR &= ~(1<<SPIMISO);	// cbi(SPIDDR,SPIMISO);
	// INIT interface, Master, set clock rate fck/64 TODO: check prescaler
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}

uint8_t spi_write(uint8_t data)
{
	// set data to send into SPI data register
	SPDR = data;
	// Wait for transmission complete 
	while(!(SPSR & (1<<SPIF)));
}

uint8_t spi_read(void)
{
	while(!(SPSR & (1<<SPIF)));
    return SPDR;
}