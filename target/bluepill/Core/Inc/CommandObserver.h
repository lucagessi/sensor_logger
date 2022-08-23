#ifndef SENSOR_LOGGER_COMMAND_OBSERVER_H
#define SENSOR_LOGGER_COMMAND_OBSERVER_H

#include "CommandsInterpreter.hpp"

extern "C"
{
  #include "FreeRTOS.h"
  #include "cmsis_os.h"
  #include "task.h"
}


class CommandObserver : public CommandsInterpreter::Obserser{
    public:
        CommandObserver(osThreadId_t task){
            this->_task = task;
        }
        void notify(const CommandsInterpreter::command_t &cmd) override{
            last_cmd = cmd;
            if(cmd.type == CommandsInterpreter::command_id::rcfg){
                // Notify task
            }else if(cmd.type == CommandsInterpreter::command_id::single){
                // Notify task
            }
        }
        CommandsInterpreter::command_t last_cmd;
    private:
        osThreadId_t _task;
};

#endif