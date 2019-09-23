#ifndef _TEST_H_
#define _TEST_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>

#define MAX_PORTS_NUMBER 21
#define MAX_SERVO_PORTS 8
#define MAX_DC 1024
#define SERVO_STEP 100
#define SERVO_HIGH_LIMIT 1150
#define SERVO_LOW_LIMIT -150

typedef uint8_t devType_t;
typedef uint16_t Id_t;
typedef uint8_t comm_t;
using namespace std;

static uint16_t id_counter =1;

enum comm_type
{
    SPI = 1,
    CAN,
    UART,
    I2C,
    Bluetooh,
    Wifi,
    COMMTYPE

};

enum dev_type
{
    Sensor = 1,
    Actuator,
    Sensor_Actuator,
    Unknow,
    DEVTYPE
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
        Id_t id;
        comm_t commType;
        string name;
        devType_t dev_Type;


    public:
        device(string Name, Id_t ID, comm_t devtype): name{Name}
        {
            id =( !ID && id_counter != 1 ) ? id_counter : id_counter++;
            dev_Type = (devtype >= Sensor && devtype <= Sensor_Actuator) ? devtype : Unknow;
        }
        string getName();
        devType_t getType();
        Id_t getID();
        uint8_t setPins(vector<uint8_t> pinNumbers,uint8_t directions[], uint8_t numberOfPorts);
};

class sensor : public device
{
    public:
        sensor(string Name, uint16_t ID, uint8_t devtype) : device(Name,ID,devtype) {}

};

class actuator : public device
{
      public:
        actuator(string Name, uint16_t ID, uint8_t devtype) : device(Name,ID,devtype) {}
        int pwm_Setup(vector<uint8_t> pinNumbers,  uint8_t numberOfPorts);
        //void digital_Write();
        void pwm_Write(uint8_t pinNumber, uint16_t DC, unsigned int lengthOfDelay);
        void pwm_Servo_Write(uint8_t pinNumber, int16_t DC, unsigned int lengthOfDelay, bool loop);
};


#endif
