#ifndef UART
#define UART
#include <avr/io.h>
void uart_init(uint16_t ubrr);
void put_c(char a);
void put_s(char * buffer, int bufferlen);




char get_c();
#endif
