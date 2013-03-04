#include "database.h"
#include "hw/hw.h"
#include "../psb/database.h"

extern char sbcTransmitBuffer[MCB_SBC_BUFFER_SIZE];
extern char sbcReceiveBuffer[MCB_SBC_BUFFER_SIZE];
extern char psbTransmitBuffer[MCB_SBC_BUFFER_SIZE];
extern char psbReceiveBuffer[MCB_SBC_BUFFER_SIZE];
struct mcb_database theDatabase;

void updateSbcTransmitBuffer (void) {
	sbcTransmitBuffer[MCB_SBC_SENSOR_DEPTH_POS] = theDatabase.sensorDepth>>8;
	sbcTransmitBuffer[MCB_SBC_SENSOR_DEPTH_POS+1] = theDatabase.sensorDepth;

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

	sbcTransmitBuffer[MCB_SBC_DEBUG_1_POS] = theDatabase.cSurge;
	sbcTransmitBuffer[MCB_SBC_DEBUG_2_POS] = theDatabase.cSway;
	sbcTransmitBuffer[MCB_SBC_DEBUG_3_POS] = theDatabase.swayVelSetPoint;
	sbcTransmitBuffer[MCB_SBC_DEBUG_4_POS] = theDatabase.surgeVelSetPoint;
	sbcTransmitBuffer[MCB_SBC_DEBUG_5_POS] = theDatabase.sensorDepth >> 8;
	sbcTransmitBuffer[MCB_SBC_DEBUG_6_POS] = theDatabase.sensorDepth;

}

void updatePsbTransmitBuffer (void) {
psbTransmitBuffer[PSB_MCB_MODE_POS] = theDatabase.psbMode;
}


void updateSbcDatabase (void) {

	theDatabase.mode = sbcReceiveBuffer[MCB_SBC_MODE_POS];
	theDatabase.control_validity = sbcReceiveBuffer[MCB_SBC_CONTROL_VALIDITY_POS];
	switch(theDatabase.mode) {
		case MCB_MODE_CONTROL: {
			controllerReset();
			if (theDatabase.control_validity & MCB_VALID_YAW_CONTROL) {
				theDatabase.yawSetPoint = (sbcReceiveBuffer[MCB_SBC_YAW_SET_POINT_POS+1]) | (sbcReceiveBuffer[MCB_SBC_YAW_SET_POINT_POS] << 8);
			}
			if (theDatabase.control_validity & MCB_VALID_DEPTH_CONTROL) {
				theDatabase.depthSetPoint = (sbcReceiveBuffer[MCB_SBC_DEPTH_SET_POINT_POS+1]) | (sbcReceiveBuffer[MCB_SBC_DEPTH_SET_POINT_POS] << 8);
			}
			if (theDatabase.control_validity & MCB_VALID_SURGE_CONTROL) {
				theDatabase.surgeVelSetPoint = sbcReceiveBuffer[MCB_SBC_SURGE_VEL_SET_POINT_POS];
			}
			if (theDatabase.control_validity & MCB_VALID_SWAY_CONTROL) {
				theDatabase.swayVelSetPoint = sbcReceiveBuffer[MCB_SBC_SWAY_VEL_SET_POINT_POS];
			}
			break;
			}
		case MCB_MODE_SET_YAW_PARAMETERS: {
			theDatabase.kpYaw = sbcReceiveBuffer[MCB_SBC_KP_YAW_POS];
			theDatabase.kdYaw = sbcReceiveBuffer[MCB_SBC_KD_YAW_POS];
			theDatabase.kiYaw = sbcReceiveBuffer[MCB_SBC_KI_YAW_POS];
			break;
			}

		case MCB_MODE_SET_DEPTH_PARAMETERS: {
			theDatabase.kpDepth = sbcReceiveBuffer[MCB_SBC_KP_DEPTH_POS];
			theDatabase.kdDepth = sbcReceiveBuffer[MCB_SBC_KD_DEPTH_POS];
			theDatabase.kiDepth = sbcReceiveBuffer[MCB_SBC_KI_DEPTH_POS];
			break;
			}
		case MCB_MODE_SET_SWAY_PARAMETERS: {
			theDatabase.cSway = sbcReceiveBuffer[MCB_SBC_C_SWAY_POS];
			break;
			}
		case MCB_MODE_SET_SURGE_PARAMETERS: {
			theDatabase.cSurge = sbcReceiveBuffer[MCB_SBC_C_SURGE_POS];
			break;
			}
		case MCB_MODE_SET_PSB_MODE: {
			theDatabase.psbMode = sbcReceiveBuffer[MCB_SBC_PSB_MODE_POS];
			break;
			}
	}
	theDatabase.sensorYaw = (sbcReceiveBuffer[MCB_SBC_SENSOR_YAW_POS+1]) + ((0x00FF & sbcReceiveBuffer[MCB_SBC_SENSOR_YAW_POS]) << 8);


}

void updatePsbDatabase (void) {
	theDatabase.sensorDepth = psbReceiveBuffer[PSB_MCB_DEPTH_POS+1] + (psbReceiveBuffer[PSB_MCB_DEPTH_POS]<<8);	
	theDatabase.psbAdcData = psbReceiveBuffer[PSB_MCB_ADC_DATA_POS+1] + (psbReceiveBuffer[PSB_MCB_ADC_DATA_POS]<<8);
	theDatabase.psbIntercept = psbReceiveBuffer[PSB_MCB_INTERCEPT_POS];
	theDatabase.psbSlope = psbReceiveBuffer[PSB_MCB_SLOPE_POS];	

}
