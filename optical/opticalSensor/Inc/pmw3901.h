#ifndef __PWM3901__
#define __PWM3901__
#include "main.h"
#include "spi.h"

#define OPTI_ENABLE 0

uint8_t PMW3901_GetPos(int16_t * dposx, int16_t * dposy);

uint8_t PMW3901_ReadRegister(uint8_t reg);

void PMW3901_WriteRegister(uint8_t reg,uint8_t data);

void PMW3901_Cs(uint8_t p);

uint8_t PMW3901_Init();
#endif