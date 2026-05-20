#include "freeRTOS_task.h"

// 遥控数据
Remote_Struct remote_struct;

// 电源任务
void vPowerTask(void *pvParameters);
#define POWER_TASK_NAME "PowerTask"
#define POWER_TASK_STACK_SIZE 128
#define POWER_TASK_PRIORITY 4
TaskHandle_t power_task_handle;
#define POWER_TASK_PERIOD 10000

// 通讯任务
void vCommTask(void *pvParameters);
#define COMM_TASK_NAME "CommTask"
#define COMM_TASK_STACK_SIZE 256
#define COMM_TASK_PRIORITY 4
TaskHandle_t comm_task_handle;
#define COMM_TASK_PERIOD 6

// 按键任务
void vKeyTask(void *pvParameters);
#define KEY_TASK_NAME "KeyTask"
#define KEY_TASK_STACK_SIZE 128
#define KEY_TASK_PRIORITY 4
TaskHandle_t key_task_handle;
#define KEY_TASK_PERIOD 10

// 摇杆任务
void vJoystickTask(void *pvParameters);
#define JOYSTICK_TASK_NAME "JoystickTask"
#define JOYSTICK_TASK_STACK_SIZE 128
#define JOYSTICK_TASK_PRIORITY 4
TaskHandle_t joystick_task_handle;
#define JOYSTICK_TASK_PERIOD 6

// 显示任务
void display_task(void *args);
#define DISPLAY_TASK_NAME     "display_task"
#define DISPLAY_TASK_STACK    128
#define DISPLAY_TASK_PRIORITY 4
TaskHandle_t display_task_handle;
#define DISPLAY_TASK_PERIOD 10


void FreeRTOS_Task_Start(void)
{
    xTaskCreate(vPowerTask, POWER_TASK_NAME, POWER_TASK_STACK_SIZE, NULL, POWER_TASK_PRIORITY, &power_task_handle);
    xTaskCreate(vCommTask, COMM_TASK_NAME, COMM_TASK_STACK_SIZE, NULL, COMM_TASK_PRIORITY, &comm_task_handle);
    xTaskCreate(vKeyTask, KEY_TASK_NAME, KEY_TASK_STACK_SIZE, NULL, KEY_TASK_PRIORITY, &key_task_handle);
    xTaskCreate(vJoystickTask, JOYSTICK_TASK_NAME, JOYSTICK_TASK_STACK_SIZE, NULL, JOYSTICK_TASK_PRIORITY, &joystick_task_handle);
    xTaskCreate(display_task, DISPLAY_TASK_NAME, DISPLAY_TASK_STACK, NULL, DISPLAY_TASK_PRIORITY, &display_task_handle);
    printf("FreeRTOS Task Start\n");
    vTaskStartScheduler();
}
void vPowerTask(void *pvParameters)
{
    // 初始化ADC
    Inf_Joystick_Init();
    uint32_t preTime = xTaskGetTickCount();
    while (1)
    {
        Inf_ip5305t_Start();
        vTaskDelayUntil(&preTime, POWER_TASK_PERIOD);
    }
}

void vCommTask(void *pvParameters)
{
    // 初始化SI24R1
    Int_SI24R1_Init();
    uint32_t preTime = xTaskGetTickCount();

    while (1)
    {
        // 发送完关机和定高之后,改回0
        App_Comm_Send_Data(&remote_struct);

        vTaskDelayUntil(&preTime, COMM_TASK_PERIOD);
    }
}

void vKeyTask(void *pvParameters)
{

    uint32_t preTime = xTaskGetTickCount();
    while (1)
    {
        App_DataProcess_Key(&remote_struct);
        vTaskDelayUntil(&preTime, KEY_TASK_PERIOD);
    }
}

void vJoystickTask(void *pvParameters)
{
    uint32_t preTime = xTaskGetTickCount();
    while (1)
    {
        // 摇杆扫描初始数据
        App_DataProcess_Joystick(&remote_struct);
        // TODO 处理原始数据

        vTaskDelayUntil(&preTime, JOYSTICK_TASK_PERIOD);
    }
}

void display_task(void *args)
{
    // OLED屏幕初始化
    App_Display_Start();
    uint32_t preTime = xTaskGetTickCount();
    while (1) {
        App_Display_Show();
        vTaskDelayUntil(&preTime, DISPLAY_TASK_PERIOD);
    }
}

