#ifndef COMMANDSINTERPRETER_HPP
#define COMMANDSINTERPRETER_HPP

#include "Serial.hpp"
#include <cstring>
#include <stdio.h>

class CommandsInterpreter{

    public:
        const uint32_t MAX_SINGLE_CAPT_SECS = 60;
        enum command_id{
            single, rcfg
        };
        typedef struct{
            command_id type;
            union{
                struct{
                    uint32_t N; // seconds to acquire
                }single;
                struct{

                }rcfg;
            };
        }command_t;
        class Obserser{
            public:
                virtual void notify(const command_t &cmd){};
        };
        CommandsInterpreter(Serial *ser, Obserser *obs){
            this->_ser = ser;
            this->_obs = obs;
        }
        void refresh(){
            uint32_t s = this->_ser->available();
            bool rx = false;
            if( s >= 4 ){ // rcfg
                if(strstr(this->_ser->in_buffer(), "rcfg") != NULL){
                    this->cmd.type = rcfg;
                    this->_obs->notify(this->cmd);
                    _ser->in_flush();
                    return;
                }
            }
            if((s >= 8)){  // single N
                if(strstr(this->_ser->in_buffer(), "single ") != NULL){
                    sscanf( this->_ser->in_buffer(), "single %d", &(this->cmd.single.N) );            
                    if(this->cmd.single.N <= MAX_SINGLE_CAPT_SECS){ // 30 seconds max
                        this->cmd.type = single; 
                        this->_obs->notify(this->cmd);
                        _ser->in_flush();
                        return;
                    }
                }
            }
            _ser->in_flush();
        }
    private:
        Serial *_ser;
        Obserser *_obs;
        command_t cmd;
};


#endif