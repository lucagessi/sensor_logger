#include "Serial.hpp"
#include <iostream>
#include <string>

class SerialFake : public Serial {
    public:
    SerialFake(){

    }
    void init() override {
        this->reset();
        return;
    }
    uint32_t write(const char *str, uint32_t N) override {
        std::string s = str;
        std::cout << s.substr(0, N) << std::endl;
        return N;
    }
    bool push(char c){
        return this->appendChar(c);
    }
};