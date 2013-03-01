#include "utils.h"
#include "uart.h"
#include "database.h"

extern struct database theDabase;


extern char uartReceiveBuffer[UART_BUFFER_SIZE];
extern char uartTransmitBuffer[UART_BUFFER_SIZE];
extern bool uartReceiveBufferFull;
extern int uartReceiveBufferLength;

void motionControl() {


int i;
	for(i=1;i<UART_BUFFER_SIZE-1;i++) {
		uartTransmitBuffer[i] = uartReceiveBuffer[UART_BUFFER_SIZE-1-i];
	}

}
