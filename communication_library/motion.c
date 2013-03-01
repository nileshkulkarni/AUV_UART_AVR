#include "utils.h"
#include "hw/hw.h"
#include "database.h"
#include "system_config.h"

extern struct database theDabase;
volatile bool runController;


extern char uartReceiveBuffer[UART_BUFFER_SIZE];
extern char uartTransmitBuffer[UART_BUFFER_SIZE];
extern bool uartReceiveBufferFull;
extern int uartReceiveBufferLength;

void motionControl() {

/* if runController variable is true, run the controller, else return*/


int i;
	for(i=1;i<UART_BUFFER_SIZE-1;i++) {
		uartTransmitBuffer[i] = uartReceiveBuffer[UART_BUFFER_SIZE-1-i];
	}

}
