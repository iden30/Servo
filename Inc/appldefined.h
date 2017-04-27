
#ifndef _APPLDEFINED_H
#define _APPLDEFINED_H

#include "types.h"

#define BUT_DEBOUNCE 80

typedef struct t_state_maschine
{
  uint16_t state;
  uint16_t mode;
}t_maschine;

typedef enum 
{
    MODE_OFF = 0,
    MODE_L,
    MODE_M,
    MODE_H, 
    MODE_F
} t_mode; 

// состояние  (активен, неактивен, недоступен)
typedef enum
{
    STATE_MASCHINE_OFF = 0x00,
    STATE_MASCHINE_ON  = 0x01,
    STATE_MASCHINE_NA  = 0x02
} m_state_t;

#endif
