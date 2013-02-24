
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "uart.h"
#include "calcCheck.c"

#define UART_BAUD_RATE 9600

void processData(int c){
		PORTC = c;

}

/*All commands will be in the form 
 * $MODE,relevant,data,comma,seprated,checkSum$
 *
 */
/*
 * List of modes in MCB
 * Brake mode (BM) - no data along with this.
 * stand still mode (SSM) - no data along with this
 * External control (EC) - change the mode first and then keep on sending pwm values over uart from SBC.
 * yaw control (YC) 
 * Pitch control (PiC)
 * Postion control (PoC)
 * Surface the auv (SA)
 * Configuration mode (CM)
 * Read Configuration 
 * Normal Mode (NM)
 */

void DataHandle(char * data){
		/* data is the date received from uart.
		 * which has mode etc information encoded onto it.
		 */



















int main(void){
	
	DDRC = 0x00;	
		
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	sei();
	unsigned int c;
	while(1){
		c = uart_getc();
		if(c & UART_NO_DATA){
				/*
			 	* NO UART DATA available
			 	*/
		}
		else{
				/*
				 *  New Data is avialable at the port.
				 *  check the frame for overrun errro
				 */
				if ( c & UART_FRAME_ERROR ){

	   					/* Framing Error detected, i.e no stop bit detected */
						uart_puts_P("UART Frame Error: ");
				}	
				if ( c & UART_OVERRUN_ERROR ){			
	
						/* 
						 *
						 * Overrun, a character already present in the UART UDR register was 
				 		 *
						 * not read by the interrupt handler before the next character arrived,
						 * one or more received characters have been dropped
				  		 *	
				 		 *                                                                  
						 */

						uart_puts_P("UART Overrun Error: ");
		
				}

				if ( c & UART_BUFFER_OVERFLOW ){

						/* 
						 *
					 	 * We are not reading the receive buffer fast enough,
						 *
						 * one or more received character have been dropped 
					 	 *
					 	 */

						uart_puts_P("Buffer overflow error: ");

				}

				processData(c);
			//	PORTC = c;
		}
	}
	return 0;
}




