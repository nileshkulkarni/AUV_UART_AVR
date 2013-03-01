#ifndef DATABASE_H
#define DATABSE_H

#include <stdint.h>
struct database {

/*calibration parameters*/
uint8_t kpYaw,kdYaw,kiYaw;
uint8_t kpDepth,kdDepth,kiDepth;
uint8_t cSurge, cSway;
/*sensor readings*/
uint8_t sensorDepth, sensorYaw;
/*set points*/
uint8_t depthSetPoint, yawSetPoint;
uint8_t surgeVelSetPoint, swayVelSetPoint;

/*etc*/
uint8_t pwm[6];
uint8_t mode;
uint16_t validity;

};

#define YAW_PID_VALID 0x0001
#define DEPTH_PID_VALID 0x0002
#define VEL_CALIB_VALID 0x0004
#define YAW_SET_POINT_VALID 0x0008
#define DEPTH_SET_POINT_VALID 0x0010
#define YAW_SENSOR_DATA_VALID 0x0020
#define SURGE_VEL_SET_POINT_VALID 0x0040
#define SWAY_VEL_SET_POINT_VALID 0x0080

/* to be sent from SBC to MCU */
#define KP_YAW_POS 0
#define KD_YAW_POS 1
#define KI_YAW_POS 2
#define KP_DEPTH_POS 3
#define KD_DEPTH_POS 4
#define KI_DEPTH_POS 5
#define C_SURGE_POS 6
#define C_SWAY_POS 7
#define SENSOR_YAW_POS 8
#define DEPTH_SET_POINT_POS 9
#define YAW_SET_POINT_POS 10
#define SURGE_VEL_SET_POINT_POS 11
#define SWAY_VEL_SET_POINT_POS 12
#define MODE_POS 13
#define VALIDITY_POS 14

/* to be sent from MCB to SBC*/
#define SENSOR_DEPTH_POS 0
#define M_1_PWM 1
#define M_2_PWM 3
#define M_3_PWM 5
#define M_4_PWM 7
#define M_5_PWM 9
#define M_6_PWM 11
#define DEBUG_1 13
#define DEBUG_2 14
#define DEBUG_3 15
#define DEBUG_4 16
#define DEBUG_5 17
#define DEBUG_6 18

void updateTransmitBuffer(void);
void updateDatabase(void);

#endif
