#ifndef DATABASE_H
#define DATABASE_H

#include <stdint.h>
struct database {
uint8_t intercept;
uint8_t slope;
uint8_t mode;
uint16_t adcData;
uint16_t depth;
};


void updateTransmitBuffer(void);
void updateDatabase(void);

/* to be sent from MCB to PSB */
#define PSB_MODE_POS 1

/* to be sent from PSB to MCB */
#define DEPTH_POS 1
#define ADC_DATA_POS 3
#define INTERCEPT_POS 5
#define SLOPE_POS 6

/* etc */
#define CALIBRATE_INTERCEPT 0x61

#endif
