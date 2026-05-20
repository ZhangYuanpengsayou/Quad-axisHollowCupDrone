#ifndef __COM_TYPES_H__
#define __COM_TYPES_H__

#include "gpio.h"


// 通用类型
typedef enum {
    COM_OK,
    COM_ERROR
} Com_Status;
 
// 按键类型
typedef enum {
    KEY_NONE,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT_X,
    KEY_RIGHT_X,
    KEY_LEFT_X_LONG,
    KEY_RIGHT_X_LONG
} Key_Type;

// 遥控数据结构体
// 会有负数
typedef struct
{
    int16_t THR;// 油门
    int16_t YAW;//偏航角
    int16_t PIT;// 俯仰角
    int16_t ROL;// 横滚角
    uint8_t fix_height; //1:定高/取消定高 0:保持状态
    uint8_t power_down; //1:关机 0:不关机
} Remote_Struct;

#endif
