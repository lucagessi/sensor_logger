#include "Serial.hpp"
#include <cstring>

uint32_t Serial::available(){
    return this->_avail_in;
}

bool Serial::appendChar(char c){
    if(this->_avail_in < SERIAL_IN_BUFFER_SIZE){
        this->_in_buffer[this->_avail_in++] = c;
        return true;
    }else{
        return false;
    }
}
void Serial::reset(){
    this->_avail_in  = 0;
    this->_avail_out = 0;
}
bool Serial::write(const char * str){
    uint32_t len = strlen(str);
    return len == this->write( str, len );
}

uint32_t Serial::read(char * str, uint32_t len){
    uint32_t l = len > this->_avail_in ? this->_avail_in: len;
    memcpy( str, this->_in_buffer, l );
    // Restore in buffer
    memcpy( this->_in_buffer, this->_in_buffer+l, this->_avail_in-l );
    this->_avail_in-=l;
    return l;
}
