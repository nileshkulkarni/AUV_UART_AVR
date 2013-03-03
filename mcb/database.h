#ifndef DATABASE_H
#define DATABSE_H

#include <stdint.h>
struct mcb_database {

/*calibration parameters*/
uint8_t kpYaw,kdYaw,kiYaw;
uint8_t kpDepth,kdDepth,kiDepth;
uint8_t cSurge, cSway;
/*sensor readings*/
uint16_t sensorYaw;
uint16_t sensorDepth;
/*set points*/
uint16_t depthSetPoint;
uint16_t yawSetPoint;
uint8_t surgeVelSetPoint;
uint8_t swayVelSetPoint;

/*etc*/
uint16_t pwm[6];
uint8_t mode;
uint8_t control_validity;

/* psb related */
uint8_t psbMode;
uint16_t psbIntercept;
uint8_t psbSlope;
uint8_t psbAdcData;

};


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
#define MCB_SBC_DEPTH_SET_POINT_POS 11
#define MCB_SBC_YAW_SET_POINT_POS 13
#define MCB_SBC_SURGE_VEL_SET_POINT_POS 15
#define MCB_SBC_SWAY_VEL_SET_POINT_POS 16
#define MCB_SBC_MODE_POS 17
#define MCB_SBC_PSB_MODE_POS 18
#define MCB_SBC_CONTROL_VALIDITY_POS 19

/* to be sent from MCB to SBC*/
#define MCB_SBC_SENSOR_DEPTH_POS 1
#define MCB_SBC_M_1_PWM_POS 3
#define MCB_SBC_M_2_PWM_POS 5
#define MCB_SBC_M_3_PWM_POS 7
#define MCB_SBC_M_4_PWM_POS 9
#define MCB_SBC_M_5_PWM_POS 11
#define MCB_SBC_M_6_PWM_POS 13
#define MCB_SBC_DEBUG_1_POS 15
#define MCB_SBC_DEBUG_2_POS 16
#define MCB_SBC_DEBUG_3_POS 17
#define MCB_SBC_DEBUG_4_POS 18
#define MCB_SBC_DEBUG_5_POS 19
#define MCB_SBC_DEBUG_6_POS 20

/* MCB modes */
#define MCB_MODE_CONTROL 1
#define MCB_MODE_SET_YAW_PARAMETERS 2
#define MCB_MODE_SET_DEPTH_PARAMETERS 3
#define MCB_MODE_SET_SWAY_PARAMETERS 4
#define MCB_MODE_SET_SURGE_PARAMETERS 5
#define MCB_MODE_SET_PSB_MODE 6

#define MCB_VALID_YAW_CONTROL 0x01
#define MCB_VALID_DEPTH_CONTROL 0x02
#define MCB_VALID_SWAY_CONTROL 0x04
#define MCB_VALID_SURGE_CONTROL 0x08

/*special bytes*/

void updateSbcTransmitBuffer(void);
void updateSbcDatabase(void);
void updatePsbTransmitBuffer(void);
void updatePsbDatabase(void);

#endif
