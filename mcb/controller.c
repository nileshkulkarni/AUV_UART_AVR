#include "../common/utils.h"
#include "hw/hw.h"
#include "database.h"
#include "../common/system_config.h"
#include "controller.h"

extern struct mcb_database theDatabase;
volatile bool runController;
struct controller_meta_data theCMD;


void motionControl(void) {
/* if runController variable is true, run the controller, else return*/

	if (runController == TRUE) {
		theCMD.yawErrorCurr = theDatabase.yawSetPoint - theDatabase.sensorYaw;
		theCMD.yawErrorPrev = theCMD.yawErrorCurr;
		theCMD.yawErrorDiff = theCMD.yawErrorCurr - theCMD.yawErrorPrev;
		theCMD.yawErrorSum += theCMD.yawErrorCurr;
		theCMD.depthErrorPrev = theCMD.depthErrorCurr;
		theCMD.depthErrorCurr = theDatabase.sensorDepth;
		theCMD.depthErrorDiff = theCMD.depthErrorCurr - theCMD.depthErrorPrev;
		theCMD.depthErrorSum += theCMD.depthErrorCurr;

		/* motors 1 and 6 control yaw and sway */

		theDatabase.pwm[1] = 512 + (theDatabase.cSway)*(theDatabase.swayVelSetPoint);
		theDatabase.pwm[1] += (theDatabase.kpYaw)*(theCMD.yawErrorCurr);
		theDatabase.pwm[1] += (theDatabase.kdYaw)*(theCMD.yawErrorDiff);
		theDatabase.pwm[1] += ((theDatabase.kiYaw)*(theCMD.yawErrorDiff) >> KI_DIV);

		theDatabase.pwm[6] = 512 - (theDatabase.cSway)*(theDatabase.swayVelSetPoint);
		theDatabase.pwm[6] -= (theDatabase.kpYaw)*(theCMD.yawErrorCurr);
		theDatabase.pwm[6] -= (theDatabase.kdYaw)*(theCMD.yawErrorDiff);
		theDatabase.pwm[6] -= ((theDatabase.kiYaw)*(theCMD.yawErrorDiff) >> KI_DIV);

		/* motors 2 and 5 control surge */
		
		theDatabase.pwm[2] = 512 + (theDatabase.cSurge)*(theDatabase.surgeVelSetPoint);
		theDatabase.pwm[5] = 512 - (theDatabase.cSurge)*(theDatabase.surgeVelSetPoint);

		/* motors 3 and 4 control depth */

		theDatabase.pwm[3] = 512 + (theDatabase.kpDepth)*(theCMD.depthErrorCurr);
		theDatabase.pwm[3] += (theDatabase.kdDepth)*(theCMD.depthErrorDiff);
		theDatabase.pwm[3] += ((theDatabase.kiDepth)*(theCMD.depthErrorDiff) >> KI_DIV);

		theDatabase.pwm[4] = 512 + (theDatabase.kpDepth)*(theCMD.depthErrorCurr);
		theDatabase.pwm[4] -= (theDatabase.kdDepth)*(theCMD.depthErrorDiff);
		theDatabase.pwm[4] -= ((theDatabase.kiDepth)*(theCMD.depthErrorDiff) >> KI_DIV);
	}

	REG_MOTOR_1_PWM = theDatabase.pwm[1];
	REG_MOTOR_2_PWM = theDatabase.pwm[2];
	REG_MOTOR_3_PWM = theDatabase.pwm[3];
	REG_MOTOR_4_PWM = theDatabase.pwm[4];
	REG_MOTOR_5_PWM = theDatabase.pwm[5];
	REG_MOTOR_6_PWM = theDatabase.pwm[6];

}

void controllerInit(void) {
theCMD.yawErrorCurr = 0;
theCMD.yawErrorPrev = 0;
theCMD.yawErrorSum = 0;
theCMD.yawErrorDiff = 0;

theCMD.depthErrorCurr = 0;
theCMD.depthErrorPrev = 0;
theCMD.depthErrorSum = 0;
theCMD.depthErrorDiff = 0;
}
