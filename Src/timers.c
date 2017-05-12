
#include "timers.h" 
#include "appldefined.h"
#include "buttons.h"


TIM_HandleTypeDef htim2;
static void Error_Handler(void);



/* TIM2 init function */
void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 47;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 20000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim2);
  
  

}


static void Error_Handler(void)
{
  while(1) 
  {
  }
}

bool delay_ms (uint32_t Delay)
{
    static uint32_t start_tick = 0;
    bool result = false;

    if (start_tick == 0) 
    {
    	start_tick = HAL_GetTick();
    }

    else 
    if ((HAL_GetTick() - start_tick) == Delay)
    {
      start_tick = 0;
      result = true;
    }  

    return result;
}


bool debounce_ms(uint32_t debounce, device_t *device)
{
    bool result = false;
    
    if (device->button == BUT_MODE)
    {
        static uint32_t start_tick = 0;
        
        if (device->debounce == 0) 
        {
            device->debounce = debounce;
        }
        
        else
        if (device->debounce > 0)
        {
            if (start_tick == 0)
            {
                start_tick = HAL_GetTick();
            }

            else if ((HAL_GetTick() - start_tick) == device->debounce)
            {
              start_tick = 0;
              device->debounce = 0;
              result = true;
            }  
        }
    }
    
    else
    if (device->button == BUT_STOP)
    {
        static uint32_t start_tick = 0;
        
        if (device->debounce == 0) 
        {
            device->debounce = debounce;
        }
        
        else
        if (device->debounce > 0)
        {
            if (start_tick == 0)
            {
                start_tick = HAL_GetTick();
            }

            else if ((HAL_GetTick() - start_tick) == device->debounce)
            {
              start_tick = 0;
              device->debounce = 0;
              result = true;
            }  
        }
    }
    
    
    
    return result;
}

void set_pwm_tim2_ch4_duty (uint32_t Precent)
{
    if (0 == Precent) Precent = 1;
    TIM2->CCR4 = (((1000 * Precent) / 100) + 1000);
}

void pwm_on (void)
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}

void pwm_off (void)
{
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
}

