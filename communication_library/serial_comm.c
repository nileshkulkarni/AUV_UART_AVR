#include "link.h"
#include "crc.h"
#include "uart.h"
#include "motion.h"
#include "database.h"

extern char uartReceiveBuffer[UART_BUFFER_SIZE];
extern char uartTransmitBuffer[UART_BUFFER_SIZE];
extern bool uartReceiveBufferFull;
extern int uartReceiveBufferLength;

void communicate(void) {

	while(1) {
		if (uartReceiveBufferFull == TRUE) {
			bool b = crc8Decrypt(uartReceiveBuffer);
			if (b == TRUE) {
				updateDatabase();
				uartTransmitBuffer[0] = DATA_RECEIVED_TRUE;	
			}
			else {
				uartTransmitBuffer[0] = DATA_RECEIVED_FALSE;
			}
			pressureSensorHandler();
			motionControl(); // this function would modify theDatabase
			updateTransmitBuffer(); 
			crc8Encrypt(uartTransmitBuffer);
			put_s(uartTransmitBuffer,UART_BUFFER_SIZE);
			uartReceiveBufferFull = FALSE;
			uartReceiveBufferLength = 0;
		}
		else {
			pressureSensorHandler();
			motionControl();
		}
	}
}
