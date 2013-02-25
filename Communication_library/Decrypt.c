
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

bool validateData(char * data){
	/* this funtion establishes the authenticity of the data.
	 */
	
	int length = sizeof (data) /sizeof(data[0]) ;
	uint16_t checksumRecv=0;
	uint16_t checksum=0;
	int i;
	int CheckSumPostion=0;
	
	if(length >=1){

		if(data[0] != '$'){
			return false;
		}

		if(data[length-1] != '$'){
			return false;
		}
	}
	
	else{ 
			return false;
	}

	for (i=length-2;i>=0;i++){
		if(data[i] == ','){
			CheckSumPostion = i+1;
		 	break;
		}
		else
			continue;	
	}
	char * rawdata = malloc(length-4)
	char * checkChar = malloc(2);
	/* no convert that part of string to no.. keep in mind the last character should be a dollar ($) */
	for(i = CheckSumPostion;i<length-1;i++){
			checkChar[i-CheckSumPositon]=data[i];
	}
	for(i=1;i<length-3;i++){
		rawdata[i-1]=data[i];
	}

	checksumRecv = getInt(checkChar);
	/* calculate actual check sum of the data.*/
	checksum = calcChecksum(rawdata);
	
	if(checksum==checksumRecv){
			return true;
	}
	else
			return false;


}


void DataHandler(char * data){
		/* data is the date received from uart.
		 * which has mode etc information encoded onto it.
		 */
	/* first I have to verify whether the data is correct then we have to interpre the data.
	 * step by step token by token.
	 */
	
	

		//call data validator.
		if(validateData(data)){	
			interpretData(data);	

		}
		else{
#ifdef DEBUG		
				printf("Data Validation failed");
#endif






}






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




