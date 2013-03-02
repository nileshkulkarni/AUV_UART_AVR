#include "database.h"
#include "hw/hw.h"

extern char mcbTransmitBuffer[PSB_MCB_BUFFER_SIZE];
extern char mcbReceiveBuffer[PSB_MCB_BUFFER_SIZE];
struct database theDatabase;
extern uint8_t adcData;
/*
Format of the transmit buffer is as follows:

*/

void updateTransmitBuffer (void) {
	mcbTransmitBuffer[DEPTH_POS] = theDatabase.depth >> 8;
	mcbTransmitBuffer[DEPTH_POS+1] = theDatabase.depth;

	mcbTransmitBuffer[ADC_DATA_POS] = theDatabase.adcData >> 8;
	mcbTransmitBuffer[ADC_DATA_POS+1] = theDatabase.adcData;

}


void updateDatabase (void) {
	theDatabase.adcData = adcData;
	theDatabase.mode = mcbReceiveBuffer[PSB_MODE_POS];
}
