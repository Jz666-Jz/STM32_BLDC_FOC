#include "foc_encoder.h"
#include "as5600.h"
#include "foc_math.h"
#include "foc_config.h"
#include "foc_pid.h"
#include "foc_svpwm.h"
static float mech_angle_unwrap=0;
static float mech_angle_norm=0;
float speed_mech=0;
static float speed_filtered=0;
volatile float elec_angle = 0;
extern  PID_TypeDef speed_pid;
extern float speed_target;
extern volatile float Uq_ref;
extern float speed_mech;
extern TIM_HandleTypeDef htim1;
float get_elec_angle(void)
{
int16_t a= AS5600_ReadRaw();
	float b =(float)a/4096.0f*_2PI*7.0f-ELEC_ANGLE_OFFSET;
return b;

}




void Encoder_Update(void)
{
uint16_t raw = AS5600_ReadRaw();
	float new_norm = (float)raw/4096.0f*_2PI;
	
	float delta = new_norm - mech_angle_norm;
	if(delta > PI) delta -=_2PI;
	if(delta < -PI) delta +=_2PI;
	mech_angle_unwrap +=delta;
	mech_angle_norm = new_norm;
	elec_angle = Normalize_Angle(mech_angle_norm*7-ELEC_ANGLE_OFFSET);
	
	float speed_raw = delta/DT_SPEED;
	speed_filtered=speed_filtered*(1-SPEED_LPF_ALPHA)+speed_raw*SPEED_LPF_ALPHA;
	speed_mech = speed_filtered;

	 speed_pid.setpoint = speed_target;
	
	Uq_ref = PID_Pos_Calc(&speed_pid ,speed_mech);




}




float Run_Offset_Calibration(void)
{
    
    HAL_TIM_Base_Stop_IT(&htim1); 
    
    
   
    const float Ud_cal = 2.0f;   
    const uint32_t t_cal = 1000; 
    float theta;
    float a, b;
    float ta, tb, tc;

    // ================= ??1:?????? 0 =================
    uint32_t t0 = HAL_GetTick();
    while(HAL_GetTick() - t0 < t_cal)
    {
        theta = 0.0f;
        // ?Park??:Ud = Ud_cal, Uq = 0
        RevPark_Transform(Ud_cal, 0.0f, theta, &a, &b);
        SVPWM_Calc(a, b, VBUS, &ta, &tb, &tc);
        SVPWM_Apply(ta, tb, tc);
    }
    
    // ????,??PWM(??50%????,??????)
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
    HAL_Delay(500); // ????????,????
    
    // ?????
    uint16_t raw1 = AS5600_ReadRaw();
    float mech1 = (float)raw1 / 4096.0f * _2PI;
    
    // ================= ??2:?????? PI =================
    // ???????,????,?????????????????????!
    t0 = HAL_GetTick();
    while(HAL_GetTick() - t0 < t_cal)
    {
        theta = PI; // ??????
        RevPark_Transform(Ud_cal, 0.0f, theta, &a, &b);
        SVPWM_Calc(a, b, VBUS, &ta, &tb, &tc);
        SVPWM_Apply(ta, tb, tc);
    }
    
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
    HAL_Delay(500);
    
    // ?????
    uint16_t raw2 = AS5600_ReadRaw();
    float mech2 = (float)raw2 / 4096.0f * _2PI;
    
    // ================= 3. ????? =================
    // ??? = ??? * ??? - ???
    // ??1:0 = mech1 * POLE_PAIRS - offset1
    // ??2:PI = mech2 * POLE_PAIRS - offset2
    float offset1 = Normalize_Angle(mech1 * 7);
    float offset2 = Normalize_Angle(mech2 * 7 - PI);
    
    // ???(??:????????? 0 ? 2PI ???,???????)
    float elec_offset = (offset1 + offset2) / 2.0f;
    if (elec_offset < 0) elec_offset += _2PI; // ??? 0~2PI ??
    
    // 4. ?? PWM ?????,??? TIM1 ??
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
    HAL_TIM_Base_Start_IT(&htim1);
    
    return elec_offset;
}