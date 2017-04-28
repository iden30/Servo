
#ifndef _BUTTONS_H
#define _BUTTONS_H

#include "main.h"
#include "stm32f1xx_hal.h"
#include "types.h"
#include "timers.h"
#include "stm32f1xx_it.h"

typedef enum 
{
    BUT_NONE = 0,
    BUT_STOP,
    BUT_MODE,
} t_but;


extern uint16_t get_button (void);


#endif
