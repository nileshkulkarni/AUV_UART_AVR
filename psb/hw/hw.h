#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include "../../common/utils.h"
#include "../../common/system_config.h"



#define NO_DATA 0x00

#define PSB_MCB_BAUD_UBRR ((PSB_FOSC/PSB_MCB_BAUD/8)-1)
#define PRESSURE_SENSOR_OCR (PSB_FOSC/PRESSURE_SENSOR_FREQ/1024)

void uartInit(void);
void put_c(uint8_t a);
void put_s(uint8_t * buffer, int bufferlen);


/* Timer for motion controller frequency */
void timerInit(void);

/* ADC for the pressure sensor */
void adcInit(void);
uint16_t adcSample(void);

#endif
