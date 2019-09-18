#ifndef _TEST_H_
#define _TEST_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef uint8_t devType_t;
typedef uint16_t Id_t;

using namespace std;

static uint16_t id_counter =1;

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
    Sensor = 1,
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
        devType_t dev_Type;


    public:
        device(string Name, uint16_t ID, uint8_t devtype): name{Name}, dev_Type{devtype}
        {
            if(!ID)
                id = id_counter;
            id_counter ++;
        }
        string getName();
        devType_t getType();
        Id_t getID();
};

class sensor : public device
{
    public:
        sensor(string Name, uint16_t ID, uint8_t devtype) : device(Name,ID,devtype) {}

};


#endif
