#ifndef FOC_SVPWM_H
#define FOC_SVPWM_H

#include "stm32f1xx_hal.h"

void SVPWM_Calc(float valpha, float vbeta, float vbus, float *ta, float *tb, float *tc);
void SVPWM_Apply(float ta, float tb, float tc);

#endif
