#ifndef __INF_JOYSTICK__
#define __INF_JOYSTICK__

#include "adc.h"
#include "com_types.h"

void Inf_Joystick_Init(void);

void Inf_Joystick_Scan(Remote_Struct *remote);
#endif // __INF_JOYSTICK__
