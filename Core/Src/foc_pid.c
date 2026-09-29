#include "foc_pid.h"

void PID_Init(PID_TypeDef*pid,float kp,float ki,float kd,float int_max,float out_max)
{
 pid->Kp = kp;
	pid->Ki = ki;
	pid->Kd = kd;
	pid->integral_max = int_max;
	pid->out_max = out_max;
	PID_Reset(pid);

}
void PID_Reset(PID_TypeDef*pid)
{
	pid->err = 0;
	pid->err_last=0;
	pid->feedback=0;
	pid->setpoint=0;
	pid->integral=0;
	pid->out=0;
	
	
}

float PID_Pos_Calc(PID_TypeDef*pid,float fb)
{
  pid->feedback = fb;
	pid->err=pid->setpoint-pid->feedback;
	pid->integral+=pid->err;
	if(pid->integral >  pid->integral_max) pid->integral =  pid->integral_max;
    if(pid->integral < -pid->integral_max) pid->integral = -pid->integral_max;

    float p = pid->Kp * pid->err;
    float i = pid->Ki * pid->integral;
    float d = pid->Kd * (pid->err - pid->err_last);

    pid->out = p + i + d;

    
    if(pid->out >  pid->out_max) pid->out =  pid->out_max;
    if(pid->out < -pid->out_max) pid->out = -pid->out_max;

    pid->err_last = pid->err;
    return pid->out;
}





