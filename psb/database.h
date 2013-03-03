#ifndef PSB_DATABASE_H
#define PSB_DATABASE_H

#include <stdint.h>
struct psb_database {
uint8_t intercept;
uint8_t slope;
uint8_t mode;
uint16_t adcData;
uint16_t depth;
};


void updateTransmitBuffer(void);
void updateDatabase(void);

/* to be sent from MCB to PSB */
#define PSB_MCB_MODE_POS 1

/* to be sent from PSB to MCB */
#define PSB_MCB_DEPTH_POS 1
#define PSB_MCB_ADC_DATA_POS 3
#define PSB_MCB_INTERCEPT_POS 5
#define PSB_MCB_SLOPE_POS 6

/* etc */
#define PSB_CALIBRATE_INTERCEPT 0x61

#endif
