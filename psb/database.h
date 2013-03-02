#ifndef DATABASE_H
#define DATABSE_H

#include <stdint.h>
struct database {
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

#endif
