#include "database.h"
#include "hw/hw.h"

extern char mcbTransmitBuffer[PSB_MCB_BUFFER_SIZE];
extern char mcbReceiveBuffer[PSB_MCB_BUFFER_SIZE];
struct database theDatabase;
/*
Format of the transmit buffer is as follows:

*/

void updateTransmitBuffer (void) {

	mcbTransmitBuffer[DEPTH_POS] = theDatabase.depth >> 8;
	mcbTransmitBuffer[DEPTH_POS+1] = theDatabase.depth;

	mcbTransmitBuffer[ADC_DATA_POS] = theDatabase.adcData >> 8;
	mcbTransmitBuffer[ADC_DATA_POS+1] = theDatabase.adcData;

	mcbTransmitBuffer[INTERCEPT_POS] = theDatabase.intercept;
	mcbTransmitBuffer[SLOPE_POS] = theDatabase.slope;

}


void updateDatabase (void) {
	theDatabase.adcData = adcSample();
	theDatabase.mode = mcbReceiveBuffer[PSB_MODE_POS];
	if (theDatabase.mode == CALIBRATE_INTERCEPT) {
		theDatabase.intercept = theDatabase.adcData;
	}

}
