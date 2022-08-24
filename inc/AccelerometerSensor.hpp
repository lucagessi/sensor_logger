#ifndef SENSOR_LOGGER_ACCELEROMETER_SENSOR_H
#define SENSOR_LOGGER_ACCELEROMETER_SENSOR_H

#include "stdint.h"

#define ACCELEROMETER_SENSOR_BUFFER_SIZE      240 // Bytes
#define ACCELEROMETER_SAMPLES_SIZE            4   // Float as default data for semplicity

class AccelerometerSensor{

    public:
        typedef struct{
            uint32_t odr;        // Hz
            float    resolution; // Resolution in mg
            float    fullscale;  // Full scale in mg
        }accelerometer_config_t; 
        class EventListener{
            public:
                virtual void OnFullBufferEvent() {};
                virtual void OnEmptyBufferEvent() {};
                virtual void OnNewDataAvailableEvent() {};
        };
        typedef struct{
            float x;
            float y;
            float z;
        }samples_t;
        class Driver{
            public:
                virtual bool setConfig(const accelerometer_config_t &config){return false;};
                virtual uint32_t read(uint8_t *data, uint32_t N){return 0;};             // Read N samples from accelerometer
                virtual const accelerometer_config_t * getConfig(){return nullptr;};     
                virtual uint32_t available(){return 0;};                                 // Return data available in FIFO HW
                virtual ~Driver(){};
        };
        AccelerometerSensor(Driver *drv, EventListener *listener){
            this->_drv = drv;
            this->_listener = listener;
            this->_buff_lvl = 0;
        }
        bool setConfig(const accelerometer_config_t &config);
        const accelerometer_config_t * getConfig();
        bool emptyBuffer();
        bool fullBuffer();
        void refresh();         // To be called periodically in order to read data from hw accelerometer and save it on ram
        uint32_t read(samples_t *samples,uint32_t N);
        uint32_t available();   // returns samples available as x,y, x set array.
    private:
        uint8_t _buffer[ACCELEROMETER_SENSOR_BUFFER_SIZE];
        uint32_t _buff_lvl;
        Driver *_drv;
        EventListener *_listener;
};


#endif