extern "C"
{
  #include "FreeRTOS.h"
  #include "cmsis_os.h"
  #include "task.h"
  #include "queue.h"
  #include "main.h"
  #include "spi.h"
  #include "usart.h"
  #include "gpio.h"
  #include "string.h"
  #include "lis3dh_driver.h"
}
#include <stdio.h>
#include "AccelerometerSensor.hpp"
#include "CommandsInterpreter.hpp"
#include "Serial.hpp"

#define APP_NEW_SENSOR_DATA_EVENT     0X01
#define APP_RX_SINGLEN_CMD_EVENT      0X02
#define APP_RX_READ_CONFIG_CMD_EVENT  0X04

extern osThreadId_t controllerTaskHandle;
extern osThreadId_t sensorTaskHandle;
static QueueHandle_t messageQueue;

#define CTRL_MSG_NEW_DATA  1
#define CTRL_MSG_NEW_CMD   2

typedef struct{
  uint32_t type;       // 1 = New data available in accelerometer, 2 = new command from serial
  union{
    CommandsInterpreter::command_t command;
  };
}controller_message_t;

class UartSerial : public Serial{
  public:
    UartSerial(UART_HandleTypeDef *huart){
      this->_huart = huart;
    }
    uint32_t write( const char *str, uint32_t len) override{
      HAL_UART_Transmit(&huart1, (uint8_t *)str, len, 500);
      return len;
    }
  private:
    UART_HandleTypeDef *_huart;
};

class SensorTaskEventListener : public AccelerometerSensor::EventListener{
  public:
    SensorTaskEventListener(){
    }
    void OnEmptyBufferEvent() override{

    }
    void OnNewDataAvailableEvent() override{
      controller_message_t msg;
      // Push notification 
      //xTaskNotify( this->_task, APP_NEW_SENSOR_DATA_EVENT, eSetBits );
      // Send a message to queue
      msg.type = CTRL_MSG_NEW_DATA;
      xQueueSend( messageQueue, (void *)&msg, (TickType_t)0 );
    }
    void OnFullBufferEvent() override{
    }
    void setTask(osThreadId_t task){
        this->_task = task;
    }
  private:
    osThreadId_t _task;
};


class LIS3DH_Driver : public AccelerometerSensor::Driver{
  public:
    LIS3DH_Driver(){
      // Static configuration!
      this->_config.fullscale = 4000;          // +- 2000mg
      this->_config.odr = 25;
      this->_config.resolution = 1;//0.9765625;    // mg
    }
    bool setConfig(const AccelerometerSensor::accelerometer_config_t &config) override {
      // Only static configuration at first
      uint8_t reg;
      LIS3DH_GetWHO_AM_I(&reg);
      if(reg != 0x33)
        return false;
      if(!LIS3DH_SetFullScale( LIS3DH_FULLSCALE_2 ))
        return false;
      if(!LIS3DH_SetMode( LIS3DH_NORMAL ))
        return false;
      if(!LIS3DH_SetODR( LIS3DH_ODR_25Hz ))
        return false;
      if(!LIS3DH_FIFOModeEnable( LIS3DH_FIFO_STREAM_MODE ))
        return false;
      return true;
    }
    uint32_t read(uint8_t *data, uint32_t N) override{
      AccelerometerSensor::samples_t *sample = (AccelerometerSensor::samples_t *)data;
      uint8_t fifo_stored = this->available();
      uint8_t max;
      AxesRaw_t raw_vals;
      uint8_t idx=0;
      max = N > fifo_stored ? fifo_stored : N;
      // Read all FIFO
      for(; idx<max;idx++){
        if(!LIS3DH_GetAccAxesRaw( &raw_vals ))
          return idx;
        // Convert from raw to m/s^2
        sample->x = this->_config.resolution * (raw_vals.AXIS_X >> 4); 
        sample->y = this->_config.resolution * (raw_vals.AXIS_Y >> 4); 
        sample->z = this->_config.resolution * (raw_vals.AXIS_Z >> 4); 
        sample = &(sample[1]);
      }
      return idx;
    }
    const AccelerometerSensor::accelerometer_config_t * getConfig() override{
      return &(this->_config);
    }
    uint32_t available() override{
      uint8_t fifo_stored;
      if(!LIS3DH_GetFifoSourceFSS(&fifo_stored)){
        return 0;
      }
      return fifo_stored;
    }
    ~LIS3DH_Driver(){

    }
  private:
    AccelerometerSensor::accelerometer_config_t _config;
};

static LIS3DH_Driver drv;
static AccelerometerSensor::accelerometer_config_t config;
//acc.setConfig( config );
static SensorTaskEventListener listener;
static AccelerometerSensor acc( &drv, &listener );
static UartSerial serial(&huart1);


// Accelerometer interrupt
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == ACC_INT1_Pin){
    // BaseType_t priority;
    // Sensor task notification
    // vTaskNotifyGiveFromISR( sensorTaskHandle, &priority );
  }
}

extern "C" void StartControllerTask(void *argument)
{
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  uint32_t notification;
  char text[50] = "Ciao bel from FreeRTOS controller task!\n";
  AccelerometerSensor::samples_t sample;
  // Create queue
  messageQueue = xQueueCreate( 10, sizeof(controller_message_t) );
  bool received;
  controller_message_t msg;
  for(;;)
  {
    //HAL_UART_Transmit(&huart1, (uint8_t *)text, strlen(text), 500);
    //xTaskNotifyWait(0, 0xffffffffUL, &notification, xDelay);
    received = xQueueReceive(messageQueue,  (void *)&msg, xDelay) == pdTRUE;
    if(received){
      if(msg.type == CTRL_MSG_NEW_DATA){
        sprintf( text, "Notification received!\n" );
        HAL_UART_Transmit(&huart1, (uint8_t *)text, strlen(text), 500);
        vTaskSuspendAll();
        uint32_t max = acc.available();
        for(uint32_t idx=0; idx<max; idx++)
        {
          acc.read(&sample, 1);
          serial.write( (char *)&sample, sizeof(AccelerometerSensor::samples_t ) );
        }
        serial.write( "\n", 1 );
        xTaskResumeAll();
      }else if(msg.type == CTRL_MSG_NEW_CMD){
      if(msg.command.type == CommandsInterpreter::rcfg){
          sprintf( text, "Read config cmd\n" );
          serial.write( (char *)text, strlen(text) );
        }else if(msg.command.type == CommandsInterpreter::single){
          sprintf( text, "Start single capture cmd. %d s\n", msg.command.single.N );
          serial.write( (char *)text, strlen(text) );
        }
      }
    }else{
      sprintf( text, "Notification NOT received!\n" );
      serial.write( (char *)text, strlen(text) );
    }
  }
}


extern "C" void StartSensorTask(void *argument)
{
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  acc.setConfig( config );
  listener.setTask(controllerTaskHandle);
  for(;;)
  {
    vTaskDelay( xDelay );
    //acc.refresh();
  }
}

class CommandListener : public CommandsInterpreter::Obserser{
  public: 
    void notify(const CommandsInterpreter::command_t &cmd) override{
      controller_message_t msg;
      if(cmd.type == CommandsInterpreter::command_id::rcfg){
          // Notify controller task. How pass N?
          // Maybe its better to use a queue?
          //xTaskNotify( this->_task, APP_RX_READ_CONFIG_CMD_EVENT, eSetBits );
          msg.type = CTRL_MSG_NEW_CMD;
          msg.command = cmd;
          xQueueSend( messageQueue, (void *)&msg, (TickType_t)0 );
      }else if(cmd.type == CommandsInterpreter::command_id::single){
          // Notify controller task
          xTaskNotify( this->_task, APP_RX_SINGLEN_CMD_EVENT, eSetBits );
          msg.type = CTRL_MSG_NEW_CMD;
          msg.command = cmd;
          xQueueSend( messageQueue, (void *)&msg, (TickType_t)0 );
      }
    }
    void setTask(osThreadId_t task){
        this->_task = task;
    }
  private:
    osThreadId_t _task;

};

static uint8_t rx_data;
extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
  serial.appendChar( rx_data );
  HAL_UART_Receive_IT( &huart1, &rx_data, 1 );
}

extern "C" void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
  //HAL_UART_AbortReceive_IT(&huart1);
  HAL_UART_Receive_IT( &huart1, &rx_data, 1 );
}

extern "C" void StartSerialTask(void *argument)
{
  const TickType_t xDelay = 200 / portTICK_PERIOD_MS;
  CommandListener cmdListener;
  cmdListener.setTask( controllerTaskHandle );
  CommandsInterpreter interpreter(&serial, &cmdListener);
  char text[40];
  uint32_t len;
  huart1.pRxBuffPtr = &rx_data;
  HAL_UART_Receive_IT( &huart1, &rx_data, 1 );
  for(;;)
  {
    vTaskDelay( xDelay );
    if(serial.available()){
      len = serial.available();
      sprintf( text, "Ser avail %d\n", len);
      serial.write( (char *)text, strlen(text) );
      serial.write( serial.in_buffer(), len );
      serial.write( (char *)"\n", 1 );
    }
    interpreter.refresh();
  }
}
