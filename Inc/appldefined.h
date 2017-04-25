
#ifndef _APPLDEFINED_H
#define _APPLDEFINED_H

#include "types.h"

#define BUT_DEBOUNCE 80

enum state_machine
{
    MODE_OFF = 0,
    MODE_L,
    MODE_M,
    MODE_H
}; 


typedef struct 
{
    uint16_t mode;   
}t_mode;

t_mode drive = {MODE_OFF};


#endif
