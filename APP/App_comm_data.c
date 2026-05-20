#include "App_comm_data.h"

uint8_t data_buf[TX_PLOAD_WIDTH] = {0};

void App_Comm_Send_Data(Remote_Struct *remote_data)
{
    // (1)打包数据
    // |帧头3|数据10|校验和(4)|  => 定长数据 17字节足够 不需要32
    uint8_t index = 0;
    data_buf[index++] = FRAME0;
    data_buf[index++] = FRAME1;
    data_buf[index++] = FRAME2;

    // 放数据
    data_buf[index++] = remote_data->THR >> 8;
    data_buf[index++] = remote_data->THR;
    data_buf[index++] = remote_data->YAW >> 8;
    data_buf[index++] = remote_data->YAW;
    data_buf[index++] = remote_data->PIT >> 8;
    data_buf[index++] = remote_data->PIT;
    data_buf[index++] = remote_data->ROL >> 8;
    data_buf[index++] = remote_data->ROL;

    taskENTER_CRITICAL();
    data_buf[index++] = remote_data->power_down;
    data_buf[index++] = remote_data->fix_height;

    // 只发一次关机和定高的信号
    if (remote_data->power_down == 1)
    {
        remote_data->power_down = 0;
    }
    if (remote_data->fix_height == 1)
    {
        remote_data->fix_height = 0;
    }
    taskEXIT_CRITICAL();
    
    // 校验和
    uint32_t sum = 0;
    for (uint8_t i = 0; i < index; i++)
    {
        sum += data_buf[i];
    }
    data_buf[index++] = sum >> 24;
    data_buf[index++] = sum >> 16;
    data_buf[index++] = sum >> 8;
    data_buf[index++] = sum >> 0;

    Int_SI24R1_TxPacket(data_buf);
}
