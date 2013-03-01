#include "database.h"
#include "hw/hw.h"

extern char uartTransmitBuffer[UART_BUFFER_SIZE];
extern char uartReceiveBuffer[UART_BUFFER_SIZE];
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
uartTransmitBuffer[SENSOR_DEPTH_POS] = theDatabase.sensorDepth;
uartTransmitBuffer[M_1_PWM] = theDatabase.pwm[0];
uartTransmitBuffer[M_2_PWM] = theDatabase.pwm[1];
uartTransmitBuffer[M_3_PWM] = theDatabase.pwm[2];
uartTransmitBuffer[M_4_PWM] = theDatabase.pwm[3];
uartTransmitBuffer[M_5_PWM] = theDatabase.pwm[4];
uartTransmitBuffer[M_6_PWM] = theDatabase.pwm[5];

}


void updateDatabase (void) {

theDatabase.validity = uartReceiveBuffer[VALIDITY_POS];
	if(theDatabase.validity & YAW_PID_VALID) {
		theDatabase.kpYaw = uartReceiveBuffer[KP_YAW_POS];
		theDatabase.kdYaw = uartReceiveBuffer[KD_YAW_POS];
		theDatabase.kiYaw = uartReceiveBuffer[KI_YAW_POS];
	}
	if(theDatabase.validity & DEPTH_PID_VALID) {
		theDatabase.kpDepth = uartReceiveBuffer[KP_DEPTH_POS];
		theDatabase.kdDepth = uartReceiveBuffer[KD_DEPTH_POS];
		theDatabase.kiDepth = uartReceiveBuffer[KI_DEPTH_POS];
	}
	if(theDatabase.validity & VEL_CALIB_VALID) {
		theDatabase.cSurge = uartReceiveBuffer[C_SURGE_POS];
		theDatabase.cSway = uartReceiveBuffer[C_SWAY_POS];
	}
	if(theDatabase.validity & YAW_SET_POINT_VALID) {
		theDatabase.yawSetPoint = uartReceiveBuffer[YAW_SET_POINT_POS];
	}
	if(theDatabase.validity & DEPTH_SET_POINT_VALID) {
		theDatabase.depthSetPoint = uartReceiveBuffer[DEPTH_SET_POINT_POS];
	}
	if(theDatabase.validity & YAW_SENSOR_DATA_VALID) {
		theDatabase.yawSetPoint = uartReceiveBuffer[SENSOR_DEPTH_POS];
	}
	if(theDatabase.validity & SURGE_VEL_SET_POINT_VALID) {
		theDatabase.surgeVelSetPoint = uartReceiveBuffer[SURGE_VEL_SET_POINT_POS];
		}
	if(theDatabase.validity & SWAY_VEL_SET_POINT_VALID) {
		theDatabase.swayVelSetPoint = uartReceiveBuffer[SWAY_VEL_SET_POINT_POS];
		}


}
