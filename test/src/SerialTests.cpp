#include <gtest/gtest.h>
#include "SerialFake.hpp"
#include <string>
/*
TEST(Serial, DummyFail) { 
    SerialFake serfake;
    Serial *ser = &serfake;
    char str[] = "Ciao bel";
    ser->write(str);
    EXPECT_EQ(1, 0) << "Dummy fail information";
}
*/

using std::string;

TEST(SerialInputBuffer, EmptyAfterInit) { 
    Serial *ser = new SerialFake();
    ser->init();
    EXPECT_EQ(ser->available() , 0) << "Serial input buffer not empty after init" ;
}

TEST(SerialInputBuffer, NotEmptyAfterPushChar) { 
    const char c = '@';
    SerialFake fake;
    Serial *ser = &fake;
    ser->init();
    fake.push(c);
    EXPECT_EQ(ser->available() , 1) << "Serial input buffer is empty after pushing dummy data" ;
}

TEST(SerialInputBuffer, ReadEqualsPushed) { 
    const char c = '@';
    char rc;
    SerialFake fake;
    Serial *ser = &fake;
    ser->init();
    fake.push(c);
    ser->read( &rc, 1 );
    EXPECT_EQ(rc , c) << "Serial read char is not equal to pushed one" ;
}

TEST(SerialInputBuffer, AvailableEqualsStringLengthPushed) { 
    const string str = "Hello world!";
    SerialFake fake;
    Serial *ser = &fake;
    ser->init();
    for(uint32_t i=0;i < str.length();i++){
        fake.push(str.c_str()[i]);
    }
    EXPECT_EQ(ser->available() , str.length()) << "Serial data available differs from string length" ;
}

TEST(SerialInputBuffer, SameStringPushed) { 
    const string str = "Hello world!";
    char rc[40];
    SerialFake fake;
    Serial *ser = &fake;
    ser->init();
    for(uint32_t i=0;i < str.length();i++){
        fake.push(str.c_str()[i]);
    }
    ser->read(rc, str.length());
    rc[str.length()] = 0; // Write end string delimiter
    EXPECT_TRUE( string(rc) == str ) << "Serial string read back is not equal. Pushed: " << str << ".Read: " << string(rc);
}

TEST(SerialInputBuffer, EmptyDataAfterReadBackString) { 
    const string str = "Hello world!";
    char rc[40];
    SerialFake fake;
    Serial *ser = &fake;
    ser->init();
    for(uint32_t i=0;i < str.length();i++){
        fake.push(str.c_str()[i]);
    }
    ser->read(rc, str.length());
    EXPECT_EQ(ser->available() , 0) << "Serial input buffer not empty after read back" ;
}