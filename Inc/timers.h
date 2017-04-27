
#ifndef _TIMERS_H
#define _TIMERS_H

#include "stm32f1xx_hal.h"
#include "types.h"

void MX_TIM2_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
bool delay_ms (uint32_t Delay);
void set_pwm_tim2_ch4_duty (uint32_t Precent);
bool debounce_ms(uint32_t Debounce);
void pwm_on (void);
void pwm_off (void);



#endif


