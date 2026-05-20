#ifndef __APP_COMM_DATA__
#define __APP_COMM_DATA__

#include "com_types.h"
#include "SI24R1.h"
#include "FreeRTOS.h"
#include "task.h"
#define FRAME0 'W'
#define FRAME1 'Q'
#define FRAME2 'M'


void App_Comm_Send_Data(Remote_Struct *remote_data);

#endif // __APP_COMM_DATA__
