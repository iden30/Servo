
#include "buttons.h"

static bool sts_button = false;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  UNUSED(GPIO_Pin);
  sts_button = true;
}

extern bool get_button (void)
{
    if(true == sts_button)
    {
        sts_button = false;
        return true;
    }
    return false;
}
