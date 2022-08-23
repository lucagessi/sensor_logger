#ifndef SENSOR_LOGGER_LIS3DH_H
#define SENSOR_LOGGER_LIS3DH_H

#include "stdint.h"

class Lis3dh_Accelerometer : public AccelerometerSensor{
    public:
        bool init();

}; 

#endif