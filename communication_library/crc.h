/* 'data' is a pointer to a global variable (mutable) of fixed size. 'length' is size of meaningful data in the global variable.

Lets fix a standard. Assume we are using the 16-bit CRC checksum.
message_length = x
crc_bits_length = y
global array of data is assumed as x+y
*/
#include <stdint.h>

#define CRC_POLYNOMIAL 0xAB
//#define CRC_POLYNOMIAL 0x12345678
#define CRC_MESSAGE_BIT_LENGTH 16
#define CRC_POLYNOMIAL_BIT_LENGTH 8
#define CRC_PACKET_LENGTH ((CRC_MESSAGE_BIT_LENGTH + CRC_POLYNOMIAL_BIT_LENGTH)/8)
#define TRUE 0
#define FALSE 1

/*
crcEncrypt would modify the global array 'data' and append checkbits to it.
*/
void crc8Encrypt(uint8_t* table);

/*
it returns the payload length
*/
uint8_t crc8Decrypt(uint8_t* table);

