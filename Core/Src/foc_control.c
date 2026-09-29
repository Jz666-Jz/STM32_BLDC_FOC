#include "foc_control.h"
#include "foc_encoder.h"
#include "foc_math.h"
#include "foc_svpwm.h"
#include "foc_config.h"

 volatile float Uq_ref = 0.0f;
extern volatile float elec_angle;
void foc_high_isr(void)
{
float a,b,uq;
	__disable_irq();
	uq=Uq_ref;
	__enable_irq();
	RevPark_Transform(Ud_ref,uq,elec_angle,&a,&b);
	float ta,tb,tc;
	SVPWM_Calc(a,b,VBUS,&ta,&tb,&tc);
	SVPWM_Apply(ta,tb,tc);


}


