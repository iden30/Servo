
#ifndef _TIMERS_H
#define _TIMERS_H


#include "stm32f1xx_hal.h"
#include "types.h"

typedef struct 
{
    uint32_t button;
    uint32_t debounce;
    bool     state;
}device_t;

void MX_TIM2_Init(void);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
bool delay_ms (uint32_t delay);
void set_pwm_tim2_ch4_duty (uint32_t Precent);
bool debounce_ms(uint32_t debounce, device_t *device);
void pwm_on (void);
void pwm_off (void);



#endif


