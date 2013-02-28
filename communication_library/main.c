#include <avr/interrupt.h>
#include <util/delay.h>
#include "crc.h"
#include "uart.h"



int main(){
	uart_init(MYUBRR);	
	sei();
	while(1){
		linkHandle();
		//motionControl();
	}
	return 0;

}
