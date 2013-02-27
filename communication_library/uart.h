#ifndef UART
#define UART
#include <avr/io.h>

typedef uint8_t bool;

#define true 1
#define false 0

#define RECEIVE_BUFFER_SIZE CRC_PACKET_LENGTH
#define TRANSMIT_BUFFER_SIZE CRC_PACKET_LENGTH
#define NO_DATA 0x00

#define MYUBRR ((FOSC/BAUD/8)-1)
#define FOSC 14745600 
void uart_init(uint16_t ubrr);
void put_c(unsigned char a);
void put_s(char * buffer, int bufferlen);
unsigned char get_c();
#endif
