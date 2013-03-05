#include "../common/crc.h"
#include "hw/hw.h"
#include "controller.h"
#include "database.h"

extern char sbcReceiveBuffer[MCB_SBC_BUFFER_SIZE];
extern char sbcTransmitBuffer[MCB_SBC_BUFFER_SIZE];
extern bool sbcReceiveBufferFull;
extern int sbcReceiveBufferLength;

extern char psbReceiveBuffer[MCB_SBC_BUFFER_SIZE];
extern char psbTransmitBuffer[MCB_SBC_BUFFER_SIZE];
extern bool psbReceiveBufferFull;
extern int psbReceiveBufferLength;
extern struct mcb_database theDatabase;

volatile bool pingPsb;

void run(void) {

	crc8Encrypt(psbTransmitBuffer,PSB_MCB_BUFFER_SIZE);
	psbPuts(psbTransmitBuffer,PSB_MCB_BUFFER_SIZE);

	while(1) {
		if (sbcReceiveBufferFull == TRUE) {
			bool b = crc8Decrypt(sbcReceiveBuffer,MCB_SBC_BUFFER_SIZE);
			if (b == TRUE) {
				updateSbcDatabase();
				sbcTransmitBuffer[0] = DATA_RECEIVED_TRUE;	
			}
			else {
				sbcTransmitBuffer[0] = DATA_RECEIVED_FALSE;
			}
			motionControl(); // this function would modify theDatabase
			updateSbcTransmitBuffer(); 
			crc8Encrypt(sbcTransmitBuffer,MCB_SBC_BUFFER_SIZE);
			sbcPuts(sbcTransmitBuffer,MCB_SBC_BUFFER_SIZE);
			sbcReceiveBufferFull = FALSE;
			sbcReceiveBufferLength = 0;
		}
		else {
			motionControl();
		}


		if (psbReceiveBufferFull == TRUE) {
			bool b = crc8Decrypt(psbReceiveBuffer,PSB_MCB_BUFFER_SIZE);
			if (b == TRUE) {
				updatePsbDatabase();
				psbTransmitBuffer[0] = DATA_RECEIVED_TRUE;	
			}
			else{
				psbTransmitBuffer[0] = DATA_RECEIVED_FALSE;
			}
			updatePsbTransmitBuffer(); 
			crc8Encrypt(psbTransmitBuffer,PSB_MCB_BUFFER_SIZE);
			if((pingPsb == TRUE) && (theDatabase.psbCommOn == TRUE)) {
				TOGGLE(PORTC);
				psbPuts(psbTransmitBuffer,PSB_MCB_BUFFER_SIZE);
				pingPsb = FALSE;
				psbReceiveBufferFull = FALSE;
				psbReceiveBufferLength = 0;
			}
		}
	}
}
