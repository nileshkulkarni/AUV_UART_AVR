#include<avr/io.h>
//#include<compat\deprecated.h>   
#include<avr/interrupt.h>
#include<util/delay.h>        
#include<inttypes.h>    
#include<math.h>
#include <avr/pgmspace.h>
void main (void)
{
  uint8_t x=0;
  DDRA=0XFF;DDRC=0XFF;DDRE=0xff;PORTC=0xff;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
   PORTE=0XFF;
  

   
   UBRR2=95;                         //baud RATE 9600
   UCSR2C=0B00000110;
    if(UCSR2A & (1<<RXC2))          //check if RXC0 flag is set, clear before enabling RXIE0
      UCSR2A&=(1<<RXC2);   
   UCSR2B=0B00011000;	             //Enable transmitter and reciever and also enable recieve interrupt  
   _delay_ms(2000);
    
   UDR2='U';   



while(1)
 {
   while(!(UCSR2A&(1<<RXC2)))
     {
	 // PORTE=0xff;
	 } 
if(x=='k')
while(1)
{}
x=UDR2;
  PORTA=0XF0;
//  PORTA=0X0f;
  _delay_ms(300);
while(!(UCSR2A&(1<<UDRE2)))
      {}

      UDR2='U';
  PORTA=0X0F;

//_delay_ms(100);
 
 }   
} 
