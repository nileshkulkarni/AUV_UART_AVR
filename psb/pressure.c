#include "../common/utils.h"
#include "database.h"
#include "pressure.h"

volatile bool runEstimator;
extern struct psb_database theDatabase;

void estimateDepth (void) {

	if (runEstimator == TRUE) {
		theDatabase.depth = (theDatabase.adcData - theDatabase.intercept)/theDatabase.slope;
		runEstimator = FALSE;
	}

}

void pressureInit(void) {

theDatabase.depth = 0;
theDatabase.depth = PRESSURE_INTERCEPT;
theDatabase.intercept = PRESSURE_INTERCEPT;
theDatabase.slope = PRESSURE_SLOPE;

}

