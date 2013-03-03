#include "database.h"
#include "hw/hw.h"

extern char sbcTransmitBuffer[MCB_SBC_BUFFER_SIZE];
extern char sbcReceiveBuffer[MCB_SBC_BUFFER_SIZE];
struct mcb_database theDatabase;
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
psbMode

the 'mode' entry can take the possible values:

'1' = depth control
'2' = yaw control
'3' = depth + yaw control
'4' = reach set point


the 'validity' byte is to be interpreted bit wise. validity byte corressponds to information that tells which data in the message is worth interpreting. define bit wise operations for the same.


*/

void updateSbcTransmitBuffer (void) {
sbcTransmitBuffer[MCB_SBC_SENSOR_DEPTH_POS] = theDatabase.sensorDepth;

sbcTransmitBuffer[MCB_SBC_M_1_PWM_POS] = theDatabase.pwm[0] >> 8;
sbcTransmitBuffer[MCB_SBC_M_1_PWM_POS+1] = theDatabase.pwm[0];

sbcTransmitBuffer[MCB_SBC_M_2_PWM_POS] = theDatabase.pwm[1] >> 8;
sbcTransmitBuffer[MCB_SBC_M_2_PWM_POS+1] = theDatabase.pwm[1];

sbcTransmitBuffer[MCB_SBC_M_3_PWM_POS] = theDatabase.pwm[2] >> 8;
sbcTransmitBuffer[MCB_SBC_M_3_PWM_POS+1] = theDatabase.pwm[2];

sbcTransmitBuffer[MCB_SBC_M_4_PWM_POS] = theDatabase.pwm[3] >> 8;
sbcTransmitBuffer[MCB_SBC_M_4_PWM_POS+1] = theDatabase.pwm[3];

sbcTransmitBuffer[MCB_SBC_M_5_PWM_POS] = theDatabase.pwm[4] >> 8;
sbcTransmitBuffer[MCB_SBC_M_5_PWM_POS+1] = theDatabase.pwm[4];

sbcTransmitBuffer[MCB_SBC_M_6_PWM_POS] = theDatabase.pwm[5] >> 8;
sbcTransmitBuffer[MCB_SBC_M_6_PWM_POS+1] = theDatabase.pwm[5];

sbcTransmitBuffer[MCB_SBC_DEBUG_1_POS] = 'x';
sbcTransmitBuffer[MCB_SBC_DEBUG_2_POS] = 'x';
sbcTransmitBuffer[MCB_SBC_DEBUG_3_POS] = 'x';
sbcTransmitBuffer[MCB_SBC_DEBUG_4_POS] = 'x';
sbcTransmitBuffer[MCB_SBC_DEBUG_5_POS] = 'x';
sbcTransmitBuffer[MCB_SBC_DEBUG_6_POS] = 'x';

}



void updateSbcDatabase (void) {

theDatabase.validity = sbcReceiveBuffer[MCB_SBC_VALIDITY_POS];
	if(theDatabase.validity & MCB_SBC_YAW_PID_VALID) {
		theDatabase.kpYaw = sbcReceiveBuffer[MCB_SBC_KP_YAW_POS];
		theDatabase.kdYaw = sbcReceiveBuffer[MCB_SBC_KD_YAW_POS];
		theDatabase.kiYaw = sbcReceiveBuffer[MCB_SBC_KI_YAW_POS];
	}
	if(theDatabase.validity & MCB_SBC_DEPTH_PID_VALID) {
		theDatabase.kpDepth = sbcReceiveBuffer[MCB_SBC_KP_DEPTH_POS];
		theDatabase.kdDepth = sbcReceiveBuffer[MCB_SBC_KD_DEPTH_POS];
		theDatabase.kiDepth = sbcReceiveBuffer[MCB_SBC_KI_DEPTH_POS];
	}
	if(theDatabase.validity & MCB_SBC_VEL_CALIB_VALID) {
		theDatabase.cSurge = sbcReceiveBuffer[MCB_SBC_C_SURGE_POS];
		theDatabase.cSway = sbcReceiveBuffer[MCB_SBC_C_SWAY_POS];
	}
	if(theDatabase.validity & MCB_SBC_YAW_SET_POINT_VALID) {
		theDatabase.yawSetPoint = sbcReceiveBuffer[MCB_SBC_YAW_SET_POINT_POS];
	}
	if(theDatabase.validity & MCB_SBC_DEPTH_SET_POINT_VALID) {
		theDatabase.depthSetPoint = sbcReceiveBuffer[MCB_SBC_DEPTH_SET_POINT_POS];
	}
	if(theDatabase.validity & MCB_SBC_YAW_SENSOR_DATA_VALID) {
		theDatabase.yawSetPoint = sbcReceiveBuffer[MCB_SBC_SENSOR_DEPTH_POS];
	}
	if(theDatabase.validity & MCB_SBC_SURGE_VEL_SET_POINT_VALID) {
		theDatabase.surgeVelSetPoint = sbcReceiveBuffer[MCB_SBC_SURGE_VEL_SET_POINT_POS];
	}
	if(theDatabase.validity & MCB_SBC_SWAY_VEL_SET_POINT_VALID) {
		theDatabase.swayVelSetPoint = sbcReceiveBuffer[MCB_SBC_SWAY_VEL_SET_POINT_POS];
	}
	if(theDatabase.validity & MCB_SBC_PSB_MODE_VALID) {
		theDatabase.psbMode = sbcReceiveBuffer[MCB_SBC_PSB_MODE_POS];
	}


}
