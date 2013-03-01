#ifndef DATABASE_H
#define DATABSE_H

#include <stdint.h>
struct database {

/*calibration parameters*/
uint8_t kpYaw,kdYaw,kiYaw;
uint8_t kpDepth,kdDepth,kiDepth;
uint8_t cSurge, cSway;
/*sensor readings*/
uint8_t sensorYaw;
uint16_t sensorDepth;
/*set points*/
uint8_t depthSetPoint, yawSetPoint;
uint8_t surgeVelSetPoint, swayVelSetPoint;

/*etc*/
uint16_t pwm[6];
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

/*special bytes*/

/* to be sent from SBC to MCU */
#define KP_YAW_POS 1
#define KD_YAW_POS 2
#define KI_YAW_POS 3
#define KP_DEPTH_POS 4
#define KD_DEPTH_POS 5
#define KI_DEPTH_POS 6
#define C_SURGE_POS 7
#define C_SWAY_POS 8
#define SENSOR_YAW_POS 9
#define DEPTH_SET_POINT_POS 10
#define YAW_SET_POINT_POS 11
#define SURGE_VEL_SET_POINT_POS 12
#define SWAY_VEL_SET_POINT_POS 13
#define MODE_POS 14
#define VALIDITY_POS 15

/* to be sent from MCB to SBC*/
#define SENSOR_DEPTH_POS 1
#define M_1_PWM 2
#define M_2_PWM 4
#define M_3_PWM 6
#define M_4_PWM 8
#define M_5_PWM 10
#define M_6_PWM 12
#define DEBUG_1 14
#define DEBUG_2 15
#define DEBUG_3 16
#define DEBUG_4 17
#define DEBUG_5 18
#define DEBUG_6 19

void updateTransmitBuffer(void);
void updateDatabase(void);

#endif
