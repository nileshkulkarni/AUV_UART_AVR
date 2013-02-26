#include "crc.h"
#include <stdio.h>

uint32_t table[CRC_PACKET_LENGTH];


int main() {

table[0] = 0x432B6719;
table[1] = 0x12345678;
table[2] = 0x00000000;

int j = 0;
for (j=0;j<CRC_PACKET_LENGTH;j++) {
	printf("%x\n",table[j]);
}

printf("\n");
crc32Encrypt(table);

for (j=0;j<CRC_PACKET_LENGTH;j++) {
	printf("%x\n",table[j]);
}

printf("\n");
crc32Decrypt(table);

for (j=0;j<CRC_PACKET_LENGTH;j++) {
	printf("%x\n",table[j]);
}

return 0;
}
