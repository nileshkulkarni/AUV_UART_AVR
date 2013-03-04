#include <avr/io.h>
#include <avr/interrupt.h>
#include "hw.h"


extern volatile bool runController;
extern volatile bool pingPsb;

void timerInit(void) {
/* motion controller frequency */
/* prescaler = 1024 */
REG_MC_FREQ_TCCRB = (1 << REG_MC_FREQ_CS2) | (1 << REG_MC_FREQ_CS0);
REG_MC_FREQ_OCRAH = (MOTION_CONTROLLER_OCR & 0xFF00) >> 8;
REG_MC_FREQ_OCRAL = MOTION_CONTROLLER_OCR & 0x00FF;
/* enabling compare match interrupts */
REG_MC_FREQ_TIMSK = (1 << REG_MC_FREQ_OCIEA);
REG_MC_FREQ_TIFR = (1 << REG_MC_FREQ_OCFA);
/* begin timer */
REG_MC_FREQ_TCNT = 0;

/* psb communication frequency */
/* prescaler = 1024 */
REG_PSB_COMM_FREQ_TCCRB = (1 << REG_PSB_COMM_FREQ_CS2) | (1 << REG_PSB_COMM_FREQ_CS0);
REG_PSB_COMM_FREQ_OCRAH = (PSB_COMMUNICATION_OCR & 0xFF00) >> 8;
REG_PSB_COMM_FREQ_OCRAL = PSB_COMMUNICATION_OCR & 0x00FF;
/* enabling compare match interrupts */
REG_PSB_COMM_FREQ_TIMSK = (1 << REG_PSB_COMM_FREQ_OCIEA);
REG_PSB_COMM_FREQ_TIFR = (1 << REG_PSB_COMM_FREQ_OCFA);
/* begin timer */
REG_PSB_COMM_FREQ_TCNT = 0;

/* pwm generation */
DDRE = 0xFF;
DDRH = 0xFF;
TCCR4A = (1 << WGM41)|(1 << WGM40)|(1 << COM4A1)|(1 << COM4B1)|(1 << COM4C1);
TCCR4B = (1 << CS40);
TCCR3A = (1 << WGM31)|(1 << WGM30)|(1 << COM3A1)|(1 << COM3B1)|(1 << COM3C1);
TCCR3B = (1 << CS30);
REG_MOTOR_1_PWM = 512;
REG_MOTOR_2_PWM = 512;
REG_MOTOR_3_PWM = 512;
REG_MOTOR_4_PWM = 512;
REG_MOTOR_5_PWM = 512;
REG_MOTOR_6_PWM = 512;
}

ISR (REG_MC_FREQ_TIMER_COMPA_vect) {
/* simulating CTC mode by forcing TCNT1 = 0 */
REG_MC_FREQ_TCNT = 0;
runController = TRUE;
}


ISR (REG_PSB_COMM_FREQ_TIMER_COMPA_vect) {
/* simulating CTC mode by forcing TCNT1 = 0 */
REG_PSB_COMM_FREQ_TCNT = 0;
pingPsb = TRUE;
}

