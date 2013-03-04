#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include "../../common/utils.h"
#include "../../common/system_config.h"



#define NO_DATA 0x00

#define MCB_SBC_BAUD_UBRR ((MCB_FOSC/MCB_SBC_BAUD/8)-1)
#define PSB_MCB_BAUD_UBRR ((MCB_FOSC/PSB_MCB_BAUD/8)-1)

#define MOTION_CONTROLLER_OCR (MCB_FOSC/MOTION_CONTROLLER_FREQ/1024)
#define PSB_COMMUNICATION_OCR (MCB_FOSC/PSB_COMMUNICATION_FREQ/1024)

void uartInit(void);
void sbcPutc(uint8_t a);
void sbcPuts(uint8_t * buffer, int bufferlen);


/* Timer for motion controller frequency */
void timerInit(void);

/* ADC for the pressure sensor */
void adcInit(void);
void adcStartSampling(void);

#define REG_SBC_UBRRH UBRR2H
#define REG_SBC_UBRRL UBRR2L
#define REG_SBC_UCSRA UCSR2A
#define REG_SBC_UCSRB UCSR2B
#define REG_SBC_UCSRC UCSR2C
#define REG_SBC_U2X U2X2
#define REG_SBC_RXCIE RXCIE2
#define REG_SBC_RXEN RXEN2
#define REG_SBC_TXEN TXEN2
#define REG_SBC_UDRE UDRE2
#define REG_SBC_UDR UDR2
#define REG_SBC_RXC RXC2 
#define REG_SBC_UCSZ0 UCSZ20
#define REG_SBC_UCSZ1 UCSZ21
#define REG_SBC_USART_RX_vect USART2_RX_vect


#define REG_PSB_UBRRH UBRR3H
#define REG_PSB_UBRRL UBRR3L
#define REG_PSB_UCSRA UCSR3A
#define REG_PSB_UCSRB UCSR3B
#define REG_PSB_UCSRC UCSR3C
#define REG_PSB_U2X U2X3
#define REG_PSB_RXCIE RXCIE3
#define REG_PSB_RXEN RXEN3
#define REG_PSB_TXEN TXEN3
#define REG_PSB_UDRE UDRE3
#define REG_PSB_UDR UDR3
#define REG_PSB_RXC RXC3 
#define REG_PSB_UCSZ0 UCSZ30
#define REG_PSB_UCSZ1 UCSZ31
#define REG_PSB_USART_RX_vect USART3_RX_vect

#define REG_MC_FREQ_TCCRB TCCR1B
#define REG_MC_FREQ_CS0 CS10
#define REG_MC_FREQ_CS1 CS11
#define REG_MC_FREQ_CS2 CS12
#define REG_MC_FREQ_OCRAH OCR1AH
#define REG_MC_FREQ_OCRAL OCR1AL
#define REG_MC_FREQ_TIMSK TIMSK1
#define REG_MC_FREQ_TIFR TIFR1
#define REG_MC_FREQ_OCIEA OCIE1A
#define REG_MC_FREQ_OCFA OCF1A
#define REG_MC_FREQ_TCNT TCNT1
#define REG_MC_FREQ_TIMER_COMPA_vect TIMER1_COMPA_vect

#define REG_PSB_COMM_FREQ_TCCRB TCCR5B
#define REG_PSB_COMM_FREQ_CS0 CS50
#define REG_PSB_COMM_FREQ_CS1 CS51
#define REG_PSB_COMM_FREQ_CS2 CS52
#define REG_PSB_COMM_FREQ_OCRAH OCR5AH
#define REG_PSB_COMM_FREQ_OCRAL OCR5AL
#define REG_PSB_COMM_FREQ_TIMSK TIMSK5
#define REG_PSB_COMM_FREQ_TIFR TIFR5
#define REG_PSB_COMM_FREQ_OCIEA OCIE5A
#define REG_PSB_COMM_FREQ_OCFA OCF5A
#define REG_PSB_COMM_FREQ_TCNT TCNT5
#define REG_PSB_COMM_FREQ_TIMER_COMPA_vect TIMER5_COMPA_vect

#define REG_MOTOR_1_PWM OCR3A
#define REG_MOTOR_2_PWM OCR3B
#define REG_MOTOR_3_PWM OCR3C

#define REG_MOTOR_4_PWM OCR4A
#define REG_MOTOR_5_PWM OCR4B
#define REG_MOTOR_6_PWM OCR4C

#define TOGGLE(REG) REG=0xFF;static int abc;if(abc==0){REG=0xFF;abc=1;}else{REG=0x00;abc=0;}
#endif
