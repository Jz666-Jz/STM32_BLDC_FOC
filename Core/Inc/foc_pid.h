#ifndef __PID_H
#define __PID_H
#include "stm32f1xx_hal.h"
typedef struct
{
float Kp;
float Ki;
float Kd;
float setpoint;
float feedback;
float err;
float err_last;
float integral;
float integral_max;
float out;
float out_max;

}PID_TypeDef;

void PID_Init(PID_TypeDef*pid,float kp,float ki,float kd,float int_max,float out_max);
void PID_Reset(PID_TypeDef*pid);
float PID_Pos_Calc(PID_TypeDef*pid,float fb);
#endif
