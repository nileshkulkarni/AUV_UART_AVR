#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include "../../common/utils.h"
#include "../../common/system_config.h"



#define NO_DATA 0x00

#define PSB_MCB_BAUD_UBRR ((PSB_FOSC/PSB_MCB_BAUD/8)-1)
#define PRESSURE_SENSOR_OCR (PSB_FOSC/PRESSURE_SENSOR_FREQ/1024)
#define TOGGLE(REG) REG=0xFF;static int abc;if(abc==0){REG=0xFF;abc=1;}else{REG=0x00;abc=0;}

void uartInit(void);
void put_c(uint8_t a);
void put_s(uint8_t * buffer, int bufferlen);


/* Timer for motion controller frequency */
void timerInit(void);

/* ADC for the pressure sensor */
void adcInit(void);
uint16_t adcSample(void);

#define REG_UBRRH UBBR3H
#define REG_UBRRL UBBR3L
#define REG_UCSRA UCSR3A
#define REG_UCSRB UCSR3B
#define REG_UCSRC UCSR3C
#define REG_U2X U2X3
#define REG_RXCIE RXCIE3
#define REG_RXEN RXEN3
#define REG_TXEN TXEN3

#endif
