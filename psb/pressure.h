#ifndef PRESSURE_H
#define PRESSURE_H

/*
For now, we shall assume a linear model of the pressure sensor.
i.e, 
depth = slope*adcData + intercept
*/

#define PRESSURE_INTERCEPT 120
#define PRESSURE_SLOPE 6

void estimateDepth(void);
void pressureInit(void);

#endif
