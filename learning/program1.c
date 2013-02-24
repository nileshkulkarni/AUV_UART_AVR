#include
int main(void) {
	DDRD = 0x01;
	PORTD = 0x01;
	while (1) { /* do nothing */ }
}
