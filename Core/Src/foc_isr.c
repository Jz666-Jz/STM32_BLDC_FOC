#include "foc_control.h"
#include "foc_encoder.h"
#include "stm32f1xx_hal.h"
#include "foc_pid.h"
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == &htim1) {
			foc_high_isr();
              
    } else if (htim == &htim2) {
			     Encoder_Update();

			
    }
}