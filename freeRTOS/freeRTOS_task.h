#ifndef _FREERTOS_TASK_H_
#define _FREERTOS_TASK_H_

#include "FreeRTOS.h"
#include "task.h"
#include "Inf_ip5305t.h"
#include "com_types.h"
#include "SI24R1.h"
#include "usart.h"
#include "string.h"
#include "Inf_key.h"
#include "Inf_joystick.h"
#include "App_data_process.h"
#include "App_comm_data.h"
#include "App_Display.h"

void FreeRTOS_Task_Start(void);

#endif
