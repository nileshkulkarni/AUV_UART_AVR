#include <avr/interrupt.h>
#include <util/delay.h>
#include "crc.h"
#include "uart.h"
#include "system_config.h"
#include "utils.h"

extern int uartReceiveBufferLength;
extern char uartReceiveBuffer[UART_BUFFER_SIZE];
extern char uartTransmitBuffer[UART_BUFFER_SIZE];

extern bool uartReceiveBufferFull;
int main(){
	uart_init(MYUBRR);	
	DDRC=0xFF;
	sei();
	PORTC= 0xAA;	
	while(1){
		//linkHandle();
		//motionControl();
	
		if(uartReceiveBufferFull){
				put_s(uartReceiveBuffer,UART_BUFFER_SIZE);
				PORTC=0xAA;
				uartReceiveBufferFull=FALSE;
				uartReceiveBufferLength=0;			
		}
		else {
				PORTC=0x55;
				continue;
		}	
	}
		/*	
			uint32_t i =0;
			while(i!=100000){
					i++;
			}
			PORTC= 0x01;
			while(i!=0){
					i--;
			}
			PORTC=0xA0;
	}*/
	return 0;

}
