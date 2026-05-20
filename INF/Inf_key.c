#include "Inf_key.h"

Key_Type Inf_key_scan(void)
{
    /* 扫描引脚  */
    if (READ_KEY_LEFT == GPIO_PIN_RESET)
    {
        // 延时消抖
        vTaskDelay(10);
        if (READ_KEY_LEFT == GPIO_PIN_RESET)
        {
            while (READ_KEY_LEFT == GPIO_PIN_RESET)
                ;
            return KEY_LEFT;
        }
    }
    if (READ_KEY_RIGHT == GPIO_PIN_RESET)
    {
        // 延时消抖
        vTaskDelay(10);
        if (READ_KEY_RIGHT == GPIO_PIN_RESET)
        {
            while (READ_KEY_RIGHT == GPIO_PIN_RESET)
                ;
            return KEY_RIGHT;
        }
    }
    if (READ_KEY_UP == GPIO_PIN_RESET)
    {
        // 延时消抖
        vTaskDelay(10);
        if (READ_KEY_UP == GPIO_PIN_RESET)
        {
            while (READ_KEY_UP == GPIO_PIN_RESET)
                ;
            return KEY_UP;
        }
    }
    if (READ_KEY_DOWN == GPIO_PIN_RESET)
    {
        // 延时消抖
        vTaskDelay(10);
        if (READ_KEY_DOWN == GPIO_PIN_RESET)
        {
            while (READ_KEY_DOWN == GPIO_PIN_RESET)
                ;
            return KEY_DOWN;
        }
    }
    if (READ_KEY_LEFT_X == GPIO_PIN_RESET)
    {

        // 延时消抖
        vTaskDelay(10);

        if (READ_KEY_LEFT_X == GPIO_PIN_RESET)
        {
            while (READ_KEY_LEFT_X == GPIO_PIN_RESET)
                ;

            return KEY_LEFT_X;
        }
    }
    if (READ_KEY_RIGHT_X == GPIO_PIN_RESET)
    {
        // 延时消抖
        uint32_t tick_count = xTaskGetTickCount();
        vTaskDelay(10);
        if (READ_KEY_RIGHT_X == GPIO_PIN_RESET)
        {
            while (READ_KEY_RIGHT_X == GPIO_PIN_RESET)
                ;
            if (xTaskGetTickCount() - tick_count > 500)
            {
                return KEY_RIGHT_X_LONG;
            }
            return KEY_RIGHT_X;
        }
    }
    return KEY_NONE;
}
