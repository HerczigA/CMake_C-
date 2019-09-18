#ifndef _TEST_H_
#define _TEST_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

enum comm_type
{
    SPI,
    CAN,
    UART,
    I2C,
    Bluetooh,
    Wifi

};

enum dev_type
{
    Sensor,
    Actuator,
    Sensor_Actuator
};

class foo
{
    public: 
    int i;
    foo() : i{10} {}
    foo(int const i_) : i{i_} {}
    auto getFooInt(){ return i;}
};

class filehandler
{
        fstream fileHand;
        string patternFile;
        string lineFromFile;
        const string newFile= "usable.txt";
        vector<string> pattern;
    public:
        filehandler(const char &p): patternFile(&p) {};
        void getPatternFileName();
        void getInfoFromPattern();
        void getLinesFromVector();
        void processPattern();
        void FinishProcess();
};


class device
{
    protected:
        uint16_t id;
        uint8_t commType;
        string name;
        uint8_t dev_Type;
    public:
        device(string Name, uint16_t ID, uint8_t devtype): id{ID}, name{Name}, dev_Type{devtype} {}
};

class sensor : protected device
{
    public:
        sensor(string Name, uint16_t ID, uint8_t devtype) : device(Name,ID,devtype) {}

};


#endif