#include "../common/utils.h"
#include "database.h"
#include "pressure.h"

volatile bool runEstimator;
extern struct psb_database theDatabase;

void estimateDepth (void) {

	if (runEstimator == TRUE) {
		if(theDatabase.adcData < theDatabase.intercept) {
		theDatabase.depth = 0;
		}
		else {
		theDatabase.depth = (theDatabase.adcData - theDatabase.intercept)/theDatabase.slope;
		}
	}

}

void pressureInit(void) {

theDatabase.depth = 0;
theDatabase.depth = PRESSURE_INTERCEPT;
theDatabase.intercept = PRESSURE_INTERCEPT;
theDatabase.slope = PRESSURE_SLOPE;

}

