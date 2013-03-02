#include "../common/utils.h"

volatile bool runEstimator;
uint16_t depth;
extern uint16_t adcData;

void estimateDepth (void) {

	if (runEstimator == TRUE) {
		depth = adcData;	
		runEstimator = FALSE;
	}

}
