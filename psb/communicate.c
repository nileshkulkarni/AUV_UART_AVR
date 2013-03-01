#include <stdint.h>
#include "../common/crc.h"
#include "hw/hw.h"

extern uint8_t mcbReceiveBuffer[MCB_BUFFER_SIZE];
extern uint8_t mcbTransmitBuffer[MCB_BUFFER_SIZE];
extern bool mcbReceiveBufferFull;
extern int mcbReceiveBufferLength;
extern uint8_t depth;

extern uint8_t adcData;

void communicate(void) {

	while(1) {
		if (mcbReceiveBufferFull == TRUE) {
			bool b = crc8Decrypt(mcbReceiveBuffer,MCB_BUFFER_SIZE);
			if (b == TRUE) {
				mcbTransmitBuffer[0] = DATA_RECEIVED_TRUE;
			}
			else {
				mcbTransmitBuffer[0] = DATA_RECEIVED_FALSE;
			}
			estimateDepth();
			mcbTransmitBuffer[1] = depth;
			mcbTransmitBuffer[2] = depth >> 8;
			crc8Encrypt(mcbTransmitBuffer,MCB_BUFFER_SIZE);
			put_s(mcbTransmitBuffer,MCB_BUFFER_SIZE);
			mcbReceiveBufferFull = FALSE;
			mcbReceiveBufferLength = 0;
		}
		else {
			estimateDepth();
		}
	}
}
