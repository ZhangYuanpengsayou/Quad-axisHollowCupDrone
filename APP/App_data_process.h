#ifndef __APP_DATA_PROCESS__
#define __APP_DATA_PROCESS__

#include "com_types.h"
#include "Inf_joystick.h"
#include "Inf_key.h"
#include "usart.h"

#define LIMIT(x,min,max) (x < min ? min : (x > max ? max : x))
void App_DataProcess_Joystick(Remote_Struct *remote_data);

void App_DataProcess_Key(Remote_Struct *remote_data);

#endif // __APP_DATA_PROCESS__
