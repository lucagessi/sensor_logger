#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <cstdint>

#define SERIAL_IN_BUFFER_SIZE 100
#define SERIAL_OUT_BUFFER_SIZE 100

class Serial{
    public: 
        virtual void init() = 0;
        uint32_t available();
        uint32_t read(char *, uint32_t);
        bool write(const char *);
        virtual uint32_t write(const char *, uint32_t) = 0;
    protected:
        bool appendChar(char);
        void reset();
        char _in_buffer[SERIAL_IN_BUFFER_SIZE];
        char _out_buffer[SERIAL_OUT_BUFFER_SIZE];
        uint32_t _avail_in;
        uint32_t _avail_out;
};

#endif