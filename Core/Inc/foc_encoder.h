#ifndef __FOC_ENCODER_H
#define __FOC_ENCODER_H
#include "stm32f1xx_hal.h"
#define DT_SPEED 0.001f
#define SPEED_LPF_ALPHA 0.05f
float get_elec_angle(void);
void Encoder_Update(void);

float Run_Offset_Calibration(void);
#endif
