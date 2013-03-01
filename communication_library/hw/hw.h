
#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include "utils.h"
#include "system_config.h"



#define NO_DATA 0x00

#define MYUBRR ((FOSC/BAUD/8)-1)

void uartInit(uint16_t ubrr);
void put_c(uint8_t a);
void put_s(uint8_t * buffer, int bufferlen);


/* Timer for motion controller frequency */
void timerInit(void);

/* ADC for the pressure sensor */
void adcInit(void);
void adcStartSampling(void);

#endif
