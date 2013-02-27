#ifndef UART
#define UART
#include <avr/io.h>
typedef uint8_t bool;
#define true 1
#define false 0


void uart_init(uint16_t ubrr);
void put_c(unsigned char a);
void put_s(char * buffer, int bufferlen);
unsigned char get_c();
#endif
