#ifndef CONTROLLER_H
#define CONTROLLER_H

struct controller_meta_data {
	uint16_t yawErrorCurr;
	uint16_t yawErrorPrev;
	uint16_t yawErrorDiff;
	uint32_t yawErrorSum;
	uint16_t depthErrorCurr;
	uint16_t depthErrorPrev;
	uint16_t depthErrorDiff;
	uint32_t depthErrorSum;
};

void controllerInit(void);
void motionControl();

#define KI_DIV 3

#endif
