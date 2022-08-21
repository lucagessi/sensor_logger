#include "CommandsInterpreter.hpp"
#include <gtest/gtest.h>
#include "SerialFake.hpp"
#include <iostream>
#include <string>

class DummyCommandsObserver : public CommandsInterpreter::Obserser{
    public:
        DummyCommandsObserver(){
            this->single_cmd_rx = 0;
            this->rcfg_cmd_rx = 0;
        }
        void notify(const CommandsInterpreter::command_t &cmd) override{
            last_cmd = cmd;
            if(cmd.type == CommandsInterpreter::command_id::rcfg){
                this->rcfg_cmd_rx++;
                std::cout << "Command received: rcfg" << std::endl;
            }else if(cmd.type == CommandsInterpreter::command_id::single){
                this->single_cmd_rx++;
                std::cout << "Command received: single. N: " << std::to_string(cmd.single.N) << std::endl;
            }
        }
        uint32_t single_cmd_rx = 0;
        uint32_t rcfg_cmd_rx = 0;
        CommandsInterpreter::command_t last_cmd;
};

TEST(CommandsInterpreter, WrongCommandResetInputBuffer) { 
    SerialFake fake;
    Serial *ser = &fake;
    DummyCommandsObserver observer;
    CommandsInterpreter interpreter(ser, &observer);
    ser->init();
    fake.receive("Ciao bell");
    interpreter.refresh();
    EXPECT_EQ(ser->available() , 0) << "Serial input buffer not empty after init" ;
}

TEST(CommandsInterpreter, SingleCommandReceived) { 
    SerialFake fake;
    Serial *ser = &fake;
    DummyCommandsObserver observer;
    CommandsInterpreter interpreter(ser, &observer);
    ser->init();
    fake.receive("single 50");
    interpreter.refresh();
    EXPECT_EQ(observer.single_cmd_rx , 1);
}

TEST(CommandsInterpreter, RcfgCommandReceived) { 
    SerialFake fake;
    Serial *ser = &fake;
    DummyCommandsObserver observer;
    CommandsInterpreter interpreter(ser, &observer);
    ser->init();
    fake.receive("rcfg");
    interpreter.refresh();
    EXPECT_EQ(observer.rcfg_cmd_rx , 1);
}