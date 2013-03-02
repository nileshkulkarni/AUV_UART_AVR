#include "../common/utils.h"
#include "database.h"

volatile bool runEstimator;
extern struct database theDatabase;

void estimateDepth (void) {

	if (runEstimator == TRUE) {
		theDatabase.depth = theDatabase.adcData;
		runEstimator = FALSE;
	}

}
