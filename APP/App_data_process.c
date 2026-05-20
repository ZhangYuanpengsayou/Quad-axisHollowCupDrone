#include "App_data_process.h"

// 摇杆偏移量
int16_t Joystick_bias[4] = {0};

void App_DataProcess_CalculateBias(Remote_Struct *remote_data)
{
    // 计算100的值 求平均值
    int16_t Joystick_bias_sum[4] = {0};
    for (uint8_t i = 0; i < 100; i++)
    {
        Joystick_bias_sum[0] += remote_data->THR - 0;
        Joystick_bias_sum[1] += remote_data->YAW - 500;
        Joystick_bias_sum[2] += remote_data->PIT - 500;
        Joystick_bias_sum[3] += remote_data->ROL - 500;
        vTaskDelay(4);
    }
    for (uint8_t i = 0; i < 4; i++)
    {
        Joystick_bias[i] += Joystick_bias_sum[i] / 100;
    }
}

void App_DataProcess_Joystick(Remote_Struct *remote_data)
{
    taskENTER_CRITICAL();
    // 1. 读取数据
    Inf_Joystick_Scan(remote_data);
    // 2. 处理数据的极性和范围
    remote_data->THR = 1000 - remote_data->THR * 1000 / 4095;
    remote_data->YAW = 1000 - remote_data->YAW * 1000 / 4095;
    remote_data->PIT = 1000 - remote_data->PIT * 1000 / 4095;
    remote_data->ROL = 1000 - remote_data->ROL * 1000 / 4095;

    // 3. 摇杆数据校准
    remote_data->THR -= Joystick_bias[0];
    remote_data->YAW -= Joystick_bias[1];
    remote_data->PIT -= Joystick_bias[2];
    remote_data->ROL -= Joystick_bias[3];

    // 4. 数据范围限制
    remote_data->THR = LIMIT(remote_data->THR, 0, 1000);
    remote_data->YAW = LIMIT(remote_data->YAW, 0, 1000);
    remote_data->PIT = LIMIT(remote_data->PIT, 0, 1000);
    remote_data->ROL = LIMIT(remote_data->ROL, 0, 1000);

    taskEXIT_CRITICAL();
}

void App_DataProcess_Key(Remote_Struct *remote_data)
{
    // 扫描按键
    Key_Type key_type = Inf_key_scan();

    switch (key_type)
    {
    case KEY_UP:
        Joystick_bias[2] -= 10;
        break;
    case KEY_DOWN:
        Joystick_bias[2] += 10;
        break;
    case KEY_LEFT:
        Joystick_bias[3] += 10;
        break;
    case KEY_RIGHT:
        Joystick_bias[3] -= 10;
        break;
    case KEY_LEFT_X:

        remote_data->power_down = 1;
        break;
    case KEY_RIGHT_X:
        remote_data->fix_height = 1;
        break;

    case KEY_RIGHT_X_LONG:
        // 计算偏移量
        // printf("计算偏移量\r\n");
        App_DataProcess_CalculateBias(remote_data);
        break;
    default:
        break;
    }
}
