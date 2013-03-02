#include <avr/interrupt.h>
#include <util/delay.h>
#include "hw/hw.h"




int main(void){
	uartInit();	
	timerInit();
	adcInit();

	sei();
	
	put_s("auv-iitb",8);

	communicate();
	return 0;

}
