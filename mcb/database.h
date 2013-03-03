#ifndef DATABASE_H
#define DATABSE_H

#include <stdint.h>
struct mcb_database {

/*calibration parameters*/
uint8_t kpYaw,kdYaw,kiYaw;
uint8_t kpDepth,kdDepth,kiDepth;
uint8_t cSurge, cSway;
/*sensor readings*/
uint8_t sensorYaw;
uint16_t sensorDepth;
/*set points*/
uint16_t depthSetPoint;
uint8_t yawSetPoint;
uint8_t surgeVelSetPoint, swayVelSetPoint;

/*etc*/
uint16_t pwm[6];
uint8_t mode;
uint16_t validity;

/* psb related */
uint8_t psbMode;
uint8_t psbIntercept;
uint8_t psbSlope;
uint8_t psbAdcData;

};

#define MCB_SBC_YAW_PID_VALID 0x0001
#define MCB_SBC_DEPTH_PID_VALID 0x0002
#define MCB_SBC_VEL_CALIB_VALID 0x0004
#define MCB_SBC_YAW_SET_POINT_VALID 0x0008
#define MCB_SBC_DEPTH_SET_POINT_VALID 0x0010
#define MCB_SBC_YAW_SENSOR_DATA_VALID 0x0020
#define MCB_SBC_SURGE_VEL_SET_POINT_VALID 0x0040
#define MCB_SBC_SWAY_VEL_SET_POINT_VALID 0x0080
#define MCB_SBC_PSB_MODE_VALID 0x0100

/*special bytes*/

/* to be sent from SBC to MCU */
#define MCB_SBC_KP_YAW_POS 1
#define MCB_SBC_KD_YAW_POS 2
#define MCB_SBC_KI_YAW_POS 3
#define MCB_SBC_KP_DEPTH_POS 4
#define MCB_SBC_KD_DEPTH_POS 5
#define MCB_SBC_KI_DEPTH_POS 6
#define MCB_SBC_C_SURGE_POS 7
#define MCB_SBC_C_SWAY_POS 8
#define MCB_SBC_SENSOR_YAW_POS 9
#define MCB_SBC_DEPTH_SET_POINT_POS 10
#define MCB_SBC_YAW_SET_POINT_POS 11
#define MCB_SBC_SURGE_VEL_SET_POINT_POS 12
#define MCB_SBC_SWAY_VEL_SET_POINT_POS 13
#define MCB_SBC_MODE_POS 14
#define MCB_SBC_VALIDITY_POS 15
#define MCB_SBC_PSB_MODE_POS 17

/* to be sent from MCB to SBC*/
#define MCB_SBC_SENSOR_DEPTH_POS 1
#define MCB_SBC_M_1_PWM_POS 2
#define MCB_SBC_M_2_PWM_POS 4
#define MCB_SBC_M_3_PWM_POS 6
#define MCB_SBC_M_4_PWM_POS 8
#define MCB_SBC_M_5_PWM_POS 10
#define MCB_SBC_M_6_PWM_POS 12
#define MCB_SBC_DEBUG_1_POS 14
#define MCB_SBC_DEBUG_2_POS 15
#define MCB_SBC_DEBUG_3_POS 16
#define MCB_SBC_DEBUG_4_POS 17
#define MCB_SBC_DEBUG_5_POS 18
#define MCB_SBC_DEBUG_6_POS 19

void updateSbcTransmitBuffer(void);
void updateSbcDatabase(void);
void updatePsbTransmitBuffer(void);
void updatePsbDatabase(void);

#endif
