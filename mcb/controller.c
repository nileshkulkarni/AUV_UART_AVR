#include "../common/utils.h"
#include "hw/hw.h"
#include "database.h"
#include "../common/system_config.h"
#include "controller.h"

#define PWM_CAP(X) if((X>1023)&&(X<0x1FFF)){X = 1023;}if(X>0x1FFF){X=0;}

extern struct mcb_database theDatabase;
volatile bool runController;
struct controller_meta_data theCMD;


void motionControl(void) {
/* if runController variable is true, run the controller, else return*/

	if (runController == TRUE) {
		theCMD.yawErrorPrev = theCMD.yawErrorCurr;
		theCMD.yawErrorCurr = theDatabase.yawSetPoint - theDatabase.sensorYaw;
		theCMD.yawErrorDiff = theCMD.yawErrorCurr - theCMD.yawErrorPrev;
		theCMD.yawErrorSum += theCMD.yawErrorCurr;
		theCMD.depthErrorPrev = theCMD.depthErrorCurr;
		theCMD.depthErrorCurr = theDatabase.depthSetPoint - theDatabase.sensorDepth;
		theCMD.depthErrorDiff = theCMD.depthErrorCurr - theCMD.depthErrorPrev;
		theCMD.depthErrorSum += theCMD.depthErrorCurr;

		/* motors 1 and 6 control yaw and sway */

		theDatabase.pwm[0] = 512 + (theDatabase.cSway)*(theDatabase.swayVelSetPoint);
		theDatabase.pwm[0] += (theDatabase.kpYaw)*(theCMD.yawErrorCurr);
		theDatabase.pwm[0] += (theDatabase.kdYaw)*(theCMD.yawErrorDiff);
		theDatabase.pwm[0] += ((theDatabase.kiYaw)*(theCMD.yawErrorDiff) >> KI_DIV);
		PWM_CAP(theDatabase.pwm[0]);

		theDatabase.pwm[5] = 512 - (theDatabase.cSway)*(theDatabase.swayVelSetPoint);
		theDatabase.pwm[5] -= (theDatabase.kpYaw)*(theCMD.yawErrorCurr);
		theDatabase.pwm[5] -= (theDatabase.kdYaw)*(theCMD.yawErrorDiff);
		theDatabase.pwm[5] -= ((theDatabase.kiYaw)*(theCMD.yawErrorDiff) >> KI_DIV);
		PWM_CAP(theDatabase.pwm[5]);

		/* motors 2 and 5 control surge */
		
		theDatabase.pwm[1] = 512 + (theDatabase.cSurge)*(theDatabase.surgeVelSetPoint);
		theDatabase.pwm[4] = 512 - (theDatabase.cSurge)*(theDatabase.surgeVelSetPoint);
		PWM_CAP(theDatabase.pwm[1]);
		PWM_CAP(theDatabase.pwm[4]);

		/* motors 3 and 4 control depth */

		theDatabase.pwm[2] = 512 + (theDatabase.kpDepth)*(theCMD.depthErrorCurr);
		theDatabase.pwm[2] += (theDatabase.kdDepth)*(theCMD.depthErrorDiff);
		theDatabase.pwm[2] += ((theDatabase.kiDepth)*(theCMD.depthErrorDiff) >> KI_DIV);
		PWM_CAP(theDatabase.pwm[2]);

		theDatabase.pwm[3] = 512 + (theDatabase.kpDepth)*(theCMD.depthErrorCurr);
		theDatabase.pwm[3] -= (theDatabase.kdDepth)*(theCMD.depthErrorDiff);
		theDatabase.pwm[3] -= ((theDatabase.kiDepth)*(theCMD.depthErrorDiff) >> KI_DIV);
		PWM_CAP(theDatabase.pwm[3]);
	}

	REG_MOTOR_1_PWM = theDatabase.pwm[0];
	REG_MOTOR_2_PWM = theDatabase.pwm[1];
	REG_MOTOR_3_PWM = theDatabase.pwm[2];
	REG_MOTOR_4_PWM = theDatabase.pwm[3];
	REG_MOTOR_5_PWM = theDatabase.pwm[4];
	REG_MOTOR_6_PWM = theDatabase.pwm[5];

}

void controllerReset(void) {
theCMD.yawErrorCurr = 0;
theCMD.yawErrorPrev = 0;
theCMD.yawErrorSum = 0;
theCMD.yawErrorDiff = 0;

theCMD.depthErrorCurr = 0;
theCMD.depthErrorPrev = 0;
theCMD.depthErrorSum = 0;
theCMD.depthErrorDiff = 0;
}
