#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include "../../common/utils.h"
#include "../../common/system_config.h"



#define NO_DATA 0x00

#define MCB_SBC_BAUD_UBRR ((MCB_FOSC/MCB_SBC_BAUD/8)-1)
#define PSB_MCB_BAUD_UBRR ((MCB_FOSC/PSB_MCB_BAUD/8)-1)

#define MOTION_CONTROLLER_OCR (MCB_FOSC/MOTION_CONTROLLER_FREQ/1024)

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


#define REG_PSB_UBRRH UBRR1H
#define REG_PSB_UBRRL UBRR1L
#define REG_PSB_UCSRA UCSR1A
#define REG_PSB_UCSRB UCSR1B
#define REG_PSB_UCSRC UCSR1C
#define REG_PSB_U2X U2X1
#define REG_PSB_RXCIE RXCIE1
#define REG_PSB_RXEN RXEN1
#define REG_PSB_TXEN TXEN1
#define REG_PSB_UDRE UDRE1
#define REG_PSB_UDR UDR1
#define REG_PSB_RXC RXC1 
#define REG_PSB_UCSZ0 UCSZ10
#define REG_PSB_UCSZ1 UCSZ11
#define REG_PSB_USART_RX_vect USART1_RX_vect

#define REG_FREQ_TCCRB TCCR1B
#define REG_FREQ_CS0 CS10
#define REG_FREQ_CS1 CS11
#define REG_FREQ_CS2 CS12
#define REG_FREQ_OCRAH OCR1AH
#define REG_FREQ_OCRAL OCR1AL
#define REG_FREQ_TIMSK TIMSK1
#define REG_FREQ_TIFR TIFR1
#define REG_FREQ_OCIEA OCIE1A
#define REG_FREQ_OCFA OCF1A
#define REG_FREQ_TCNT TCNT1
#define REG_FREQ_TIMER_COMPA_vect TIMER1_COMPA_vect

#define REG_MOTOR_1_OCR OCR3A
#define REG_MOTOR_2_OCR OCR3B
#define REG_MOTOR_3_OCR OCR3C

#define REG_MOTOR_4_OCR OCR4A
#define REG_MOTOR_5_OCR OCR4B
#define REG_MOTOR_6_OCR OCR4C

#endif
