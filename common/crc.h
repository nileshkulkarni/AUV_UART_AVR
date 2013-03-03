/* 'data' is a pointer to a global variable (mutable) of fixed size. 'length' is size of meaningful data in the global variable.

Lets fix a standard. Assume we are using the 16-bit CRC checksum.
message_length = x
crc_bits_length = y
global array of data is assumed as x+y
*/
#ifndef CRC_H
#define CRC_H

#include <stdint.h>
#include "utils.h"
#include "system_config.h"

#define CRC_POLYNOMIAL 0xAB
#define DATA_RECEIVED_TRUE 0xAA
#define DATA_RECEIVED_FALSE 0xBB

/*
crcEncrypt would modify the global array 'data' and append checkbits to it.
*/
void crc8Encrypt(uint8_t* table,uint8_t table_length);

/*
it returns the payload length
*/
uint8_t crc8Decrypt(uint8_t* table,uint8_t table_length);

#endif