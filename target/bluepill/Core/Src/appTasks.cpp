
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
  #include "lis3dh_driver.h"
}
#include <stdio.h>

extern osThreadId_t controllerTaskHandle;
extern osThreadId_t sensorTaskHandle;

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

// Accelerometer interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == ACC_INT1_Pin){
    BaseType_t priority;
    // Sensor task notification
    vTaskNotifyGiveFromISR( sensorTaskHandle, &priority );
  }
}

extern "C" void StartSensorTask(void *argument)
{
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  char text[40];
  uint8_t whoiam;
  if( LIS3DH_GetWHO_AM_I(&whoiam) ){
    sprintf( text, "Sensor task, whoiam: 0x%02X \n", whoiam );
  }else{
    sprintf( text, "Sensor task, whoiam reding error\n" );
  }
  LIS3DH_SetODR( LIS3DH_ODR_25Hz );
  HAL_UART_Transmit(&huart1, (uint8_t *)text, strlen(text), 1000);    vTaskDelay(xDelay);

  for(;;)
  {
    ulTaskNotifyTake()
  }
}