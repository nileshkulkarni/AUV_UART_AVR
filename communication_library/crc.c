#include "crc.h"
#include <stdio.h>


void crc32Encrypt(uint32_t* crc_table) {

int i=0;
uint32_t table[CRC_PACKET_LENGTH];
for (i=0;i<CRC_PACKET_LENGTH;i++) {
	table[i] = crc_table[i];
}


//table[CRC_PACKET_LENGTH-1] = 0x0000;
uint32_t temp_upper, temp_lower, temp;

	for (i=0;i<CRC_PACKET_LENGTH-1;i++) {
		uint32_t j = 0;
		for (j=0;j<32;j++) {
			//printf("%d,%x %x %x old\n",j,table[0],table[1],table[2]);
			if (table[i] & (0x80000000 >> j)) {
			temp_upper = table[i] << j;
			if(j==0) {
				temp_lower = 0x00000000;
			} else {
				temp_lower = table[i+1] >> (32-j);
			}
			temp = temp_upper + temp_lower;
			temp = temp ^ CRC_POLYNOMIAL;
			if(j==0) {
				table[i] =  (temp >> j);
				table[i+1] = (table[i+1] & (0xFFFFFFFF >> j)) | (temp << (32-j));
			} else {
				table[i] = (table[i] & (0xFFFFFFFF << (32-j))) | (temp >> j);
				table[i+1] = (table[i+1] & (0xFFFFFFFF >> j)) | (temp << (32-j));
			}
			//printf("%d,%x %x %x\n",j,table[0],table[1],table[2]);
			}
		}
	}
crc_table[CRC_PACKET_LENGTH-1] = table[CRC_PACKET_LENGTH-1];
}


void crc32Decrypt(uint32_t* table) {

}
