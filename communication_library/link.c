#include "link.h"
#include "crc.h"
#include "uart.h"

extern char uartReceiveBuffer[UART_BUFFER_SIZE];
extern char uartTransmitBuffer[UART_BUFFER_SIZE];
extern bool uartReceiveBufferFull;
extern int uartReceiveBufferLength;

void linkHandle() {

	if (uartReceiveBufferFull == TRUE) {
		bool b = crc8Decrypt(uartReceiveBuffer);
		if (b == TRUE) {
			uartTransmitBuffer[0] = 't';
			crc8Encrypt(uartTransmitBuffer);
			put_s(uartTransmitBuffer,UART_BUFFER_SIZE);
		}
		else {
			uartTransmitBuffer[0] = 'f';
			crc8Encrypt(uartTransmitBuffer);
			put_s(uartTransmitBuffer,UART_BUFFER_SIZE);
		}
	uartReceiveBufferFull = FALSE;
	uartReceiveBufferLength = 0;
	}
}
