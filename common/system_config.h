#ifndef SYSTEM_H
#define SYSTEM_H

#define MCB_FOSC 14745600 
#define PSB_FOSC 14745600 

#define MCB_SBC_BAUD 9600
#define PSB_MCB_BAUD 9600

/* Buffer size is inclusive of the CRC remainder and the correction byte */
#define MCB_SBC_BUFFER_SIZE 20
#define PSB_MCB_BUFFER_SIZE 3

#define MOTION_CONTROLLER_FREQ 20 // in hertz
#define PRESSURE_SENSOR_FREQ 20 // in hertz


#endif
