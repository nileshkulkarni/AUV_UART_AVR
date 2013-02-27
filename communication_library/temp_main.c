#include "crc.h"
#include <stdio.h>

uint8_t table[CRC_PACKET_LENGTH];


int main() {

table[0] = 0x61;
table[1] = 0x7D;
table[2] = 0x00;

int j = 0;
for (j=0;j<CRC_PACKET_LENGTH;j++) {
	printf("%x\n",table[j]);
}

printf("\n");
crc8Encrypt(table);

for (j=0;j<CRC_PACKET_LENGTH;j++) {
	printf("%x\n",table[j]);
}

printf("\n");
crc8Decrypt(table);

for (j=0;j<CRC_PACKET_LENGTH;j++) {
	printf("%x\n",table[j]);
}

return 0;
}
