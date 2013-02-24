#include <avr/io.h>
#include <util/delay.h>

int main(void){
	DDRD=0b11111111;
	PORTA=0xFF;
	return 0;
}
