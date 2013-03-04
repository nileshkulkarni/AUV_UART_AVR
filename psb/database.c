#include "database.h"
#include "hw/hw.h"

extern char mcbTransmitBuffer[PSB_MCB_BUFFER_SIZE];
extern char mcbReceiveBuffer[PSB_MCB_BUFFER_SIZE];
struct psb_database theDatabase;
/*
Format of the transmit buffer is as follows:
*/

void updateTransmitBuffer (void) {

	mcbTransmitBuffer[PSB_MCB_DEPTH_POS] = theDatabase.depth >> 8;
	mcbTransmitBuffer[PSB_MCB_DEPTH_POS+1] = theDatabase.depth;

	mcbTransmitBuffer[PSB_MCB_ADC_DATA_POS] = theDatabase.adcData >> 8;
	mcbTransmitBuffer[PSB_MCB_ADC_DATA_POS+1] = theDatabase.adcData;

	mcbTransmitBuffer[PSB_MCB_INTERCEPT_POS] = theDatabase.intercept;
	mcbTransmitBuffer[PSB_MCB_SLOPE_POS] = theDatabase.slope;
		

}


void updateDatabase (void) {
	theDatabase.adcData = adcSample();
	theDatabase.mode = mcbReceiveBuffer[PSB_MCB_MODE_POS];
	switch(theDatabase.mode) {
	case PSB_CALIBRATE_INTERCEPT: {
		theDatabase.intercept = theDatabase.adcData;
		break;
		}
	case PSB_SET_SLOPE_INTERCEPT: {
		theDatabase.intercept = mcbReceiveBuffer[PSB_MCB_INTERCEPT_POS];
		theDatabase.intercept = mcbReceiveBuffer[PSB_MCB_SLOPE_POS];
		break;
		}
	}

}
