#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <cstdint>

#define SERIAL_IN_BUFFER_SIZE 100
#define SERIAL_OUT_BUFFER_SIZE 100

class Serial{
    public: 
        virtual void init(){};
        uint32_t available() const;
        uint32_t read(char *, uint32_t);
        bool write(const char *);
        const char * in_buffer();
        void in_flush();
        virtual uint32_t write(const char *, uint32_t) {return 0;};
        bool appendChar(char);
    protected:
        void reset();
        char _in_buffer[SERIAL_IN_BUFFER_SIZE+1];
        char _out_buffer[SERIAL_OUT_BUFFER_SIZE+1];
        uint32_t _avail_in;
        uint32_t _avail_out;
};

#endif