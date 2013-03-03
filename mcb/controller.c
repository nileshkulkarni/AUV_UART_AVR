#include "../common/utils.h"
#include "hw/hw.h"
#include "database.h"
#include "../common/system_config.h"

extern struct mcb_database theDatabase;
volatile bool runController;


void motionControl() {
/* if runController variable is true, run the controller, else return*/
static int j = 0;
	if (runController == TRUE) {
		int i;
		for(i=0;i<6;i++) {
		theDatabase.pwm[i] = 0x6167;
		}
		j++;
	}
	else {

	}

}
