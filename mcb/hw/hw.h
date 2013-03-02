
#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include "../../common/utils.h"
#include "../../common/system_config.h"



#define NO_DATA 0x00

#define MCB_SBC_BAUD_UBRR ((MCB_FOSC/MCB_SBC_BAUD/8)-1)
#define MOTION_CONTROLLER_OCR (MCB_FOSC/MOTION_CONTROLLER_FREQ/1024)

void uartInit(void);
void put_c(uint8_t a);
void put_s(uint8_t * buffer, int bufferlen);


/* Timer for motion controller frequency */
void timerInit(void);

/* ADC for the pressure sensor */
void adcInit(void);
void adcStartSampling(void);

#endif
