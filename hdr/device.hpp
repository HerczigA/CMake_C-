#ifndef _TEST_H_
#define _TEST_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "spi_module.hpp"
#include "i2c_module.hpp"
#include <wiringPi.h>

#define MAX_PORTS_NUMBER 21
#define MAX_SERVO_PORTS 8
#define MAX_DC 1024
#define SERVO_STEP 200
#define SERVO_HIGH_LIMIT 1050
#define SERVO_LOW_LIMIT -150
#define MIN_SERVO_DELAY_TIME 100
#define DEF_SERVO_TIME 200
#define DEF_SERVO_POSITION 500

typedef uint8_t devType_t;
typedef uint16_t Id_t;
typedef uint8_t comm_t;
typedef unsigned int time_ms_t;

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
    Unknow_communication,
    COMMTYPE

};

enum dev_type
{
    Sensor = 1,
    Actuator,
    Sensor_Actuator,
    Unknow_device,
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
        bool Initialized;
        int Init_SPI(SPI_Frame spi);
        int Init_I2C();
        int Init_Bluetooth();
        int Init_UART();
        int Init_CAN();
        int Init_Wifi();

    public:
        device(string Name, Id_t ID, devType_t devtype,comm_t commtype): name{Name}
        {
            id =( !ID && id_counter != 1 ) ? id_counter : id_counter++;
            dev_Type = (devtype >= Sensor && devtype <= Sensor_Actuator) ? devtype : Unknow_device;
            commType = (commtype >= SPI && commtype <= Wifi) ? commtype : Unknow_communication;
            wiringPiSetup();
            Initialized = false;
        }
        string get_Name();
        devType_t get_Dev_Type();
        Id_t get_ID();
        comm_t get_Comm_Type();
        uint8_t setPins(vector<uint8_t> pinNumbers,uint8_t directions[], uint8_t numberOfPorts);
        //void Init_Communication();
};

class sensor : public device
{
    public:
        sensor(string Name, Id_t ID, devType_t devtype, comm_t commtype) : device(Name,ID,devtype,commtype) {}

};

class actuator : public device
{
    
      public:
        actuator(string Name, Id_t ID, devType_t devtype, comm_t commtype) : device(Name,ID,devtype,commtype) {}
        void pwm_Setup(vector<uint8_t> pinNumbers,  uint8_t numberOfPorts);
        //void digital_Write();
        void pwm_Write(uint8_t pinNumber, uint16_t DC, unsigned int lengthOfDelay);
        void pwm_Servo_Write_In_Loop(uint8_t pinNumber, int16_t DC, time_ms_t lengthOfDelay, bool loop);
        void pwm_Servo_Full_Limit(uint8_t pinNumber,time_ms_t t_length);
        int16_t get_Servo_DC();
};


#endif