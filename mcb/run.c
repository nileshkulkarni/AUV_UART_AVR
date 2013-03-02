#include "../common/crc.h"
#include "hw/hw.h"
#include "controller.h"
#include "database.h"

extern char sbcReceiveBuffer[MCB_SBC_BUFFER_SIZE];
extern char sbcTransmitBuffer[MCB_SBC_BUFFER_SIZE];
extern bool sbcReceiveBufferFull;
extern int sbcReceiveBufferLength;

void run(void) {

	while(1) {
		if (sbcReceiveBufferFull == TRUE) {
			bool b = crc8Decrypt(sbcReceiveBuffer,MCB_SBC_BUFFER_SIZE);
			if (b == TRUE) {
				updateDatabase();
				sbcTransmitBuffer[0] = DATA_RECEIVED_TRUE;	
			}
			else {
				sbcTransmitBuffer[0] = DATA_RECEIVED_FALSE;
			}
			pressureSensorHandler();
			motionControl(); // this function would modify theDatabase
			updateTransmitBuffer(); 
			crc8Encrypt(sbcTransmitBuffer,MCB_SBC_BUFFER_SIZE);
			put_s(sbcTransmitBuffer,MCB_SBC_BUFFER_SIZE);
			sbcReceiveBufferFull = FALSE;
			sbcReceiveBufferLength = 0;
		}
		else {
			pressureSensorHandler();
			motionControl();
		}
	}
}
