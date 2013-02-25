#include <stdio.h>
#include <stdint.h>
#define NUM_BITS        (8)


uint16_t calculateChecksum(char *data)
{

	int length = sizeof (data) /sizeof(data[0]);

    uint16_t checksum = 0;
    uint8_t  bit_index = 0;
    uint8_t  bit_value = 0;
    char dummy;
	int i;
	for(i =0;i<length;i++){
		dummy = data[i];
		checksum = checksum ^ dummy;	
	}	
   return ( checksum );
}


int getInt(char * data){
		int length = sizeof(data) / sizeof(data[0]);
		int i=0;
		int no=0;
		for(i=0;i<length;i++){
			no = no* 10 + ((int)data[0] - 48);
		}

		return no;
}




/*
int main()
{
        uint8_t         return_value = 0;
        uint8_t         source_data = 0xF3;
        uint32_t        transfer_data = 0;
        uint16_t        checksum = 0;
		char A[3] = "ABC";
        checksum = calculate_checksum(A );

        printf( "\nChecksum calculated = %x",checksum );

	
       		
        return ( 0 );
	
}
*/
