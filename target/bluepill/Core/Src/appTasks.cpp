
extern "C"
{
  #include "FreeRTOS.h"
  #include "cmsis_os.h"
  #include "task.h"

  #include "main.h"
  #include "spi.h"
  #include "usart.h"
  #include "gpio.h"
  #include "string.h"
}
#include <stdio.h>

extern "C" void StartControllerTask(void *argument)
{
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  const char text[] = "Ciao bel from FreeRTOS controller task!\n";
  for(;;)
  {
    HAL_UART_Transmit(&huart1, (uint8_t *)text, strlen(text), 500);
    vTaskDelay(xDelay);
  }
}

extern "C" void StartSensorTask(void *argument)
{
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  const char text[] = "Ciao bel from FreeRTOS sensor task!\n";
  for(;;)
  {
    HAL_UART_Transmit(&huart1, (uint8_t *)text, strlen(text), 500);
    vTaskDelay(xDelay);
  }
}