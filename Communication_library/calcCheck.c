#include <stdio.h>
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
#define NUM_BITS        (8)


uint16_t calculate_checksum(char *data)
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

uint8_t set_transfer_data( uint32_t *dest_data , const uint8_t src_data , const uint16_t checksum )
{
    uint8_t return_value = 0;
    *dest_data = checksum << NUM_BITS | src_data ;
    return ( return_value );
}

int main()
{
        uint8_t         return_value = 0;
        uint8_t         source_data = 0xF3;
        uint32_t        transfer_data = 0;
        uint16_t        checksum = 0;
		char A[3] = "ABC";
        checksum = calculate_checksum(A );

        printf( "\nChecksum calculated = %x",checksum );

//        return_value = set_transfer_data( &transfer_data,source_data,checksum );
/*
        if( 0 == return_value )
        {
            printf( "\nChecksum added successfully; transfer_data = %x",
                    transfer_data );
        }
        else
        {
            printf( "\nError adding checksum" );
        }
		*/
        return ( 0 );

}