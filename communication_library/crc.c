#include "crc.h"
#include "utils.h"

void crc8(uint8_t* crc_table) {

uint16_t i=0;
uint8_t table[CRC_PACKET_LENGTH];
uint8_t temp_upper, temp_lower, temp;

	for (i=0;i<CRC_PACKET_LENGTH;i++) {
		table[i] = crc_table[i];
	}

	for (i=0;i<CRC_PACKET_LENGTH-1;i++) {
		uint8_t j = 0;
		for (j=0;j<8;j++) {
			if (table[i] & (0x80 >> j)) {
			temp_upper = table[i] << j;
			if(j==0) {
				temp_lower = 0x00;
			} 
			else {
				temp_lower = table[i+1] >> (8-j);
			}
			temp = temp_upper + temp_lower;
			temp = temp ^ CRC_POLYNOMIAL;
			if(j==0) {
				table[i] =  (temp >> j);
				table[i+1] = (table[i+1] & (0xFF >> j));
			} else {
				table[i] = (table[i] & (0xFF << (8-j))) | (temp >> j);
				table[i+1] = (table[i+1] & (0xFF >> j)) | (temp << (8-j));
			}
			}
		}
	}
crc_table[CRC_PACKET_LENGTH-1] = table[CRC_PACKET_LENGTH-1];
}

void crc8Encrypt(uint8_t* crc_table) {
crc_table[CRC_PACKET_LENGTH-1] = 0x00;
crc8(crc_table);
}


uint8_t crc8Decrypt(uint8_t* crc_table) {
crc8(crc_table);
	if(crc_table[CRC_PACKET_LENGTH-1] == 0x00) {
		return TRUE;
	}
	else {
		return FALSE;;
	}
}
