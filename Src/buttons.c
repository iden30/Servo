
#include "buttons.h"

static bool sts_button = false;
static uint16_t but = BUT_NONE;




void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  UNUSED(GPIO_Pin);
 
  sts_button = true;
    
  if (But_Mode_Pin == GPIO_Pin)
  {
      but = BUT_MODE;
  }
  
  if (But_Stop_Pin == GPIO_Pin)
  {
      but = BUT_STOP; 
  }
  
  
}

uint16_t get_button (void)
{
    if(true == sts_button)
    {
        sts_button = false;
        return but;
    }
    return BUT_NONE;
}
