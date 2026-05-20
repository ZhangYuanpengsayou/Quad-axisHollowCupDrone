#ifndef __INF_KEY__
#define __INF_KEY__

#include "com_types.h"
#include "FreeRTOS.h"
#include "task.h"
#define READ_KEY_LEFT (HAL_GPIO_ReadPin(KEY_LEFT_GPIO_Port, KEY_LEFT_Pin))
#define READ_KEY_RIGHT (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin))
#define READ_KEY_UP (HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin))
#define READ_KEY_DOWN (HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin))
#define READ_KEY_LEFT_X (HAL_GPIO_ReadPin(KEY_LEFT_X_GPIO_Port, KEY_LEFT_X_Pin))
#define READ_KEY_RIGHT_X (HAL_GPIO_ReadPin(KEY_RIGHT_X_GPIO_Port, KEY_RIGHT_X_Pin))

Key_Type Inf_key_scan(void);

#endif // __INF_KEY__
