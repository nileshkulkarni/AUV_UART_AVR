#include <stdint.h>
#include "../common/crc.h"
#include "hw/hw.h"

extern uint8_t mcbReceiveBuffer[PSB_MCB_BUFFER_SIZE];
extern uint8_t mcbTransmitBuffer[PSB_MCB_BUFFER_SIZE];
extern bool mcbReceiveBufferFull;
extern int mcbReceiveBufferLength;
extern uint8_t depth;

extern uint8_t adcData;

void run(void) {

	while(1) {
		if (mcbReceiveBufferFull == TRUE) {
			static int iii = 0;
				if (iii == 0) {
				PORTC = 0xF0;
				iii = 1;
				}
				else {
				PORTC = 0x00;
				iii = 0;
				}
			bool b = crc8Decrypt(mcbReceiveBuffer,PSB_MCB_BUFFER_SIZE);
			if (b == TRUE) {
				updateDatabase();
				mcbTransmitBuffer[0] = DATA_RECEIVED_TRUE;
			}
			else {
				mcbTransmitBuffer[0] = DATA_RECEIVED_FALSE;
			}
			estimateDepth();
			updateTransmitBuffer();
			crc8Encrypt(mcbTransmitBuffer,PSB_MCB_BUFFER_SIZE);
			put_s(mcbTransmitBuffer,PSB_MCB_BUFFER_SIZE);
			mcbReceiveBufferFull = FALSE;
			mcbReceiveBufferLength = 0;
		}
		else {
			//updateDatabase();
			estimateDepth();
		}
	}
}
