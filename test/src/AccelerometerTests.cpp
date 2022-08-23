#include "AccelerometerSensor.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

class AccelerometerEventListenerMock : public AccelerometerSensor::EventListener{
    public:
        AccelerometerEventListenerMock(){
            this->empty_buff = 0;
            this->full_buff = 0;
            this->new_data = 0;
        }
        void OnFullBufferEvent() override{
            this->full_buff++;
        }
        void OnEmptyBufferEvent() override{
            this->empty_buff++;
        }
        void OnNewDataAvailableEvent() override{
            this->new_data++;
        }
        uint32_t empty_buff = 0;
        uint32_t full_buff  = 0;
        uint32_t new_data   = 0;
};

class AccelerometerDriverFake : public AccelerometerSensor::Driver{
    public:
        AccelerometerDriverFake(){
            this->_available = 0;  
        }  
        bool setConfig(const AccelerometerSensor::accelerometer_config_t &config) override{
            this->_config = config;
            return true;
        }
        uint32_t read(uint8_t *data, uint32_t N) override{
            AccelerometerSensor::samples_t *sample = (AccelerometerSensor::samples_t *)data;
            uint32_t max = N>this->_available?this->_available:N;
            for( uint32_t idx=0;idx<max;idx++){
                sample->x = (idx*3) + 0;
                sample->y = (idx*3) + 1;
                sample->z = (idx*3) + 2;
                sample = &( sample[1] );
            }
            return max;
        }            
        const AccelerometerSensor::accelerometer_config_t * getConfig() override{
            return &this->_config;
        }     
        uint32_t available() override{
            return this->_available;
        }   
        void forceDataAvailable(uint32_t N){
            this->_available = N;
        }
    private:
        uint32_t _available;
        AccelerometerSensor::accelerometer_config_t _config;
};

TEST(Accelerometer, InitCondition) { 
    AccelerometerEventListenerMock listener;
    AccelerometerDriverFake drv;
    AccelerometerSensor acc( &drv, &listener );
    drv.forceDataAvailable(0);
    acc.refresh();
    EXPECT_EQ(acc.available() , 0);
    EXPECT_TRUE(acc.emptyBuffer());
    EXPECT_FALSE(acc.fullBuffer());
}

TEST(Accelerometer, AvailableEqualsFakeDriver) { 
    uint32_t fakedatalen = 3;
    AccelerometerEventListenerMock listener;
    AccelerometerDriverFake drv;
    AccelerometerSensor acc( &drv, &listener );
    drv.forceDataAvailable(0);
    acc.refresh();
    drv.forceDataAvailable(fakedatalen);
    acc.refresh();
    EXPECT_EQ(acc.available() , fakedatalen);
    EXPECT_FALSE(acc.emptyBuffer());
    EXPECT_FALSE(acc.fullBuffer());
}

TEST(Accelerometer, EmptyAfterRead) { 
    uint32_t fakedatalen = 3;
    AccelerometerSensor::samples_t samples[40];
    AccelerometerEventListenerMock listener;
    AccelerometerDriverFake drv;
    AccelerometerSensor acc( &drv, &listener );
    drv.forceDataAvailable(0);
    acc.refresh();
    drv.forceDataAvailable(fakedatalen);
    acc.refresh();
    acc.read( samples, 3 );
    EXPECT_EQ(acc.available() , 0);
    EXPECT_TRUE(acc.emptyBuffer());
    EXPECT_FALSE(acc.fullBuffer());
}

TEST(Accelerometer, EmptyAfterReadOversize) { 
    uint32_t fakedatalen = 3;
    AccelerometerSensor::samples_t samples[40];
    AccelerometerEventListenerMock listener;
    AccelerometerDriverFake drv;
    AccelerometerSensor acc( &drv, &listener );
    drv.forceDataAvailable(0);
    acc.refresh();
    drv.forceDataAvailable(fakedatalen);
    acc.refresh();
    acc.read( samples, 10 );
    EXPECT_EQ(acc.available() , 0);
    EXPECT_TRUE(acc.emptyBuffer());
    EXPECT_FALSE(acc.fullBuffer());
}

TEST(Accelerometer, ReadNotEntireBufferNotEmpy) { 
    uint32_t fakedatalen = 3;
    AccelerometerSensor::samples_t samples[40];
    AccelerometerEventListenerMock listener;
    AccelerometerDriverFake drv;
    AccelerometerSensor acc( &drv, &listener );
    drv.forceDataAvailable(0);
    acc.refresh();
    drv.forceDataAvailable(fakedatalen);
    acc.refresh();
    acc.read( samples, 2 );
    EXPECT_EQ(acc.available() , 1);
    EXPECT_FALSE(acc.emptyBuffer());
}

TEST(Accelerometer, CorrectReadSamples) { 
    uint32_t fakedatalen = 3;
    AccelerometerSensor::samples_t samples[40];
    AccelerometerEventListenerMock listener;
    AccelerometerDriverFake drv;
    AccelerometerSensor acc( &drv, &listener );
    drv.forceDataAvailable(0);
    acc.refresh();
    drv.forceDataAvailable(fakedatalen);
    acc.refresh();
    acc.read( samples, 2 );
    EXPECT_EQ(samples[0].x , 0);
    EXPECT_EQ(samples[0].y , 1);
    EXPECT_EQ(samples[0].z , 2);
    EXPECT_EQ(samples[1].x , 3);
    EXPECT_EQ(samples[1].y , 4);
    EXPECT_EQ(samples[1].z , 5);
}

TEST(Accelerometer, MoreDataFromHWAccThanBufferSize) { 
    uint32_t fakedatalen = 999;
    AccelerometerEventListenerMock listener;
    AccelerometerDriverFake drv;
    AccelerometerSensor acc( &drv, &listener );
    drv.forceDataAvailable(0);
    acc.refresh();
    drv.forceDataAvailable(999);
    acc.refresh();
    EXPECT_EQ(acc.available() , ACCELEROMETER_SENSOR_BUFFER_SIZE / sizeof(AccelerometerSensor::samples_t));
    EXPECT_FALSE(acc.emptyBuffer());
    EXPECT_TRUE(acc.fullBuffer());
}

TEST(Accelerometer, NewDataEventCalled) { 
    uint32_t fakedatalen = 3;
    AccelerometerEventListenerMock listener;
    AccelerometerDriverFake drv;
    AccelerometerSensor acc( &drv, &listener );
    drv.forceDataAvailable(0);
    acc.refresh();
    drv.forceDataAvailable(fakedatalen);
    acc.refresh();
    EXPECT_EQ(listener.new_data , 1);
}