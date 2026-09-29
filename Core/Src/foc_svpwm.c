#include "foc_svpwm.h"
#include "foc_config.h"

extern TIM_HandleTypeDef htim1;

void SVPWM_Calc(float valpha, float vbeta, float vbus, float *ta, float *tb, float *tc) {
    
    float va = valpha;
    float vb = -0.5f * valpha + 0.8660254f * vbeta;
    float vc = -0.5f * valpha - 0.8660254f * vbeta;

    
    float vmax = vbus / 1.7320508f;
    *ta = 0.5f + (va / vmax) * 0.5f;
    *tb = 0.5f + (vb / vmax) * 0.5f;
    *tc = 0.5f + (vc / vmax) * 0.5f;

    
    if (*ta > 0.95f) *ta = 0.95f; if (*ta < 0.05f) *ta = 0.05f;
    if (*tb > 0.95f) *tb = 0.95f; if (*tb < 0.05f) *tb = 0.05f;
    if (*tc > 0.95f) *tc = 0.95f; if (*tc < 0.05f) *tc = 0.05f;
}

void SVPWM_Apply(float ta, float tb, float tc) {
    uint32_t arr = __HAL_TIM_GET_AUTORELOAD(&htim1);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint32_t)(ta * arr));
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (uint32_t)(tb * arr));
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (uint32_t)(tc * arr));
}