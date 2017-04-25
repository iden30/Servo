
#ifndef _TIMERS_H
#define _TIMERS_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include "types.h"

void MX_TIM2_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
static void Error_Handler(void);
extern bool delay_ms (uint32_t Delay);
extern void set_pwm_tim2_ch4_duty (uint32_t Precent);
extern bool debounce_ms(uint32_t Debounce);



#endif


