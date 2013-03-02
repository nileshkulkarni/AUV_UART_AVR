#ifndef PRESSURE_H
#define PRESSURE_H

/*
For now, we shall assume a linear model of the pressure sensor.
i.e, 
depth = slope*adcData + intercept
*/

void estimateDepth (void);


#endif
