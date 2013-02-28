
#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include "utils.h"
#include "system_config.h"



#define NO_DATA 0x00

#define MYUBRR ((FOSC/BAUD/8)-1)
#define FOSC 14745600 
void uart_init(uint16_t ubrr);
void put_c(unsigned char a);
void put_s(char * buffer, int bufferlen);
unsigned char get_c();
#endif
