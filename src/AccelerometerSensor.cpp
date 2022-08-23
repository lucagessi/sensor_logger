#include "AccelerometerSensor.hpp"
#include <cstring>

void AccelerometerSensor::refresh(){
    uint32_t N = this->_drv->available();  // Number of samples, which is to be multipled by 3 axis
    uint32_t bytes = N * sizeof(samples_t); // 3 axis
    uint32_t samplesToRead = bytes > (ACCELEROMETER_SENSOR_BUFFER_SIZE - this->_buff_lvl) ? 
                            (ACCELEROMETER_SENSOR_BUFFER_SIZE - this->_buff_lvl)/sizeof(samples_t) : N;
    this->_drv->read( this->_buffer+this->_buff_lvl, samplesToRead);
    this->_buff_lvl+=samplesToRead * sizeof(samples_t);
    if(samplesToRead && (this->_buff_lvl == ACCELEROMETER_SENSOR_BUFFER_SIZE)){
        this->_listener->OnFullBufferEvent();
    }
    if(samplesToRead)
        this->_listener->OnNewDataAvailableEvent();
}

bool AccelerometerSensor::setConfig( const accelerometer_config_t &config ){
    return this->_drv->setConfig( config );
}

const AccelerometerSensor::accelerometer_config_t * AccelerometerSensor::getConfig(){
    return this->_drv->getConfig();
}

bool AccelerometerSensor::fullBuffer(){
    return this->_buff_lvl == ACCELEROMETER_SENSOR_BUFFER_SIZE;
}

bool AccelerometerSensor::emptyBuffer(){
    return this->_buff_lvl == 0;
}

uint32_t AccelerometerSensor::available(){
    return this->_buff_lvl / sizeof(samples_t); // To get better saving actual samples in buffer
}

uint32_t AccelerometerSensor::read( samples_t * samples, uint32_t N ){
    uint32_t M, max = this->available();
    if(max > N)
        M = N;
    else
        M = max;
    memcpy(samples, this->_buffer, sizeof(samples_t)*M);
    // Cycle the buffer if necessary
    if(M != max){
        uint32_t R = max-M;
        uint32_t rem_bytes = R*sizeof(samples_t);
        memcpy(this->_buffer, this->_buffer+sizeof(samples_t)*M, rem_bytes);
        this->_buff_lvl = rem_bytes;
    }else{
        this->_buff_lvl = 0;
        this->_listener->OnEmptyBufferEvent();
    }
    return M;
}