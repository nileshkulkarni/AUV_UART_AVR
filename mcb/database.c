#include "database.h"
#include "hw/hw.h"

extern char sbcTransmitBuffer[MCB_SBC_BUFFER_SIZE];
extern char sbcReceiveBuffer[MCB_SBC_BUFFER_SIZE];
extern struct database theDatabase;
/*
Format of the transmit buffer is as follows:

kpYaw
kdYaw
kiYaw
kpDepth
kdDepth
kiDepth
cSurge
cSway
sensorDepth
sensorYaw
depthSetPoint
yawSetPoint
swayVelSetPoint
surgeVelSetPoint
pwm[6]
mode
validity

the 'mode' entry can take the possible values:

'1' = depth control
'2' = yaw control
'3' = depth + yaw control
'4' = reach set point
'5' = nfs style


the 'validity' byte is to be interpreted bit wise. validity byte corressponds to information that tells which data in the message is worth interpreting. define bit wise operations for the same.


*/

void updateTransmitBuffer (void) {
sbcTransmitBuffer[SENSOR_DEPTH_POS] = theDatabase.sensorDepth;

sbcTransmitBuffer[M_1_PWM] = theDatabase.pwm[0] >> 8;
sbcTransmitBuffer[M_1_PWM+1] = theDatabase.pwm[0];

sbcTransmitBuffer[M_2_PWM] = theDatabase.pwm[1] >> 8;
sbcTransmitBuffer[M_2_PWM+1] = theDatabase.pwm[1];

sbcTransmitBuffer[M_3_PWM] = theDatabase.pwm[2] >> 8;
sbcTransmitBuffer[M_3_PWM+1] = theDatabase.pwm[2];

sbcTransmitBuffer[M_4_PWM] = theDatabase.pwm[3] >> 8;
sbcTransmitBuffer[M_4_PWM+1] = theDatabase.pwm[3];

sbcTransmitBuffer[M_5_PWM] = theDatabase.pwm[4] >> 8;
sbcTransmitBuffer[M_5_PWM+1] = theDatabase.pwm[4];

sbcTransmitBuffer[M_6_PWM] = theDatabase.pwm[5] >> 8;
sbcTransmitBuffer[M_6_PWM+1] = theDatabase.pwm[5];

sbcTransmitBuffer[DEBUG_1] = 'x';
sbcTransmitBuffer[DEBUG_2] = 'x';
sbcTransmitBuffer[DEBUG_3] = 'x';
sbcTransmitBuffer[DEBUG_4] = 'x';
sbcTransmitBuffer[DEBUG_5] = 'x';
sbcTransmitBuffer[DEBUG_6] = 'x';

}


void updateDatabase (void) {

theDatabase.validity = sbcReceiveBuffer[VALIDITY_POS];
	if(theDatabase.validity & YAW_PID_VALID) {
		theDatabase.kpYaw = sbcReceiveBuffer[KP_YAW_POS];
		theDatabase.kdYaw = sbcReceiveBuffer[KD_YAW_POS];
		theDatabase.kiYaw = sbcReceiveBuffer[KI_YAW_POS];
	}
	if(theDatabase.validity & DEPTH_PID_VALID) {
		theDatabase.kpDepth = sbcReceiveBuffer[KP_DEPTH_POS];
		theDatabase.kdDepth = sbcReceiveBuffer[KD_DEPTH_POS];
		theDatabase.kiDepth = sbcReceiveBuffer[KI_DEPTH_POS];
	}
	if(theDatabase.validity & VEL_CALIB_VALID) {
		theDatabase.cSurge = sbcReceiveBuffer[C_SURGE_POS];
		theDatabase.cSway = sbcReceiveBuffer[C_SWAY_POS];
	}
	if(theDatabase.validity & YAW_SET_POINT_VALID) {
		theDatabase.yawSetPoint = sbcReceiveBuffer[YAW_SET_POINT_POS];
	}
	if(theDatabase.validity & DEPTH_SET_POINT_VALID) {
		theDatabase.depthSetPoint = sbcReceiveBuffer[DEPTH_SET_POINT_POS];
	}
	if(theDatabase.validity & YAW_SENSOR_DATA_VALID) {
		theDatabase.yawSetPoint = sbcReceiveBuffer[SENSOR_DEPTH_POS];
	}
	if(theDatabase.validity & SURGE_VEL_SET_POINT_VALID) {
		theDatabase.surgeVelSetPoint = sbcReceiveBuffer[SURGE_VEL_SET_POINT_POS];
		}
	if(theDatabase.validity & SWAY_VEL_SET_POINT_VALID) {
		theDatabase.swayVelSetPoint = sbcReceiveBuffer[SWAY_VEL_SET_POINT_POS];
		}


}
