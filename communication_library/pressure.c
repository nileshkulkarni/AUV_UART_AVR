#include "hw/hw.h"
#include "database.h"

extern bool adcReceivedData;
extern struct database theDatabase;
extern uint16_t adcData;

void pressureSensorHandler (void) {

	if (adcReceivedData == TRUE) {
		theDatabase.sensorDepth = (DEPTH_CALIBRATION_SLOPE*adcData) + DEPT_CALIBRATION_INTERCEPT;
		adcReceivedData = FALSE;
		adcStartSampling();
	}
}
